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

/**
 * \file ID_types.h
 */

#ifndef Scandy_ID_types_h
#define Scandy_ID_types_h

#include <string>
#include <cstdlib>

namespace scandy { namespace utilities {

using CameraID = std::string;
using StreamID = std::string;

using MetadataUID = uint32_t;
using SensorID = std::string;
using DeviceID = std::string;
}}

#endif // Scandy_ID_types_h
