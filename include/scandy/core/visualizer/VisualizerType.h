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

#ifndef Scandy_VisualizerType_h
#define Scandy_VisualizerType_h

namespace scandy { namespace core {
    enum class VisualizerType
    {
      AUTO,
      SCANDYCORE,
#if defined(IOS) || defined(APPLE)
      SCENEKIT,
#endif
    };
}}

#endif // Scandy_VisualizerType_h
