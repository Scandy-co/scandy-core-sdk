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

#ifndef Scandy_royale_utils_h
#define Scandy_royale_utils_h

#include <scandy/core/Status.h>

#include <royale/Status.hpp>


namespace scandy { namespace core {
    /*! Convert royale::CameraStatus to scandy::core::Status. */
    scandy::core::Status royaleCameraStatus2ScandyCoreStatus(const royale::CameraStatus& royale_status);
}}

#endif // Scandy_royale_utils_h
