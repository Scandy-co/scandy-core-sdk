/****************************************************************************\
 * Copyright (C) 2015-2019 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * For distribution.
\****************************************************************************/

#ifndef Scandy_core_ScanState_h
#define Scandy_core_ScanState_h

#include <string>

namespace scandy { namespace core {
    enum class ScanState
    {
      NONE,
      PENDING,
      INITIALIZED,
      PREVIEWING,
      SCANNING,
      STOPPED,
      MESHING,
      VIEWING
    };

    std::string getScanStateString(const scandy::core::ScanState& state);
}}

#endif // Scandy_core_ScanState_h
