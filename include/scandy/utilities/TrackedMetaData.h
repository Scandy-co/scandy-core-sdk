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

#ifndef Scandy_TrackedMetadata_h
#define Scandy_TrackedMetadata_h

#include <scandy/utilities/SensorFrameMetadata.h>


namespace scandy { namespace utilities {

/**
 * \brief TrackedMetadata
 */
class TrackedMetadata : public SensorFrameMetadata {
public:
  friend class hiberlite::access;
  // time that the computed pose was calculated
  // TODO decide if this is the same as timestamp
  uint64_t time_tracked;
  bool frame_tracked = false;
  bool frame_integrated = false;

  // delay from when we created the frame to when pose was computed
  uint64_t track_time_cost;

  // time difference from the last frame
  float delta_t;

  // metadata of the raw sensor frame associated
  // SensorFrameMetadata frame_metadata;

  // type of sensor this metadata describes
  std::string sensor_type;

  // some normalized confidence on scale of 0 to 1
  // TODO determine how to find this value / what it means
  float confidence;

  // flags to let the fusion thread know if we have enough information to
  // filter
  bool did_compute_velocities;
  bool did_compute_accels;

  // The computed Pose of the sensor that captured a SensorFrame
  scandy::utilities::Pose computed_pose;

  // the orientation part of the pose saved a a quaternion
  scandy::utilities::float4 orientation_quaterion;

  // linear velocity/acceleration for sensors that measure position
  scandy::utilities::float3 linear_velocity;
  scandy::utilities::float3 linear_acceleration;

  // angular velocity/acceleration for sensors that measure pose orientation
  scandy::utilities::float3 angular_velocity;
  scandy::utilities::float3 angular_acceleration;

  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(time_tracked);
    ar & HIBERLITE_NVP(frame_tracked);
    ar & HIBERLITE_NVP(frame_integrated);
    ar & HIBERLITE_NVP(track_time_cost);
    ar & HIBERLITE_NVP(delta_t);
    // ar & HIBERLITE_NVP(frame_metadata);
    ar & HIBERLITE_NVP(sensor_type);
    ar & HIBERLITE_NVP(confidence);
    ar & HIBERLITE_NVP(did_compute_velocities);
    ar & HIBERLITE_NVP(did_compute_accels);
    ar & HIBERLITE_NVP(computed_pose);
    ar & HIBERLITE_NVP(orientation_quaterion);
    ar & HIBERLITE_NVP(linear_velocity);
    ar & HIBERLITE_NVP(linear_acceleration);
    ar & HIBERLITE_NVP(angular_velocity);
    ar & HIBERLITE_NVP(angular_acceleration);

    SensorFrameMetadata::hibernate(ar);
  }
};

}}

#endif // Scandy_TrackedMetadata_h
