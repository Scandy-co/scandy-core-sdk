/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_GLImgViewport_h
#define Scandy_GLImgViewport_h

#include <scandy/core/visualizer/Viewport.h>

#include <vtkSmartPointer.h>
#include <vtkOpenGLTexture.h>
#include <vtkTextureObject.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

namespace scandy { namespace core {

class GLImgViewport : public Viewport {
public:
  int m_calc_width, m_calc_height;
  vtkSmartPointer<vtkOpenGLTexture> m_gl_texture;
  vtkSmartPointer<vtkTextureObject> m_to;
  vtkSmartPointer<vtkPolyDataMapper> m_plane_mapper;
  vtkSmartPointer<vtkActor> m_textured_plane;
  vtkSmartPointer<vtkOpenGLRenderWindow> m_renWin;
public:
  GLImgViewport();
  ~GLImgViewport();
protected:
  bool setupGLTexture(int width=0, int height=0);
};

}}

#endif // Scandy_GLImgViewport_h
