/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_ImgViewport_h
#define Scandy_ImgViewport_h

#include <scandy/core/Status.h>
#include <scandy/core/visualizer/Viewport.h>

/* Begin VTK includes */
#include <vtkSmartPointer.h>
#include <vtkActor2D.h>
#include <vtkImageData.h>
#include <vtkImageMapper.h>
#include <vtkImageReslice.h>
#include <vtkTransform.h>
#include <vtkImageImport.h>

namespace scandy { namespace core {

class ImgViewport : public Viewport {
public:
  vtkSmartPointer<vtkImageData> m_img;
  vtkSmartPointer<vtkImageImport> m_img_import;
  vtkSmartPointer<vtkTransform> m_transform;
  vtkSmartPointer<vtkImageReslice> m_reslice;
  vtkSmartPointer<vtkImageMapper> m_mapper;
  vtkSmartPointer<vtkActor2D> m_actor;
public:
  ImgViewport();
public:
  void resizeAndRotate(int input_width, int input_height, scandy::utilities::Mat4f rel_pose);
};

}}

#endif // Scandy_ImgViewport_h
