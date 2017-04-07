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

#include <scandy/core/status.h>
#include <scandy/core/visualizer/Viewport.h>

/* Begin VTK includes */
#include <vtkSmartPointer.h>
#include <vtkActor2D.h>
#include <vtkImageData.h>
#include <vtkImageFlip.h>
#include <vtkImageMapper.h>
#include <vtkImageResize.h>
#include <vtkTransform.h>

namespace scandy { namespace core {

class ImgViewport : public Viewport {
public:
  float m_zoom;
  vtkImageData *m_img;
  vtkTransform *m_transform;
  vtkImageResize *m_resize;
  vtkImageMapper *m_mapper;
  vtkActor2D *m_actor;
public:
  ImgViewport();
  ~ImgViewport();
};

}}

#endif // Scandy_ImgViewport_h
