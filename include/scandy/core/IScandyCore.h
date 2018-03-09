/****************************************************************************\
 * Copyright (C) 2016 Scandy
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
#include <scandy/core/ScanResolution.h>
#include <scandy/core/visualizer/Visualizer.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

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
  virtual scandy::core::Status uninitializeScanner();

  /**
   * Sets up the image processing workers
   */
  virtual scandy::core::Status initializeImageProcessor();

  /**
  * Starts the processing pipeline that's been configured
  */
  virtual scandy::core::Status start();
  virtual scandy::core::Status stop();

  /**
   * Tells whether the underlying pipeline is running
   */
  virtual bool isRunning();

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


  /**
   * Adds a Viewport to the Visualizer with a 3D object in. Use to test your
   * setup to make the Visualizer is working and receiving interactions.
   * @return @see Status.h
   */
  virtual scandy::core::Status addTestViewport();


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
   * Generate a mesh from current point cloud data as viewed in the visualizer.
   * @return @see Status.h
   */
  virtual scandy::core::Status generateMesh();

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
   * Start the SLAM algorithm.
   * @return @see Status.h
   */
  virtual scandy::core::Status startScanning();

  /**
   * Stop the SLAM algorithm.  Do not continue to record and integrate sensor data.
   * @return @see Status.h
   */
  virtual scandy::core::Status stopScanning();

  // *** Getters

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

  // *** Events
  std::function<void()> onVisualizerReady;
  std::function<void()> onScannerReady;
  std::function<void()> onScannerStart;
  std::function<void()> onScannerStop;
  std::function<void()> onPreviewStart;
  std::function<void()> onPreviewStop;
  std::function<void()> onLoadMesh;
  std::function<void()> onGenerateMesh;
  std::function<void()> onSaveMesh;
  std::function<void()> onFinishedHeadCapture;

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
