/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_Viewport_h
#define Scandy_Viewport_h

#include <scandy/utilities/CameraIntrinsics.h>

/* Begin VTK includes */
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkMatrix4x4.h>
#include <vtkSmartPointer.h>
/* End VTK includes */

/* Begin cpp includes */
#include <cmath>
/* End cpp includes */


namespace scandy { namespace core {

/**
 * \class Viewport
 * \brief Viewport is the abstract base class for visualizing a specific piece
 * of data with ScandyCore. You must use the subclass for the type of data you
 * you wish to view.
 */
class Viewport {
protected:
  vtkRenderer *m_renderer;
  /* Camera position, view-up, and focus. */
  double m_cx, m_cy, m_cz, m_vx, m_vy, m_vz, m_lx, m_ly, m_lz;
public:
  Viewport();
  virtual ~Viewport();
public:
  void setCameraIntrinsics(const scandy::utilities::CameraIntrinsics &k);
  /* FIXME (@kaben): super-ugly. */
  void setCameraExtrinsics(
    double e00, double e01, double e02, double e03,
    double e10, double e11, double e12, double e13,
    double e20, double e21, double e22, double e23,
    double e30, double e31, double e32, double e33
  );
  /* The next two methods check to see whether the user has changed the
   * camera position or orientation by interacting with VTK, and if so,
   * displays info about the camera pose. This is useful for choosing a
   * good pose to use when initializing the camera.
   */
  vtkRenderer* renderer();
  double getMaxResizeFactor(int original_width, int original_height);
  bool didCameraPoseChange();
  void updateCameraPose();
  void checkCameraPose();
  void reportCameraPose();
  /* Subclass implement this method to render VTK visualizations. */
  virtual void render();
};

}}

#endif // Scandy_Viewport_h
