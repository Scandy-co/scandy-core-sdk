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
 * \file PointCloud.h
 * \brief Furnishes class for `PointCloud` and struct for `PointCloudFrame`.
 */

#ifndef Scandy_PointCloud_h
#define Scandy_PointCloud_h

#include <scandy/utilities/DepthTrackMetaData.h>
#include <scandy/utilities/XYZC.h>

#include <royale/DepthData.hpp>

#ifdef ENABLE_EXPERIMENTAL
#include <hiberlite.h>
#endif

#include <vector>

namespace scandy { namespace utilities {

/**
 * \class PointCloud
 * \brief `PointCloud` represents a collection of points and their metadata.
 */
class PointCloud {
public:
  DepthTrackMetaData m_metadata;
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
  DepthTrackMetaData metadata(){ return m_metadata; }

#ifdef ENABLE_EXPERIMENTAL
  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(m_points);
  }
#endif
};

/**
 * \struct PointCloudFrame
 * \brief Packages `PointCloud` data with identifiers specific to its stream,
 * camera, and frame.
 */
struct PointCloudFrame {
  StreamID stream_id;
  CameraID camera_id;
  uint64_t frame_id;
  PointCloud pointcloud;

#ifdef ENABLE_EXPERIMENTAL
  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(stream_id);
    ar & HIBERLITE_NVP(camera_id);
    ar & HIBERLITE_NVP(frame_id);
    ar & HIBERLITE_NVP(pointcloud);
  }
#endif
};

}}

#endif // Scandy_PointCloud_h
