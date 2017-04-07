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

#include <scandy/core/status.h>

namespace scandy { namespace core {
    /*! Scandy library version. */
    Status getVersion (int &major, int &minor, int &patch);
}}

#endif // Scandy_scandy_h
