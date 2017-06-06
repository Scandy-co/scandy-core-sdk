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
 * \file ColorFrame.h
 * \brief Furnishes class for `ColorFrame` and struct for `sColorFrame`.
 */

#ifndef Scandy_ColorFrame_h
#define Scandy_ColorFrame_h

#include <chrono>
#include <vector>

#include <scandy/utilities/vector_types.h>
#include <scandy/utilities/ID_types.h>
#include <scandy/utilities/RGBAPoint.h>
#include <scandy/utilities/DepthTrackMetadata.h>

namespace scandy { namespace utilities {

/**
 * \class ColorFrame
 * \brief Consolidate constituent parts comprising `ColorFrame`, including,
 * without limitation, relative pose, camera intrinsics, point cloud meta-data,
 * analogous intrinsics and analogous meta-data.
 */
class ColorFrame {
public:
  using RGBAPoint = scandy::utilities::RGBAPoint;
  using ColorMetadata = scandy::utilities::DepthTrackMetadata;

public:
    std::vector<RGBAPoint> m_rgba_data;
    std::vector<uchar> m_yuv420_data;
    ColorMetadata m_metadata;
    unsigned int m_texture_id = 0;
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
    uint16_t height
  );
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

  /**
   * Base our metadata on relative pose and an analogous `CameraIntrinsics`.
   * Preconditions:
   * - The intrinsic width and height of this Color Frame are set correctly.
   * - The analogous intrinsic matrix is based on a relative pose
   *   with rotation part equal to EXIF Orientation 1 relative to this frame.
   *   (That is, if the original analogous intrinsics did not have a relative
   *   pose rotation of "no rotation", they have  already been corrected based
   *   on their relative pose).
   * \warning Be careful not to call this more than once if you don't mean to!
   * It will absolutely keep transforming the intrinsics matrix.
   */
  void scaleAndTransformMetadata(scandy::utilities::Pose rel_pose, scandy::utilities::CameraIntrinsics analogous_intrinsics);
  /* As above, but accepts analogous data as DepthTrackMetadata */
  void scaleAndTransformMetadata(scandy::utilities::Pose rel_pose, scandy::utilities::DepthTrackMetadata analogous_metadata);
  /* As above, but uses the ColorFrame's relative pose */
  void scaleAndTransformMetadata(scandy::utilities::CameraIntrinsics analogous_intrinsics);
  void scaleAndTransformMetadata(scandy::utilities::DepthTrackMetadata analogous_metadata);
};

// NOTE: @hcwiley realizes he is breaking convention, but thinks the class
// should be called `ColorFrame` and therefore the struct `sColorFrame`.
/**
 * \struct sColorFrame
 * \brief Define struct for storing type `ColorFrame`.
 */
struct sColorFrame {
  // scandy::utilities::StreamID stream_id;
  // scandy::utilities::CameraID camera_id;
  // uint64_t frame_id;
  ColorFrame color_frame;
};

}}

#endif // Scandy_ColorFrame_h
