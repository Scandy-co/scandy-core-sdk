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

#ifndef Scandy_PointCloud_h
#define Scandy_PointCloud_h

#include <scandy/utilities/PointCloudMetaData.h>
#include <scandy/utilities/XYZC.h>

#include <royale/DepthData.hpp>

#include <vector>

namespace scandy { namespace utilities {

/**
 * \brief PointCloud represents a collection of points and their metadata.
 */
class PointCloud {
public:
  PointCloudMetaData m_metadata;
  std::vector<XYZC> m_points;
public:
  PointCloud() = default;
  PointCloud(const PointCloud&) = default;
  PointCloud(PointCloud&&) = default;
  PointCloud& operator=(const PointCloud&) = default;
  PointCloud& operator=(PointCloud&) = default;
  PointCloud& operator=(PointCloud&&) = default;
  PointCloud(
    int version,
    std::chrono::microseconds timestamp,
    uint16_t width,
    uint16_t height,
    const royale::Vector<royale::DepthPoint>& points
  );

public:
  void setVersion(int version);
  void setTimeStamp(std::chrono::microseconds timestamp);
  void setPoints(
    uint16_t width,
    uint16_t height,
    const royale::Vector<royale::DepthPoint>& points
  );
  int version();
  uint64_t timestamp();
  uint16_t width();
  uint16_t height();
  std::vector<XYZC>& points(){
    return m_points;
  }
  PointCloudMetaData metadata(){ return m_metadata; }
};

struct PointCloudFrame {
  StreamID stream_id;
  CameraID camera_id;
  uint64_t frame_id;
  PointCloud pointcloud;
};

}}

#endif // Scandy_PointCloud_h