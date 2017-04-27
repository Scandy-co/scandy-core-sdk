/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_VisualizerContext_h
#define Scandy_VisualizerContext_h

#include <scandy/core/visualizer/GridPositions.h>

/* Begin VTK includes */
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyle.h>

#ifdef ANDROID
#include "vtkAndroidRenderWindowInteractor.h"
#endif

#if defined(MACOS) || defined(LINUX)
#include <vtkRenderWindowInteractor.h>
#endif
/* End VTK includes */

namespace scandy { namespace core {

/**
 * \class VisualizerContext
 * \brief VisualizerContext is a class that holds various VTK components needed
 * to by Scandy Core to visualize. It is the "context" with which the visualizer
 * operates.
 */
class VisualizerContext {
protected:
  scandy::core::GridPositions m_grid_positions;

  /* m_renwin is allocated in VisualizerContext constructor, so must be
   * deallocated in destructor.
   */
  std::vector<vtkRenderer*> m_renderers;

  bool m_external_win = false;
  vtkRenderWindow* m_renwin = nullptr;

  /* m_interactor is expected to allocated before constructor is called. The
   * destructor should not deallocate.
   * The constructor sets the interactors render window.
   */
#ifdef ANDROID
  vtkAndroidRenderWindowInteractor* m_interactor = nullptr;
#endif

#if defined(MACOS) || defined(LINUX)
  vtkRenderWindowInteractor* m_interactor = nullptr;
#endif

public:
  VisualizerContext(
    int width,
    int height,
    int cols,
    int rows,
    vtkRenderWindow* vtkWindow = NULL
  );

  VisualizerContext(
#ifdef ANDROID
    vtkAndroidRenderWindowInteractor* i,
#endif
#if defined(MACOS) || defined(LINUX)
    vtkRenderWindowInteractor* i,
#endif
    int width,
    int height,
    int cols,
    int rows,
    vtkRenderWindow* vtkWindow = NULL
  );

  ~VisualizerContext();

  void setInteractorStyle(vtkInteractorStyle *interactor_style);

#ifdef ANDROID
  vtkAndroidRenderWindowInteractor* interactor();
#endif

#if defined(MACOS) || defined(LINUX)
  vtkRenderWindowInteractor* interactor();
#endif


  /* Note that this class doesn't directly track the added renderers. They are
   * however available via renwin()->GetRenderers().
   */
  void addRenderer(vtkRenderer* renderer, int idx = -1);

  vtkRenderWindow* renwin();
  std::vector<vtkRenderer*>& renderers();
  virtual void render();
  void clear();
  void close();
};

}}

#endif // Scandy_VisualizerContext_h
