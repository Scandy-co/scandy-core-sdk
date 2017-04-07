/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_Visualizer_h
#define Scandy_Visualizer_h

#include <scandy/core/visualizer/VisualizerContext.h>
#include <scandy/core/visualizer/Viewport.h>

namespace scandy { namespace core {

/**
 * \class Visualizer
 * \brief Visualizer is the abstract base class for visualizing data with
 * ScandyCore.
 *
 * <B>You must use the subclass (currently AndroidVisualizer or UnixVisualizer) for the operating system you wish to
 * run on.</B>
 *
 * A Visualizer connects a VisualizerContext and Viewport together, and adds the
 * renderers from all the Viewports to the VisualizerContext
 */
class Visualizer {
public:
  VisualizerContext& m_viz_ctxt;
  std::vector<Viewport*> m_viewports;
public:
  Visualizer(VisualizerContext& viz_ctxt);
  virtual ~Visualizer();
public:
  /**
   * addViewport Adds a new Viewport to the m_viewports std::vector and adds the
   * renderer from the Viewport to the VisualizerContext
   * @param viewport The Viewport to be added
   */
  void addViewport(Viewport& viewport);
  /**
   * clear Clears the m_viewports and m_viz_ctxt
   */
  void clear();
  void start();
  void stop();
  void join();

};

}}

#endif // Scandy_Visualizer_h
