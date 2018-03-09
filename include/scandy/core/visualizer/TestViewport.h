/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_TestViewport_h
#define Scandy_TestViewport_h

#include <scandy/core/Status.h>
#include <scandy/core/visualizer/Viewport.h>

/* Begin VTK includes */
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include "vtkConeSource.h"
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
/* End VTK includes */

/* Begin cpp includes */
#include <string>
/* End cpp includes */

namespace scandy { namespace core {

/**
 * \class TestViewport
 * \brief TestViewport is a subclass of Viewport with the specific purpose of
 * viewing a TestObject.
 */
class TestViewport : public Viewport {
public:
  vtkSmartPointer<vtkPolyData> m_data;
  vtkSmartPointer<vtkPolyDataMapper> m_mapper;
  vtkSmartPointer<vtkActor> m_actor;
public:
  TestViewport();
  virtual void render();
};

}}

#endif // Scandy_TestViewport_h
