/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_QtVisualizer_h
#define Scandy_QtVisualizer_h

#include <scandy/core/visualizer/Visualizer.h>
//#include <scandy/core/visualizer/VisualizerContext.h>
//#include <scandy/core/visualizer/VisualizerStopThread.h>
//#include <scandy/core/visualizer/VisualizerWakeCommand.h>


namespace scandy { namespace core {

class QtVisualizer : public Visualizer {
public:
  unsigned long m_duration = 30;
public:
  QtVisualizer(
    VisualizerContext& viz_ctxt,
    unsigned long ms = 30
  );
  virtual ~QtVisualizer();
public:
  void start();
  void stop();
  void join();
};

}}

#endif // Scandy_QtVisualizer_h
