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

#ifndef Scandy_FloatPointCloud_h
#define Scandy_FloatPointCloud_h

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>


namespace scandy { namespace core {

struct FloatPoint3D{
public:
  float x;
  float y;
  float z;
};

/**
 * A point cloud
 */
class FloatPointCloud {
/* FIXME@kaben: Make protected or private ASAP. */
public:
  std::chrono::microseconds m_timestamp;
  int m_width;
  int m_height;
  /** Vector of FloatPoint3D (x, y, z) */
  std::vector<FloatPoint3D> m_data;
public:
  FloatPointCloud(int width, int height);
  FloatPointCloud();
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
  FloatPointCloud(
    std::chrono::microseconds timestamp,
    int width,
    int height,
    std::vector<FloatPoint3D>&& points
  );

  void resize(int width, int height);
  void describe(const char* reporter, std::ostream& out);
};

}}

#endif // Scandy_FloatPointCloud_h
