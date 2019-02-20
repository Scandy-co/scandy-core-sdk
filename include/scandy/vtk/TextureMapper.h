/****************************************************************************\
 * Copyright (C) 2018 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

#include <scandy/utilities/vector_math.h>
#include <scandy/utilities/CameraIntrinsics.h>

#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkOBBTree.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>

#ifdef ENABLE_OPENCV
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#else
namespace cv {
class Mat{
Mat(){}
};
}
#endif

/* TextureMapper is responsible for for mapping the provide images to a mesh */
namespace scandy { namespace utilities{
/*
 * FaceLabel classifies faces for the patch-growing portion of algorithm in
 * "Multiple Textures Stitching and Blending on 3D Objects" by Rocchini et al.
 * internal: a face is surrounded by faces with the same target image
 * frontier: a face is bordering at least one face with different target image
 */
enum FaceLabel {internal, frontier};

/*
 * UVPoint represents the UV coordinate mapped from a vertex of a face to a
 * normalized position in a specific texture
 */
struct UVPoint {
  // the image ID that this UVPoint is mapped too
  int img_id;

  // true if this UVPoint belongs to a target face. these are the only ones
  // we want to write to the file
  bool target_face;

  // the normalized (u, v) coordinate mapping to the image
  float2 uv_coord;

  // the exact (rounded) pixel mapping from a vertex to the image
  int2 pixel;
};

/*
 * TexturedMeshPoint represents the 3D point of a mesh in world space and stores each
 * face it's part of for easier neighbor searching
 */
struct TexturedMeshPoint{
  // a list of faces that contains this point
  std::vector<int> face_ids;

  // the point position in world coordinates (using float4 for matrix math)
  float4 pt;
};

/*
 * TexturedMeshFace contains relevant information about a mesh's face in relation to
 * the texture mapping process
 */
// TODO add m_ to the member variables for clarity
class TexturedMeshFace {
public:
  // the three point IDs for this each point making up this face in the mesh
  std::vector<int> pt_ids;

  // a list of computed neighbors based on sharing a single pt_id
  std::vector<int> neighbors;

  // the classification on the face compared to its neighbors' target images
  FaceLabel label;

  // the ID for the "target" image, which is the one that best maps to this
  // face. Initially it will be the one with the best view angle/face normal
  // correspondence, then after the patch growing step will be a combination
  // of that and its neighborhood consensus
  int target_img_id;

  // TODO there might need to be a more inclusive struct for each of the
  // valid_img_ids, uv_indices, and view_angles

  // a short list of 3 image IDs that all see this face fairly well. this list
  // includes the target_img_id;
  std::vector<int> valid_img_ids;

  // index to the uv coordinates stored in the TextureMapper's UVCoord vector
  // one for each valid image seeing this face
  std::vector<int> uv_indices;

  // view angle of this face's projection related to each of the valid_img_ids
  std::vector<float> view_angles;

  // TODO this might be needed unless we need to grow a patch into the unseen
  // portions of the mesh
  bool visible;

  // number of neighbors that share the same target image.
  int num_target_neighbors;

  // ratio of neighbors that have a different target image
  float neighbor_ratio;
public:
  // default constructor that initializes appropriate values to 0 or equivalent
  TexturedMeshFace();

  // checks if info for img_idx is already stored, then checks if the view_angle
  // is better than any of the valid images stored and updates valid_img_ids,
  // view_angles, uv_indices, and target_img_id accordingly
  bool tryAddValidImage(float view_angle, std::vector<float2> local_uv_coords, std::vector<int2> local_pixel, std::vector<UVPoint>& uv_pts, vtkIdType *pt_ids, int img_idx, bool check_valid);

  // "pops" the target image from the info stored within this face. used when the face is found to be occluded in the target image
  // either results in the next best face becoming the target, or no target at all
  void removeOldTargetImg(std::vector<UVPoint>& uv_pts);


private:
  // return the index for valid_img_ids, view_angles, and uv_indices that were
  // all derived from the same img_idx. returns -1 if this img_idx isn't stored
  // as a valid image for this face AND if the valid_img_ids is full. returns
  // the next available index into valid_img_ids if it's not full and if this
  // image index is not stored
  int getInternalIdxForImg(int img_idx);
};

/*
 * TextureMapper holds all the data needed and executes the major functions of
 * the texture mapping process.
 */
class TextureMapper {
public:
  // the vtkPolyData that textures are being mapped to. TexturedMeshFaces will be
  // mapped to the list of faces in the polydata during the execution.
  // NOTE: this is assumed to have faces, vertices, and face normals
  // TODO: have a check for face normals or other missing components that can
  // be calculated before texture mapping
  vtkSmartPointer<vtkPolyData> m_texture_poly;

  // list of faces extracted from m_texture_poly for convenience
  vtkSmartPointer<vtkCellArray> m_face_list;

  // list of points extracted from m_texture_poly for convenience
  vtkSmartPointer<vtkPoints> m_pt_list;

  // list of face normals extracted/computed from m_texture_poly for convenience
  vtkSmartPointer<vtkFloatArray> m_face_normals;

  // number of faces in m_texture_poly
  int m_num_faces = 0;

  // number of points in m_texture_poly
  int m_num_pts = 0;

  // a mapping from the face IDs in m_texture_poly with additional helpful
  // information for texture mapping process
  std::vector<TexturedMeshFace> m_mesh_faces;

  // number of frontier faces in m_mesh_faces;
  int m_num_frontier = 0;

  // a mapping from the point IDs in m_texture_poly with additional helpful
  // information for texture mapping process
  std::vector<TexturedMeshPoint> m_mesh_pts;

  // a list of all UVPoints successfully mapped to a vertex from any image in
  // the images provided.
  // NOTE: not all of these UVPoints should be written to the final object file
  // the TexturedMeshFaces written will have a reference to the UVPoints needed
  // it's possible for there to be 3 x m_num_faces of these if m_num_poses_saved >= 3
  // otherwise there will be m_num_poses_saved x m_num_faces of these
  std::vector<UVPoint> m_uv_points;

  // a list of camera poses (maps camera coords to world coords) for each image
  // being mapped to m_texture_poly
  std::vector<Mat4f> m_cam_poses;

  // directory path name to the saved images and poses
  std::string m_img_dir_path;

  // directory path name (within application's "Documents" for iOS) to save
  // the output files into
  std::string m_out_dir_path;

  // file name to use for output mesh, texture, and material file, which proper
  // extensions will be added to at time of save
  std::string m_out_file_name;

  // a helpful data structure for the faces to check occlusion from a view
  vtkSmartPointer<vtkOBBTree> m_raycast_tree;

  CameraIntrinsics m_camera_intrinsics;

  float m_view_angle_thresh;

  std::vector<cv::Mat> m_cv_in_imgs;

  // z buffers for each image. matrix of single channel floats with center distance of triangle
  // TODO better pixel to point depth estimation with interpolation from triangle points
  std::vector<cv::Mat> m_z_buffs;

  // a mapping of each pixel in an image to the face it projects to on the mesh or -1 if none
  std::vector<cv::Mat> m_face_maps;

  // mask of the mapped part of each image
  std::vector<cv::Mat> m_img_masks;

  // mask of the mapped part of each image
  std::vector<cv::Mat> m_masked_imgs;

  // Determines whether to load images from disk. If false, you need to provide poses and images manually
  bool m_get_images_from_disk;
  // Determines whether to save the output to disk. If false, you need to get the output manually
  bool m_save_to_disk;

public:
  // constructor with the polydata to map to that initializes member variables
  // with information from in_polydata
  TextureMapper(vtkSmartPointer<vtkPolyData> in_polydata);

  // constructor with polydata and directory of images and poses to map and
  // optionally an output directory path and file name. it is recommended to
  // give the out_dir here, but the default will be Documents/<date_time>/
  TextureMapper(
    vtkSmartPointer<vtkPolyData> in_polydata,
    int num_poses_saved,
    std::string img_directory,
    std::string out_file_name,
    std::string out_dir = ""
  );

public:
  // How many poses are we working with?
  int numPosesSaved();

  // sets the name of the output directory (within application's "Documents"
  // directory for iOS)
  void setOutputDirectory(std::string out_dir);

  // Add an image to the to vector of loaded images
  void addImg(cv::Mat img);

  // main call to run the texture mapping process
  void execute();

  // TODO make our vtkOBJWriter able to handle this stuff
  // saveOutput saves the mesh with the mapped texture(s) and material file
  // as output_obj_name (with .obj, .jpeg, and .mtl respectively) in the
  // output_directory path.
  // this function is called during the execute() process, but is able to be
  // called after execute() has completed to save a copy elsewhere
  // returns true if save was successfully completed
  bool saveOutput(std::string output_obj_name = "", std::string output_directory = "");

  void setCameraIntrinsics(CameraIntrinsics intrinsics);

private:
  // transfers all the vtkPolyData faces and points into our own structures for
  // faces (m_mesh_faces) and points (m_mesh_pts)
  void initializeMesh();

  // helper function that goes through the image directory and populate
  // m_cam_poses from the saved pose files
  void getPosesFromFile();

  // helper function that goes through the image directory and populate
  // m_cv_in_imgs from the saved images. also allocates the corresponding image masks
  void getImgsFromFile();

  // computes the initial mapping of each image's uv coordinates to the mesh
  void projectImagesToMesh();

  // find correspondences between areas of the mesh should all share the same
  // target image and re-map uv coordinates to reduce frontier faces
  void growPatches();

  // iterates through each face's neighbors and labels as frontier or internal face
  void labelFaces();

  // iterates through each face and if it's a minority frontier face, reproject it to the target image of it's neigbors
  void smoothBoundaries();

  void projectFace(Mat4f image_pose, Mat4f inverse_pose, float4 cam_dir, float4 cam_pos, int face_id, int img_idx, bool check_valid);

  // isValidProjection checks the face's normal with the cam_direction to check
  // for a valid projection angle and uses m_raycast_tree to check occlusion
  // of the face.
  // returns false if view angle is past m_view_thresh or if the face is
  // occluded and returns true otherwise
  bool isValidProjection(float3 face_normal, float4 center_of_tri, float4 face_pt, float4 cam_direction, float4 cam_pos, float& view_angle);

  // checks if this face is occluded by another face seen by this image or another image
  bool isOccluded(int img_idx, int face_id, std::vector<int2> tmp_pix, float4 center_of_tri, Mat4f inverse_pose);

  int4 getTextureBounds(int img_idx);

  // a naive approach to blending the texture seams by iterating through the frontier faces and
  // averaging the general rectangular areas from each neighbors face to try to blur the edge
  // NOTE: this must be run after labelFaces
  void blendSeams();


  // returns the (min_x, max_x, min_y, max_y) of pixel bounds of the neighbors of face
  // as seen from face's target_img_id
  scandy::utilities::int4 getRectForBorderFace(TexturedMeshFace face, int neighbor_img_id);

  // computes the color average of each patch
  void avgPatch(cv::Mat patch1, cv::Mat patch2, cv::Mat& outPatch);

  // writes a patch of an image to a new image only containing the boarder areas
  void writePatch(cv::Mat patch, cv::Mat& borderImg);


  // computes a bitmask that covers the parts of the image that were mapped to the mesh
  void maskImages();

  // remaps each individually mapped image into one single image to map
  // TODO optimize this for more efficient packing
  void packTextures();

  // updates the UV map for the combined image to map to the mesh
  // TODO update this when updating the packTextures internal algorithm
  void remapUV();

  // saved the remapped texture and mesh
  // TODO the innards of this will replace saveOutput();
  void saveCombinedOutput();
};

}}
