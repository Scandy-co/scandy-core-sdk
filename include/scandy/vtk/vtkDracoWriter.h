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
 * \file vtkDracoWriter.h
 * \brief Writes a vtkPolyData to a .glb file
 */

#ifndef Scandy_vtkDracoWriter_h
#define Scandy_vtkDracoWriter_h

#include <string>

#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkImageData;

namespace scandy { namespace utilities {

class vtkDracoWriter {
public:
  // the mesh to convert
  vtkSmartPointer<vtkPolyData> m_polydata;

  // the texture image to write to the glb. is nullptr if using per-vertex colors
  vtkSmartPointer<vtkImageData> m_tex_img;

  // the .glb file path to write to
  std::string m_file_path;

  // true if mesh is texture mapped, false if it has per-vertex colors
  bool m_use_texturing = false;

  // depending on the platform, we may have to use float4 for color (i.e. sketchfab, facebook)
  // if false, uses float4 for rgba colors
  bool m_use_uchar4_color = false;

  // when true, flips the mesh so that the z-direction matches most external views.
  bool m_reorient_mesh = true;


public:
  // constructor that gets all the info at once
  vtkDracoWriter(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data, vtkSmartPointer<vtkImageData> tex_img = nullptr);

  // executes the write to file once all the data is set
  bool write();
};

}}

#endif // Scandy_vtkDracoWriter_h
