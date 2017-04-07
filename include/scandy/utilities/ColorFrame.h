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

#ifndef Scandy_ColorFrame_h
#define Scandy_ColorFrame_h

#include <chrono>
#include <vector>

#include <scandy/utilities/vector_types.h>
#include <scandy/utilities/ID_types.h>
#include <scandy/utilities/RGBAPoint.h>
#include <scandy/utilities/PointCloudMetaData.h>

namespace scandy { namespace utilities {

/**
 * \brief ColorFrame is
 */
class ColorFrame {
public:
  using RGBAPoint = scandy::utilities::RGBAPoint;
  using ColorMetaData = scandy::utilities::PointCloudMetaData;

public:
    std::vector<RGBAPoint> m_rgba_data;
    ColorMetaData m_metadata;
public:
  ColorFrame() = default;
  ColorFrame(const ColorFrame&) = default;
  ColorFrame(ColorFrame&&) = default;
  ColorFrame& operator=(const ColorFrame&) = default;
  ColorFrame& operator=(ColorFrame&) = default;
  ColorFrame(
    int version,
    std::chrono::microseconds timestamp,
    uint16_t width,
    uint16_t height,
    std::vector<RGBAPoint> rgba_data
  );
public:
  void setVersion(int version);
  void setTimeStamp(std::chrono::microseconds timestamp);

  /*
   * Base our metadata on relative pose and and an analogous CameraIntrinsics
   * Preconditions:
   * - The intrinsic width and height of this Color Frame are set correctly.
   * - The analogous intrinsic matrix is based on a relative pose
   *   with rotation part equal to EXIF Orientation 1 relative to this frame.
   *   (That is, if the original analogous intrinsics did not have a relative pose rotation of
   *    "no rotation", they have  already been corrected based on their relative pose.)
   * WARNING: Be careful not to call this more than once if you don't mean to!
   * It will absolutely keep transforming the intrinsics matrix.
   */
  void scaleAndTransformMetadata(scandy::utilities::RelativePose rel_pose, scandy::utilities::CameraIntrinsics analogous_intrinsics);
  /* As above, but accepts analogous data as PointCloudMetaData */
  void scaleAndTransformMetadata(scandy::utilities::RelativePose rel_pose, scandy::utilities::PointCloudMetaData analogous_metadata);
  /* As above, but uses the ColorFrame's relative pose */
  void scaleAndTransformMetadata(scandy::utilities::CameraIntrinsics analogous_intrinsics);
  void scaleAndTransformMetadata(scandy::utilities::PointCloudMetaData analogous_metadata);
};

// NOTE: @hcwiley realizes he is breaking conviction, but think the class should
// be called ColorFrame and therefore the struct sColorFrame
struct sColorFrame {
  // scandy::utilities::StreamID stream_id;
  // scandy::utilities::CameraID camera_id;
  // uint64_t frame_id;
  ColorFrame color_frame;
};

}}

#endif // Scandy_ToFPointCloud_h
