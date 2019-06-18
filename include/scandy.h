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

#ifndef Scandy_scandy_h
#define Scandy_scandy_h

// Top-level scandy include file.

#include <scandy/core/Status.h>

// Define all the modules we are using
#define ENABLE_VTK 1
/* #undef ENABLE_FBX_SDK */
/* #undef ENABLE_OPENCL */
/* #undef ENABLE_ROYALE */
#define ENABLE_SOURCEY 1
/* #undef ENABLE_TANGO */
/* #undef ENABLE_PCL */
/* #undef ENABLE_EXPERIMENTAL */
/* #undef ENABLE_VTK_QT */
#define ENABLE_METAL 1
#define ENABLE_OPENCV 1
/* #undef ENABLE_DLIB */
#define ENABLE_DRACO 1
#define ENABLE_TBB 1
/* #undef ENABLE_ROS */
/* #undef ENABLE_SNAPPY */
/* #undef ENABLE_HIBERLITE */

#define IOS 1
#define APPLE 1
/* #undef ANDROID */
/* #undef LINUX */

namespace scandy { namespace core {
    /*! Scandy library version. */
    Status getVersion (int &major, int &minor, int &patch);
}}

#endif // Scandy_scandy_h
