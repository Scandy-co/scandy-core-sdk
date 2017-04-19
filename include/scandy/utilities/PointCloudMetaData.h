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
 * \file PointCloudMetaData.h
 * \brief Furnishes struct for `PointCloudMetaData`.
 */

// TODO: from @hcwiley
// -refactor this struct be "CameraFrameMetaData"

#ifndef Scandy_PointCloudMetaData_h
#define Scandy_PointCloudMetaData_h

#include <scandy/utilities/Pose.h>
#include <scandy/utilities/ID_types.h>
#include <scandy/utilities/RelativePose.h>
#include <scandy/utilities/CameraIntrinsics.h>

namespace scandy { namespace utilities {

  /**
   * \brief `PointCloudMetaData` describes necessary additional information for
   * using a `PointCloud`.
   */
  struct PointCloudMetaData {
    // The version for a PointCloud
    int version;
    // The relative frame for a PointCloud
    uint64_t frame_id;
    // The timestamp for a PointCloud
    uint64_t timestamp;
    /**
     * "units" per meters; e.g., for mm, set unit_conversion to 1000.
     * For unknown units, or if not applicable, set to zero.
     */
    double unit_conversion;
    // The intrinsics for camera that captured a point cloud
    scandy::utilities::CameraIntrinsics intrinsics;
    // The computed Pose of the camera that captured a PointCloud
    Pose computed_pose;
    // The RelativePose of the camera that captured a PointCloud
    RelativePose relative_pose;
    // The StreamID of the stream that captured a PointCloud
    StreamID stream_id;
    // The CameraID of the camera that captured a PointCloud
    CameraID camera_id;
  };

}}

#endif // Scandy_PointCloudMetaData_h
