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

#ifndef Scandy_ToFPointCloud_h
#define Scandy_ToFPointCloud_h

#include <scandy/utilities/PointCloud.h>

namespace scandy { namespace utilities {

/**
 * \brief ToFPointCloud is
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

/** Prepended to the beginning of each serializaed TofPointCloudFrame in a .spb file.
    Not used for network streaming */
struct ToFPointCloudStreamHeader {
  /** Serialization format description.*/
  std::string description;
  /** Number of serialized frames; zero if unknown at serialization time. */
  uint64_t frame_count;
};
/** Used to serialize tof point cloud metadata (like camera position) and the depth sensor plane. 
    Used to serialized data to/from a network stream. */
struct ToFPointCloudFrame {
  ToFPointCloud tof_pointcloud;
};

}}

#endif // Scandy_ToFPointCloud_h
