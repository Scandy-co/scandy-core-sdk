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
 * \file ToFPointCloud.h
 * \brief Furnishes class for `ToFPointCloud` and structs for
 * `ToFPointCloudStreamHeader` and `ToFPointCloudFrame`.
 */

#ifndef Scandy_ToFPointCloud_h
#define Scandy_ToFPointCloud_h

#include <scandy/utilities/PointCloud.h>

namespace scandy { namespace utilities {

/**
 * \class ToFPointCloud
 * \brief Furnishes an implementation of `PointCloud` specific to time-of-flight.
 */
class ToFPointCloud : public PointCloud {
public:
  std::vector<uint32_t> m_exposure_times;
public:
  ToFPointCloud() = default;
  ToFPointCloud(const ToFPointCloud&) = default;
  ToFPointCloud(ToFPointCloud&&) = default;
  ToFPointCloud(const royale::DepthData&);
  ToFPointCloud& operator=(const ToFPointCloud&) = default;
  ToFPointCloud& operator=(ToFPointCloud&) = default;
  ToFPointCloud& operator=(const royale::DepthData&);
public:
  std::vector<uint32_t>& exposureTimes();
};

/**
 * \struct ToFPointCloudStreamHeader
 * \brief Furnishes a header, to be prepended to each `ToFPointCloudFrame` in an
 * `.spb` file.
 * \warning Not to be used for network streaming.
 */
struct ToFPointCloudStreamHeader {
  /** Serialization format description.*/
  std::string description;
  /** Number of serialized frames; zero if unknown at serialization time. */
  uint64_t frame_count;
};

/**
 * \struct ToFPointCloudFrame
 * \brief Used to serialize time-of-flight point cloud metadata (such as camera
 * position) and the depth sensor plane.
 * Used to serialized data to/from a network stream
 */
struct ToFPointCloudFrame {
  ToFPointCloud tof_pointcloud;
};

}}

#endif // Scandy_ToFPointCloud_h
