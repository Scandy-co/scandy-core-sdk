/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

#ifndef Scandy_PlatformVisualizer_h
#define Scandy_PlatformVisualizer_h

#include <scandy/core/visualizer/tVisualizerContext.h>

#ifdef SCANDY_QT
#include <scandy/core/visualizer/QtVisualizer.h>
// including Qt breaks compile all over the place
//#include "QVTKInteractor.h"
#endif
#ifdef ANDROID
#include <scandy/core/visualizer/AndroidVisualizer.h>
#endif
#if defined(MACOS) || defined(LINUX)
#include <scandy/core/visualizer/UnixVisualizer.h>
#endif

namespace scandy { namespace core {

#ifdef SCANDY_QT
using PlatformVisualizerContext = scandy::core::tVisualizerContext<vtkRenderWindowInteractor>;
using PlatformVisualizer = scandy::core::QtVisualizer;
#else

#ifdef ANDROID
using PlatformVisualizerContext = scandy::core::tVisualizerContext<vtkAndroidRenderWindowInteractor>;
using PlatformVisualizer = scandy::core::AndroidVisualizer;
#endif

#if defined(MACOS) || defined(LINUX)
using PlatformVisualizerContext = scandy::core::tVisualizerContext<vtkRenderWindowInteractor>;
using PlatformVisualizer = scandy::core::UnixVisualizer;
#endif

#endif

}}

#endif // Scandy_PlatformVisualizer_h
