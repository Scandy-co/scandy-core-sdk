/****************************************************************************\
 * Copyright (C) 2018 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

#ifndef Scandy_IScandyCoreConfiguration_h
#define Scandy_IScandyCoreConfiguration_h

#include <scandy/utilities/CameraIntrinsics.h>
#include <scandy/utilities/RelativePose.h>

#include <string>

namespace scandy { namespace core {
/**
 * Interface for interacting with configuration that defines the SLAM context.
 * Get the IScandyCoreConfiguration shared_ptr from IScandyCore
 */
class IScandyCoreConfiguration {
protected:
  std::vector<std::string> m_discovered_hosts;
public:
  /* CameraIntrinsics for the Depth Camera */
  scandy::utilities::CameraIntrinsics m_depth_camera_intrinsics;
  /* The Relative Pose for the Depth Camera */
  scandy::utilities::RelativePose m_depth_camera_relative_pose;
  /* CameraIntrinsics for the Color Camera */
  scandy::utilities::CameraIntrinsics m_color_camera_intrinsics;
  /* The Relative Pose for the Color Camera */
  scandy::utilities::RelativePose m_color_camera_relative_pose;
  /* Intrinsics for the virtual "model" camera used to render the TSDF. */
  scandy::utilities::CameraIntrinsics m_model_camera_intrinsics;

  /**
   * Adjust how close neighboring depth pixels must be for a pixel to be
   * considered valid. 0.0 would result in none of the pixels being valid.
   * The range of 0.005 - 0.01 is most reasonable and effective.
   *
   * This filter is highly dependent on the type of depth sensor. For instance
   * this filter has very little effect on structured light sensors.
   */
  float m_valid_depth_distance_ratio_thresh;

  /**
   * How many neighbors must be valid within the
   * m_valid_depth_distance_ratio_thresh for the pixel to be valid
   */
  short m_valid_depth_neighbor_count_thresh;

  /**
   * Adjust how connective or elastic the surface of the TSDF is.
   * The default value is 0.02 and is good for most use cases.
   * A value of 0.004 would result is a very splattered or not connected surface
   */
  float m_tsdf_mu_ratio;

  /**
   * Adjust how well aligned the camera needs to be with the model for
   * tracking and integration of new data to take place.
   * The default value is 0.8 and is good for most use cases.
   * Normal threshold should be between 0.0 - 1.0, with lower values being
   * more flexible.
   */
  float m_normal_threshold;

  /**
  * Adjust how well aligned the camera needs to be with the model for
  * tracking and integration of new data to take place.
  * The default value is 0.2 and is good for most use cases.
  * Distance threshold should be between 0.0 - 1.0, with higher values being
  * more flexible.
   */
  float m_dist_threshold;

  /**
   * Adjust how long it takes for the TSDF to go from uncertain (yellow)
   * to established (white).
   * The default value is 10 and is good for must uses cases.
   * 0 will cause the TSDF to go white immediately, whereas values over 20 will
   * result in a model that very open to change and resetting.
   */
  float m_tsdf_valid_weight_thresh;

  /**
   * Adjust how many samples make up section of the TSDF, how long it takes to
   * transition from established (white) to locked (green).
   * The default value is 100 and is good for most use cases. The minimum value
   * of 1 will cause the TSDF to constatly overwrite itself.
   */
  float m_tsdf_max_weight;

  /**
   * Adjust how certain the tracking output must be to have valid tracking.
   * Default value of 1e-5, with 0.0 being absolute perfect tracking.
   * Higher values (i.e. 1e-4) will result in more fast and loose tracking.
   */
  double m_icp_threshold;

  /**
   * Determines whether the pipeline is running in preview mode or not.
   * This means different things depending on how the pipeline is configured.
   * For 3D scanning, it means whether to scan (track and fuse) or just preview
   */
  bool m_preview_mode;

  /* Set whether the SLAM algorithm should use the color camera or not */
  bool m_enable_color;

  /* Sets the host ip that we should send packets to when networking */
  std::string m_server_host;
  /* Sets the port that we should send packets to when networking */
  int m_server_port;
  /* Sets whether this device should receive the renderer preview stream */
  bool m_receive_rendered_stream;
  /* Sets whether this device should stream its renderered preview to m_server_host */
  bool m_send_rendered_stream;
  /* Sets whether this device should stream its SLAMInputBuffer to the m_server_host */
  bool m_send_slam_stream;
  /* Sets whether this device should receive SLAM data via a network stream */
  bool m_receive_slam_stream;

  /* Sets whether this device should receive commands from connected devices */
  bool m_receive_network_commands;
  /* Sets whether this device should send commands to other connected devices */
  bool m_send_network_commands;

  /* Sets whether scanning is done with a bounding box or without */
  bool m_use_unbounded;

  /* Sets whether to use texture mapping mode for face scanning */
  bool m_use_texturing;

  /* Sets whether to configure for volumetric video use case */
  bool m_enable_volumetric_video_streaming;
  bool m_enable_volumetric_video_recording;

  /* Where to store all the temporary files that get created with a scan */
  std::string m_scan_dir_path;

  /* Index into the list of shaders to apply to a volumetric video stream */
  int m_shader_idx;

public:
  IScandyCoreConfiguration();
public:
  bool enableVolumetricVideo(){
    return m_enable_volumetric_video_streaming || m_enable_volumetric_video_recording;
  }

  std::vector<std::string> discoveredHosts(){
    auto hosts = m_discovered_hosts;
    return hosts;
  }
};

}}

#endif // Scandy_IScandyCoreConfiguration_h
