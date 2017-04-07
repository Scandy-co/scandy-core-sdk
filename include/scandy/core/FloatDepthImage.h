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

#ifndef Scandy_FloatDepthImage_h
#define Scandy_FloatDepthImage_h

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>


namespace scandy { namespace core {

/**
 * An image whose pixel intensity indicates floating-point distance to the
 * imaged surface.
 */
class FloatDepthImage {
/* FIXME@kaben: Make protected or private ASAP. */
public:
  std::chrono::microseconds m_timestamp;
  int m_width;
  int m_height;
  /** Vector of depth pixels; should have size m_width x m_height. */
  std::vector<float> m_data;
public:
  FloatDepthImage(int width, int height);
  FloatDepthImage();
  /**
   * This constructor is for braced initialization, primarily for testing
   * purposes in order to make mocked depth image streams.
   *
   * Example use (for a 224x171 depth image with timestamp 1469460882342000LL):
   * ```cpp
   * FloatDepthImage img{std::chrono::microseconds(1469460882342000LL), 224, 171, std::vector<float>({
   *   0, 0, 0, 0, 0, 0, 0, 0, 0
   * , 0, 0, 0, 0, 0, 0, 0, 0
   * , 0, 0, 0, 0, 0, 0, 0, 0
   * , 0.301446, 0, 0.360464, 0.357918, 0.307232, 0.362846, 0.300143, 0.314577
   * , 0.307779, 0.36395, 0.342863, 0.342541, 0.326838, 0.314929, 0.338804, 0.324472
   * , 0.35531, 0.339515, 0.307949, 0.32575, 0.327233, 0, 0, 0
   * ...
   * , 0.752741, 0, 0, 0.16693, 0.172288, 0, 0, 0.891401
   * , 0, 0, 0, 0, 0, 0, 0, 0
   * , 0, 0, 0, 0, 0, 0, 0, 0
   * , 0, 0, 0, 0, 0, 0, 0
   * })};
   * ```
   */
  FloatDepthImage(
    std::chrono::microseconds timestamp,
    int width,
    int height,
    std::vector<float>&& depths
  );
  void resize(int width, int height);
  void describe(const char* reporter, std::ostream& out);
};

}}

#endif // Scandy_FloatDepthImage_h
