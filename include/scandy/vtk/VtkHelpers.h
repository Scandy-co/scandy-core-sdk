/****************************************************************************\
 * Copyright (C) 2017 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

/**
 * \file VtkHelpers.h
 * \brief Useful helpers for common VTK operations
 */

#ifndef Scandy_VtkHelpers_h
#define Scandy_VtkHelpers_h

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
class vtkPolyDataAlgorithm;
class vtkPolyData;
class vtkImageData;

#include <scandy/core/MeshType.h>
#include <scandy/utilities/vector_types.h>

namespace scandy { namespace utilities {

void colorizePolyData(vtkSmartPointer<vtkPolyData> poly_data, const float rgb[3], bool color_points=false);
void colorizePolyData(vtkSmartPointer<vtkPolyData> poly_data, const float r, const float g, const float b, bool color_points=false);

vtkSmartPointer<vtkPolyData> combinePolyData(vtkPolyData* poly_data_1, vtkPolyData* poly_data_2);
vtkSmartPointer<vtkPolyData> combinePolyData(vtkPolyDataAlgorithm *algo_1, vtkPolyDataAlgorithm *algo_2);

vtkSmartPointer<vtkMatrix4x4> getVtkMatrix4x4FromMat4f(scandy::utilities::Mat4f mat4f);
scandy::utilities::Mat4f getMat4fFromVtkMatrix4x4(vtkSmartPointer<vtkMatrix4x4> matrix);
void printVtkMatrix4x4(vtkSmartPointer<vtkMatrix4x4> matrix, const char* name="matrix");

bool saveImage(std::string file_path, vtkSmartPointer<vtkImageData> img_data=nullptr);

vtkSmartPointer<vtkPolyData> loadMesh(std::string file_path, bool clean_data=false);
bool saveMesh(std::string file_path, scandy::core::MeshType mesh_type=scandy::core::MeshType::AUTO, vtkSmartPointer<vtkPolyData> poly_data=nullptr, vtkSmartPointer<vtkImageData> img_data=nullptr);
bool savePLY(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data);
bool saveOBJ(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data, vtkSmartPointer<vtkImageData> img_data=nullptr);
bool saveSTL(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data);
bool saveGLB(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data, vtkSmartPointer<vtkImageData> tex_img = nullptr);
bool saveDraco(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data, vtkSmartPointer<vtkImageData> tex_img = nullptr);

vtkSmartPointer<vtkPolyData> volumeToMesh(vtkSmartPointer<vtkImageData> volume, bool cleanBackside=true, bool triangulate=true);
vtkSmartPointer<vtkPolyData> generateNormals(vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> reverseNormals(vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> cleanAndRegenerateNormalsPolyData(vtkSmartPointer<vtkPolyData> poly_data);

/**
 * Decimates the polydata to reduce the numebr of triangles
 * @method decimatePolyData
 * @param  percent          How much to decimate by. 0.1 is very little, 0.9 is a lot
 * @param  poly_data        The vtkPolyData to decimate
 * @return                  The decimated vtkPolyData
 */
vtkSmartPointer<vtkPolyData> decimatePolyData(float percent, vtkSmartPointer<vtkPolyData> poly_data);
/**
 * Decimates the polydata using a different more aggressive deicmate algo that changes the topology a lot
 * @method quadDecimatePolyData
 * @param  percent              How much to decimate by. 0.1 is very little, 0.9 is a lot
 * @param  poly_data            The vtkPolyData to decimate
 * @return                      The decimated vtkPolyData
 */
vtkSmartPointer<vtkPolyData> quadDecimatePolyData(float percent, vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> smoothPolyData(int iterations, vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> fillHolesPolyData(float hole_size, vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> poissonPolyData(int depth, vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> adjustHSVPolyData(float percent[3], vtkSmartPointer<vtkPolyData> poly_data, bool color_points=true);

void createTextureCoords(vtkSmartPointer<vtkPolyData> polydata);

}}

#endif // Scandy_VtkHelpers_h
