/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_MeshViewport_h
#define Scandy_MeshViewport_h

#include <scandy/core/Status.h>
#include <scandy/core/visualizer/Viewport.h>


#if ENABLE_EXPERIMENTAL
#include <scandy/utilities/MeshFrame.h>
#include <scandy/core/tChannel.h>
#endif

/* Begin VTK includes */
#include <vtkSmartPointer.h>
#include <vtkActor.h>
// #include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkLight.h>

// Forward declare these so we don't get our clients into trouble
class vtkClipPolyData;
class vtkPlane;
class vtkPlaneSource;
class vtkPolyDataAlgorithm;
class vtkPointSetAlgorithm;
class vtkPolyData;
/* End VTK includes */

/* Begin cpp includes */
#include <string>
/* End cpp includes */

namespace scandy { namespace core {

class MeshRotateInteractorStyle;

/**
 * \class MeshViewport
 * \brief MeshViewport is a subclass of Viewport with the specific purpose of
 * viewing meshes.
 */
class MeshViewport : public Viewport {
private:
  bool m_camera_needs_update;
  bool m_enable_cropping_plane;
  bool m_added_interator;
  bool m_rotate_mesh;
public:
#if ENABLE_EXPERIMENTAL
  using MeshFrameChannel = scandy::internal::core::tChannel<scandy::utilities::MeshFrame>;
  using MeshFrameChannelPointer = std::shared_ptr<MeshFrameChannel>;
  MeshFrameChannelPointer m_ch;
#endif
  vtkSmartPointer<vtkPolyData> m_data;
  vtkSmartPointer<vtkPolyDataMapper> m_mapper;
  vtkSmartPointer<vtkActor> m_actor;
  vtkSmartPointer<vtkLight> m_light;
  vtkSmartPointer<vtkClipPolyData> m_clipper;
  vtkSmartPointer<vtkPlane> m_clip_plane;
  vtkSmartPointer<vtkPlaneSource> m_plane_source;
  vtkSmartPointer<vtkPolyDataMapper> m_plane_mapper;
  vtkSmartPointer<vtkActor> m_plane_actor;
  vtkSmartPointer<MeshRotateInteractorStyle> m_interactor_style;
  bool m_added_light;
  bool m_color_enabled;
  bool m_color_lighting;
public:
  MeshViewport();
  ~MeshViewport();

  bool getEnableCroppingPlane();
  scandy::core::Status setEnableCroppingPlane(bool enable_cropping);
  scandy::core::Status setCroppingPlaneNormal(float x, float y, float z);
  scandy::utilities::float3 getCroppingPlaneNormal();
  scandy::core::Status setCroppingPlanePosition(float x, float y, float z);
  scandy::utilities::float3 getCroppingPlanePosition();
  scandy::core::Status applyCrop();


  scandy::core::Status setEnableWireframe(bool enable_wireframe);
  /**
   * loadMesh Loads a mesh file from the local disk. Puts loaded data into
   * vtkPolyData object to be visualized.
   * @param  file_path    Absolute path to the mesh file to be loaded
   * @param  texture_path Optional absolute path to the texture file to be
   * loaded and mapped on the mesh
   * @return              Should return scandy::core::Status::SUCCESS. If it
   * does not, there was an error with the loading.
   */
  scandy::core::Status loadMesh(std::string filename, std::string texture_path="");

  void setPolyData(vtkSmartPointer<vtkPolyData> poly_data, bool camera_needs_update=true);
  void setPolyData(vtkSmartPointer<vtkPolyDataAlgorithm> algorithm);
  void setPolyData(vtkSmartPointer<vtkPointSetAlgorithm> algorithm);

  void setEnableMeshColor(bool enable_mesh_color);
  void setEnableLightingForColor();
  void setEnableLightingForColor(bool color_lighting);

  void setLightTransformationMat(scandy::utilities::Mat4f mat);

  // xmin, xmax, ymin, ymax, zmin, zmax
  scandy::utilities::float8 getBounds();

  // changes render lighting based on color or absence of it
  bool hasColor();

  virtual void render();
};

}}

#endif // Scandy_MeshViewport_h
