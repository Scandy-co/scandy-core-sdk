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

#ifndef Scandy_ScanResolution_h
#define Scandy_ScanResolution_h

#include <string>
#include <scandy/utilities/vector_types.h>

namespace scandy { namespace core {
  class ScanResolution {
  public:
    std::string description;
    scandy::utilities::uint id;
    scandy::utilities::uint4 resolution;
  public:
    ScanResolution(){
      description = "";
      id = 0;
      resolution = {{0,0,0,0}};
    }
  };
}}

#endif // Scandy_ScanResolution_h
