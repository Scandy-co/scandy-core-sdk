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

#ifndef Scandy_SensorFrameMetadata_h
#define Scandy_SensorFrameMetadata_h

#include <scandy/utilities/Metadata.h>
#include <scandy/utilities/Pose.h>
#include <scandy/utilities/eigen_vector_math.h>

#include <cereal/types/base_class.hpp>

#if ENABLE_HIBERLITE
#include <hiberlite.h>
#endif

namespace scandy { namespace utilities {

/**
 * \brief SensorFrameMetadata describes necessary additional information for
 * using a SensorFrame that's created by a SensorDataStream.
 */
class SensorFrameMetadata : public Metadata {
public:
  // The relative pose of the sensor that captured a SensorFrame to Scandy's
  // coordinates
  scandy::utilities::Pose initial_pose_offset;

  // The DeviceID of the camera that captured a SensorFrame
  DeviceID device_id="";

  // The SensorID of the stream that captured a SensorFrame
  SensorID sensor_id="";

public:
  SensorFrameMetadata(){
    initial_pose_offset = scandy::utilities::eigen::identityMat4f();
  }

  SensorFrameMetadata(const SensorFrameMetadata&) = default;
  SensorFrameMetadata(SensorFrameMetadata&&) = default;
  SensorFrameMetadata& operator=(const SensorFrameMetadata&) = default;
  SensorFrameMetadata& operator=(SensorFrameMetadata&) = default;
  SensorFrameMetadata& operator=(SensorFrameMetadata&&) = default;

  template <class Archive>
  void serialize(Archive& archive){
    archive(
      cereal::base_class<Metadata>( this ),
      initial_pose_offset,
      device_id,
      sensor_id
    );
  }

#if ENABLE_HIBERLITE
  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(initial_pose_offset);
    ar & HIBERLITE_NVP(device_id);
    ar & HIBERLITE_NVP(sensor_id);

    Metadata::hibernate(ar);
  }
#endif
};

}}

#endif // Scandy_SensorFrameMetadata_h
