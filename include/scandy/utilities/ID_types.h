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

using MetadataUID = std::string;
using SensorID = std::string;
using DeviceID = std::string;

// testing function for generating a uid
// TODO DON'T actually use this!. use the database one and find better solution
// for memory track store
inline void gen_uid(MetadataUID& uid, const int len) {
  char *s = (char *)malloc(sizeof(char)*(len+1));

  static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

  for (int i = 0; i < len; ++i) {
    s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }

    s[len] = 0;

    uid = s;

    free(s);
}

}}

#endif // Scandy_ID_types_h
