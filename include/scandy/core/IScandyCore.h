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

#ifndef Scandy_iscandycore_h
#define Scandy_iscandycore_h

/* Begin scandy includes */
#include <scandy.h>
#include <scandy/utilities/DepthTrackMetadata.h>
#include <scandy/utilities/RelativePose.h>
#include <scandy/core/Status.h>
#include <scandy/core/ScannerType.h>
#include <scandy/core/ScanState.h>
#include <scandy/core/MeshType.h>
#include <scandy/core/MeshExportOptions.h>
#include <scandy/core/ScanResolution.h>
#include <scandy/core/visualizer/Visualizer.h>
#include <scandy/core/visualizer/ISceneKitVisualizer.h>
#include <scandy/core/visualizer/VisualizerType.h>
#include <scandy/core/IScandyCoreConfiguration.h>


#ifdef SCANDY_QT
#include <QVTKWidget.h>
#endif
/* End scandy includes */

/* C++ stl includes */
#include <map>
#include <vector>
#include <memory>
/* End C++ stl includes */

namespace scandy { namespace core {

/**
 * Interface for interacting with ScandyCore.  Call factoryCreate to get a pointer
 * to ScandyCore.
 * NOTE: On iOS, access IScandyCore through ScandyCoreManager instead of factoryCreate().
 *
 */
class IScandyCore {
public:
  /**
   * Create a pointer to ScandyCore.  Use default visualizer options.
   * @return Valid pointer to ScandyCore.
   */
  static std::shared_ptr<IScandyCore> factoryCreate();

  /**
   * Create a pointer to IScandyCore.
   * @param width Width of the visualizer window in pixesls.
   * @param height Height of the visualizer window in pixels.
   * @param columns Number of columns to subdivide views into the main window.
   * @param rows Number of rows to subdivide views into the main window.
   * @return Valid pointer to IScandyCore.
   */
  static std::shared_ptr<IScandyCore> factoryCreate(
    int width,
    int height,
    int columns=1,
    int rows=1
  );

#ifdef SCANDY_QT
  /**
   * Create a pointer to IScandyCore.
   * @param width Width of the visualizer window in pixesls.
   * @param height Height of the visualizer window in pixels.
   * @param qvtkWidget A pointer to a QVTKWidget that IScandyCore should use as
   *                   its Visualizer
   * @return Valid pointer to IScandyCore.
   */
  static std::shared_ptr<IScandyCore> factoryCreate(
    int width,
    int height,
    QVTKWidget* qvtkWidget
  );
#endif

  /**
   * Checks to see if the IScandyCore has a valid license to perform SLAM
   * operations.
   * @return Returns scandy::core::Status::SUCCESS if it does, otherwise returns
   * an error status.
   */
  virtual scandy::core::Status hasValidLicense();

  /**
   * Sets the license to use with IScandyCore
   * @param  license The license string to use with Scandy Core
   * @return Returns scandy::core::Status::SUCCESS if the license
   * validated, otherwise returns an error status.
   */
  virtual scandy::core::Status setLicense(std::string license);

  // *** Actions

  /**
   * Prepares ScandyCore to perform a 3D scan.  If source is a file path reads that file.
   * @param scanner_type  The type of scanner (@see ScannerType.h)
   * @param source A Royale library .rrf file or a specific camera id.  Defaults to default camera id.
   * @return @see Status.h
   */
  virtual scandy::core::Status initializeScanner(ScannerType scanner_type, std::string source = "");

  /**
   * Clears the pipeline and configurations made for the current scanning session.
   * @return @see Status.h
   */
  virtual scandy::core::Status uninitializeScanner();

  /**
   * Sets up the image processing pipeline and workers
   * @return @see Status.h
   */
  virtual scandy::core::Status initializeImageProcessor();

  /**
  * Starts the processing pipeline that's been configured.
  * NOTE: You should only call this function when configuring the pipeline
  * manually, which is not fully supported at this time. Calling startPreview()
  * or startScanning() will tell the pipeline to start after it has been
  * automatically configured in initializeScanner().
  *
  * @return @see Status.h
  */
  virtual scandy::core::Status startPipeline();

  /**
  * Stops the processing pipeline.
  * NOTE: You should only call this function when configuring the pipeline
  * manually, which is not fully supported at this time. Calling stopScanning()
  * will tell the pipeline to stop. Then uninitializeScanner() can be called to
  * automatically tear down the pipeline configuration.
  *
  * @return @see Status.h
  */
  virtual scandy::core::Status stopPipeline();

  /**
   * Tells whether the underlying pipeline is running
   * @return bool true if pipeline is running, false if not.
   */
  virtual bool isRunning();

  /**
   * Tells whether the Network Mananger has connected clients or not
   * @return bool true if there are active connections, false if not.
   */
  virtual bool hasNetworkConnection();

  /**
   * Returns a list of strings of connected IP addresses
   */
  virtual std::vector<std::string> connectedClients();

  /**
   * Returns a list of strings of discovered Scandy Core host IP addresses
   */
  virtual std::vector<std::string> discoveredHosts();

  /*
   Connects to a remote host to receive commands from
   @return bool true if successful, false if not
   */
  virtual bool connectToCommandHost(std::string host);

  /**
   * Clears the list of hosts that we should receive commands from
   */
  virtual void clearCommandHosts();

  /**
   * Automatically create instances of the views in each col,grid location of the visualizer window.
   * Implicitly called if factoryCreate with visualizer params was invoked.
   * @param  width Width of the visualizer window in pixesls.
   * @param  height Height of the visualizer window in pixels.
   * @param  columns Number of columns to subdivide views into the main window.
   * @param  rows Number of rows to subdivide views into the main window.
   * @param  qvtkWidget If SCANDY_QT was enabled then this optional parameter
   *                    accepts a point to a QVTKWidget that IScandyCore shouldu use.
   * @return @see Status.h
   */
  virtual scandy::core::Status createVisualizer(
    int width=640,
    int height=480,
    int columns=1,
    int rows=1
#ifdef SCANDY_QT
    , QVTKWidget* qvtkWidget=NULL
#endif
  );

  virtual scandy::core::Status setVisualizerType(VisualizerType visualizer_type=VisualizerType::SCANDYCORE, void* native_host_ptr=nullptr);

  /**
   * Clears the current visualizer context. Helpful if your GL context updates
   * @return @see Status.h
   */
  virtual scandy::core::Status clearVisualizer(VisualizerType visualizer_type=VisualizerType::AUTO);


  /**
   * Adds a Viewport to the Visualizer with a 3D object in. Use to test your
   * setup to make sure the Visualizer is working and receiving interactions.
   * @return @see Status.h
   */
  virtual scandy::core::Status addTestViewport();

  /**
   * Adds a Viewport to the Visualizer that receives an volumetric video stream
   * and displays it in ARKit
   * @method addAR4DViewport
   * @return @see Status.h
   */
  virtual std::shared_ptr<ISceneKitVisualizer> addAR4DViewport();

  /**
   * Exports the most recent volumetic video recording to a series of the
   * desired file types.
   * @return @see Status.h
   */
  virtual scandy::core::Status exportVolumetricVideo(MeshExportOptions meshExportOptions);

  /**
   * Loads a mesh file from the local disk.
   * @param  file_path_or_url Absolute path to the mesh file to be loaded. Can be
   *         a .obj, .ply, or .stl file format.
   * @param  texture_path Optional absolute path to the texture file to be
   * loaded and mapped on the mesh. Can be .png, .jpg, or .jpeg file format.
   * @return @see Status.h
   */
  virtual scandy::core::Status loadMesh(std::string file_path_or_url, std::string texture_path="");

  /**
   * Loads a volumetric video exported in the Scandy Core format.
   * Looks for a scvv_animation.json in the src_dir_path
   * @method loadVolumetricVideo
   * @param  src_dir_path        Directory to load the volumetic video from
   * @return                     @see Status.h
   */
  virtual std::shared_ptr<ISceneKitVisualizer> loadVolumetricVideo(std::string src_dir_path, void* scnScene=nullptr);

  /**
   * Generate a mesh from current point cloud data as viewed in the visualizer.
   * @return @see Status.h
   */
  virtual scandy::core::Status generateMesh();

  /**
   * Reduce the number of points and triangles in the mesh.
   * @param percent 0.0 - 1.0 for percent reduction in number of points
   */
  virtual Status decimateMesh(float percent);
  /**
   * Smooth the surface of the mesh
   * @param iterations The number of smoothing iterations to make. 3-10 is a reasonable range
   */
  virtual Status smoothMesh(int iterations);
  /**
   * Attempts to automatically fill holes in the mesh
   * @param hole_size Largest area of to fill
   */
  virtual Status fillHoles(float hole_size);

  /**
   * Attempts to automatically make the mesh water tight
   * @param depth How deeply to follow the original model. 5 is loose, 8 is default, 13 is high
   */
  virtual Status makeWaterTight(int depth);

  /**
   * Adjust the Hue saturation and value of the mesh
   * @param hsv float[3] Percent increase on hue, saturation, and value respectively. -1.0 to 1.0
   */
  virtual Status adjustHSV(float hsv[3]);
  /**
   * Apply the edits being viewed in the Viewport into the mesh, so that when you save they take
   * @param apply_changes (true) Apply the edits or (false) undo the edits
   */
  virtual Status applyEditsFromMeshViewport(bool apply_changes);

  /**
   * Reset the in the camera in the mesh viewer
   */
  virtual Status resetViewportCamera();

  /**
   * Saves a screenshot of the current Visualizer to the specified file path
   * @param  file_path File path to save screenshot to
   * @return           @see Status.h
   */
  virtual Status saveScreenShot(std::string file_path);

  /**
   * Gets the currernt model orientation loaded in the Visualizer
   * @return Mat4f with the current model orientation
   */
  virtual scandy::utilities::Mat4f getModelOrientation();

  /**
   * Gets the current model's bounding box loading the visualizer
   * @return float3 with the current model bounding box
   */
  virtual scandy::utilities::float8 getModelBoundingBox();

  /**
   * Toggle wireframe or surface rendering for meshes.
   * @param enable_wireframe True for wireframe, false for surface
   * @return @see Status.h
   */
  virtual Status setEnableWireframe(bool enalbe_wireframe);

  /**
   * Toggle color or monochrome rendering for meshes.
   * @param enable_color True for color, false for monochrome
   * @return @see Status.h
   */
  virtual Status setEnableColorViewport(bool enable_color);

  /**
   * Set shader to use for surface rendering for meshes.
   * @param shaderName Name of the shader to use
   * @return @see Status.h
   */
  virtual Status setViewportShader(std::string shaderName);

  /**
   * Turns on and off a cropping plane for editing a mesh
   * @param  enable Boolean that enables of disables the cropping plane
   * @return @see Status.h
   */
  virtual Status setEnableCroppingPlane(bool enable);

  /**
   * Determines where the cropping plane is enabled
   * @return True for enabled, false otherwise
   */
  virtual bool getEnableCroppingPlane();


  /**
   * If cropping plane is orthogonal, then this helper functions sets the
   * cropping plane from 0-1.0 (0 to 100%) along that orthogonal plane.
   * @param  percent A percent (0.0 - 1.0) for how much to crop
   * @return @see Status.h
   */
  virtual Status setCroppingPlanePercent(float percent);


  /**
   * Saves the output from the previously generated mesh to disk.
   * @method saveMesh
   * @param  file_path  The absolute file path of where you want to save mesh
   * to.
   * @param  mesh_type  The MeshType that you want to save.
   * @param  save_color Whether or not the saved mesh should include color. Set
   * to true to save the color, and false to save monochrome. Some MeshType do
   * not support color and will ignore this flag. For example, STL always saves
   * as monochrome.
   * @return            Should return scandy::core::Status::SUCCESS. If it does
   * not, there was an error saving the mesh.
   */
  virtual scandy::core::Status saveMesh(std::string file_path, MeshType mesh_type=MeshType::PLY, bool save_color=true);

  /**
   * Begin showing sensor data in the visualizer window but do not start SLAM algorithms.
   * @return @see Status.h
   */
  virtual scandy::core::Status startPreview();

  /**
   * Start the SLAM algorithm, creates a 3D scan by tracking successive frames
   * and integrating them into a TSDF.
   * @return @see Status.h
   */
  virtual scandy::core::Status startScanning();

  /**
   * Stop the SLAM algorithm. Do not continue to record and integrate sensor data.
   * @return @see Status.h
   */
  virtual scandy::core::Status stopScanning();

  // *** Getters

  /**
   * Get the underlying IScandyCoreConfiguration.
   * @return Pointer to IScandyCoreConfiguration.
   */
  virtual std::shared_ptr<scandy::core::IScandyCoreConfiguration> getIScandyCoreConfiguration();

  /**
   * Get the underlying visualizer that is platform dependent.
   * @return Pointer to visualizer.
   */
  virtual std::shared_ptr<scandy::core::Visualizer> getVisualizer();

  /**
   * Get current available resolutions as a vector. This must be called after
   * initializeScanner otherwise you will always get vector with 0 elements.
   * @return Vector map of available resolutions.
   */
  virtual std::vector<ScanResolution> getAvailableScanResolutions();

  /**
   * Gets the current resolution of the scanning volume in meters.
   * @method getScanResolution
   * @return A ScanResolution which describes the resolution that scanning
   * volume is configured for.
   */
  virtual scandy::core::ScanResolution getScanResolution();

  /**
   * Gets the current size of the scanning volume in meters.
   * @method getScanSize
   * @return A scandy::utilities::float3 with the x, y, z representing the
   * width, height, and depth of the current scanning volume.
   */
  virtual scandy::utilities::float3 getScanSize();

  /**
   * Gets the current voxel size in meters.
   * @method getVoxelSize
   * @return A float representing the voxel size in meters
   */
  virtual float getVoxelSize();

  /**
   * Gets the current scan state of ScandyCore
   * @return ScanState of IScandyCore instance
   */
  virtual scandy::core::ScanState getScanState();

  /**
   * Gets the currently available use cases for scanning. These are different
   * frame rates or configurations that can be used depending on the Scanner.
   * @return A list of strings that can be provided to IScandyCore::setUseCase
   */
  virtual std::vector<std::string> getUseCases();

  // *** Setters

  // *** These setter methods only have affect if called pre-scan.

  /**
   * How many voxels are contained within our setScanSize. Use the
   * ScanResolutions return from IScandyCore::getAvailableScanResolutions()
   * @param resolution
   * @return @see Status.h
   */
  virtual scandy::core::Status setResolution(ScanResolution resolution);

  /**
   * Sets frame rate and hardware modes
   * @param use_case Can be any value supported by depth sensor.
   * @return @see Status.h
   */
  virtual scandy::core::Status setUseCase(std::string use_case);

  /**
   * The scan size of each frame in the scene, example: 1 meter * 1 meter * 1 meter
   * @param size The size of the volume in meters.
   * @return @see Status.h
   */
  virtual scandy::core::Status setScanSize(scandy::utilities::float3 size);

  /**
   * The scan size of each frame in the scene, example: 1 meter * 1 meter * 1 meter
   * @param size The size of the volume in meters.
   * @return @see Status.h
   */
  virtual scandy::core::Status setScanSize(float size);


  /**
   * The size of each voxel in the scan volume. Essentially setting resolution when
   * using unbounded scanning. 0.0005 - 0.04 are a good range of values.
   * @param size The size of the voxel in meters.
   * @return @see Status.h
   */
  virtual scandy::core::Status setVoxelSize(float size);

  /**
   * Sets the noise filter in Scandy Core depending on the scanner type
   * @param  percent 0.0 - 1.0 with higher values providing a tighter filter that removes more data
   * @return @see Status.h
   */
  virtual Status setNoiseFilter(float percent);

  /**
   * Set the distance between the sensor and start of the bounding box. The
   * default value is 0, but some sensors do not perceive data within a small
   * distance.
   * @param offset The distance in meters the bounding box should be moved away
   * from the sensor.
   * @return @see Status.h
   */
  virtual scandy::core::Status setBoundingBoxOffset(float offset);

  /**
   * Maximum distance allowed for a depth camera reading. Used during raycast
   *    to remove points above this distance
   * @param threshold Distance in meters.
   * @return @see Status.h
   */
  virtual scandy::core::Status setDistanceThreshold(float threshold);

  /**
   * Set the depth camera orientation in viewport.
   * @param exif_orientation EXIFOrientation of the desired orientation.
   * @return @see Status.h
   */
  virtual scandy::core::Status setDepthCameraEXIFOrientation(scandy::utilities::EXIFOrientation exif_orientation);

  /**
   * Set the color camera orientation in viewport.
   * @param exif_orientation EXIFOrientation of the desired orientation.
   * @return @see Status.h
   */
  virtual scandy::core::Status setColorCameraEXIFOrientation(scandy::utilities::EXIFOrientation exif_orientation);


  /**
   * Toggle per-vertex color integration into the scan.
   * @param enable_color True for color, false for monochrome
   * @return
   */
  virtual scandy::core::Status setEnableColor(bool enable_color);


  // *** Events
  std::function<void(bool createdVisualizer)> onVisualizerReady;
  std::function<void()> onScannerReady;
  std::function<void()> onScannerStart;
  std::function<void()> onScannerStop;
  std::function<void()> onPreviewStart;
  std::function<void()> onPreviewStop;
  std::function<void()> onLoadMesh;
  std::function<void()> onGenerateMesh;
  std::function<void()> onSaveMesh;
  std::function<void()> onFinishedHeadCapture;
  std::function<void(std::string host)> onClientConnected;
  std::function<void(std::string host)> onHostDiscovered;

  /**
   * Bind a listener to trigger on tracking pose and status updates.
   * @param current_pose The most current camera pose.
   * @param is_tracking TRUE if the SLAM algorithm will incorporate the tracking data.
   * @param confidence The confidence of the tracking data. Will always be less
   *        than value set via setTrackingAlignThreshold.
   */
  std::function<void(
    const scandy::utilities::Pose current_pose,
    const bool is_tracking,
    const float confidence)> onTrackingDidUpdate;

  /**
   * Bind a listener to trigger when render preview image is ready.
   * @param img_data RGB image data. (indexed: const uint idx = pos.x + row_size * pos.y;)
   * @param width Width of image_data.
   * @param height Height of image_data.
   * @param frame_metadata Camera pose and intrinsics.
   */
  std::function<void(
    const scandy::utilities::uchar4* img_data,
    const int width,
    const int height,
    const scandy::utilities::DepthTrackMetadata frame_metadata)> onScanPreviewDidUpdate;

  /**
   * Bind a listener to trigger when new point cloud data is ready.
   * @param point_cloud_data Point cloud data.
   * @param width Width of image_data.
   * @param height Height of image_data.
   * @param frame_metadata Camera pose and intrinsics.
   */
  std::function<void(
    const scandy::utilities::float3* point_cloud_data,
    const int width,
    const int height,
    const scandy::utilities::DepthTrackMetadata frame_metadata)> onScanPointCloudDidUpdate;
};

}};

#endif // Scandy_iscandycore_h
