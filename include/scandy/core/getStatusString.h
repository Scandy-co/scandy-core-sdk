/****************************************************************************\
 * Copyright (C) 2016-2017 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * For distribution.
\****************************************************************************/

#ifndef Scandy_core_getStatusString_h
#define Scandy_core_getStatusString_h

#include <scandy/core/Status.h>

#include <string>

namespace scandy { namespace core {
    std::string getStatusString (const scandy::core::Status& status);
}}

#endif // Scandy_core_getStatusString_h

