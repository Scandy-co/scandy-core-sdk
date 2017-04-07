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
      FILE,
      TANGO,
      PICO_FLEXX,  
      NETWORK
    };
}}

#endif // Scandy_ScannerType_h
