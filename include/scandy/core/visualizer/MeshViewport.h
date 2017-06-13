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

#include <scandy/core/status.h>
#include <scandy/core/visualizer/Viewport.h>

/* Begin VTK includes */
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkTexture.h>

#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkSTLReader.h>
#include <vtkJPEGReader.h>
#include <vtkPNGReader.h>

#include <vtksys/SystemTools.hxx>
/* End VTK includes */

/* Begin cpp includes */
#include <string>
/* End cpp includes */

namespace scandy { namespace core {

/**
 * \class MeshViewport
 * \brief MeshViewport is a subclass of Viewport with the specific purpose of
 * viewing meshes.
 */
class MeshViewport : public Viewport {
private:
  bool m_camera_needs_update;
public:
  vtkPolyData *m_data;
  vtkPolyDataMapper *m_mapper;
  vtkActor *m_actor;
public:
  MeshViewport();
  ~MeshViewport();

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

  void setPolyData(vtkPolyData *poly_data);
  void setPolyData(vtkPolyDataAlgorithm *algorithm);

  // xmin, xmax, ymin, ymax, zmin, zmax
  void getBounds(std::vector<double>& bounds);

  virtual void render();
};

}}

#endif // Scandy_MeshViewport_h
