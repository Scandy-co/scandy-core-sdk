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

#if ENABLE_ROYALE
#include <royale/DepthData.hpp>
#endif //#if ENABLE_ROYALE

#if ENABLE_HIBERLITE
#include <hiberlite.h>
#endif

#if !IS_A_CL_HEADER_STRING
#include <stdint.h>
#endif //endif !IS_A_CL_HEADER_STRING

#if !IS_A_CL_HEADER_STRING
namespace scandy { namespace utilities {
#endif //endif !IS_A_CL_HEADER_STRING
/**
 * \class XYZC
 * \brief A class that represents an individual point in a point cloud.
 */
#if IS_A_CL_HEADER_STRING
struct sXYZC {
#else
class XYZC {
public:
#endif //endif IS_A_CL_HEADER_STRING
  // The x value of the point. Assumed to be in meters
  float x;
  // The y value of the point. Assumed to be in meters
  float y;
  // The z value of the point. Assumed to be in meters
  float z;
  // The noise of the point. Assumbed to be in meters
  float noise;
  // The confidence of the point. 0 - 255, low to high
  unsigned char confidence;
  // The gray scale color of the point
  unsigned int gray_value;
#if IS_A_CL_HEADER_STRING
};
#else
  XYZC() = default;
  XYZC(const XYZC& p) = default;
#if ENABLE_ROYALE
  XYZC(const royale::DepthPoint& p);
#endif //#if ENABLE_ROYALE

#if ENABLE_HIBERLITE
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
#endif
};

struct sXYZC {
  XYZC point;
};
#endif //endif IS_A_CL_HEADER_STRING

#if !IS_A_CL_HEADER_STRING
}}
#endif //endif !IS_A_CL_HEADER_STRING

#endif // Scandy_XYZC_h
