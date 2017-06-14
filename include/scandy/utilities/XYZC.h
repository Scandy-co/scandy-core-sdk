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
 * \file XYZC.h
 * \brief Furnishes a class for `XYZC`.
 */

#ifndef Scandy_XYZC_h
#define Scandy_XYZC_h

#include <royale/DepthData.hpp>

#include <hiberlite.h>

namespace scandy { namespace utilities {

/**
 * \class XYZC
 * \brief A class that represents an individual point in a point cloud.
 */
class XYZC {
public:
  // The x value of the point. Assumed to be in meters
  float x;
  // The y value of the point. Assumed to be in meters
  float y;
  // The z value of the point. Assumed to be in meters
  float z;
  // The noise of the point. Assumbed to be in meters
  float noise;
  // The confidence of the point. 0 - 255, low to high
  uint8_t confidence;
  // The gray scale color of the point
  uint16_t gray_value;

  XYZC() = default;
  XYZC(const XYZC& p) = default;
  XYZC(const royale::DepthPoint& p);

  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(x);
    ar & HIBERLITE_NVP(y);
    ar & HIBERLITE_NVP(z);
    ar & HIBERLITE_NVP(noise);
    ar & HIBERLITE_NVP(confidence);
    ar & HIBERLITE_NVP(gray_value);
  }
};

}}

#endif // Scandy_XYZC_h
