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

#ifndef Scandy_ScannerType_h
#define Scandy_ScannerType_h

namespace scandy { namespace core {
    enum class ScannerType
    {
      UNKNOWN=0,
      FILE=1,
      PICO_FLEXX=2,
      TANGO=3,
      OPENNI2=4,
      NETWORK=5,
      DS541=6,
      TRUE_DEPTH=7,
      DUAL_CAMERA=8
    };
}}

#endif // Scandy_ScannerType_h
