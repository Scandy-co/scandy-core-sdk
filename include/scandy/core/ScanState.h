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

#ifndef Scandy_ScanState_h
#define Scandy_ScanState_h

namespace scandy { namespace core {
    enum class ScanState
    {
      NONE,
      INITIALIZED,
      PREVIEWING,
      SCANNING,
      STOPPED,
      MESHING,
      VIEWING
    };
}}

#endif // Scandy_ScanState_h
