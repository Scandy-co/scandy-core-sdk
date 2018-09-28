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

#ifndef Scandy_ISLAMConfigration_h
#define Scandy_ISLAMConfigration_h

#include <string>

namespace scandy { namespace core {
/**
 * Interface for interacting with configuration that defines the SLAM context.
 * Get the ISLAMConfiguration shared_ptr from IScandyCore
 */
class ISLAMConfiguration {
public:
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
  /* Sets whether a network server should be launched */
  bool m_is_network_server;
  /* Sets whether a network client should be launched and streamed */
  bool m_is_network_client;

public:
  ISLAMConfiguration();
};

}}

#endif // Scandy_ISLAMConfigration_h
