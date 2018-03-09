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
 * \file MeshFrame.h
 * \brief Furnishes class for `MeshFrame` and struct for `sMeshFrame`.
 */

#ifndef Scandy_MeshFrame_h
#define Scandy_MeshFrame_h

#include <scandy/utilities/DepthTrackMetadata.h>
#include <vtkPolyData.h>

namespace scandy { namespace utilities {

class MeshFrame{
public:
  vtkPolyData* m_vtk_polydata;
  scandy::utilities::DepthTrackMetadata m_metadata;
  MeshFrame(){
    m_vtk_polydata = vtkPolyData::New();
  }
  ~MeshFrame(){
    m_vtk_polydata->Delete();
  }
};

// NOTE: @hcwiley realizes he is breaking convention, but thinks the class
// should be called `MeshFrame` and therefore the struct `sMeshFrame`.
/**
 * \struct sMeshFrame
 * \brief Define struct for storing type `MeshFrame`.
 */
struct sMeshFrame {
  // scandy::utilities::SensorID sensor_id;
  // scandy::utilities::DeviceID device_id;
  // uint64_t frame_id;
  MeshFrame mesh_frame;
};

}}

#endif // Scandy_MeshFrame_h
