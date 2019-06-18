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

#ifndef Scandy_DepthFrameMetadata_h
#define Scandy_DepthFrameMetadata_h

#include <scandy/utilities/SensorFrameMetadata.h>

#if ENABLE_HIBERLITE
#include <hiberlite.h>
#endif

namespace scandy { namespace utilities {

/**
 * \brief DepthFrameMetadata contains metadata relating to the depth frame
 * and the device it's from
 */
class DepthFrameMetadata : public SensorFrameMetadata {
public:
  // The intrinsics for camera that captured this depth frame
  scandy::utilities::CameraIntrinsics intrinsics;
public:
  DepthFrameMetadata(){};

  DepthFrameMetadata(const DepthFrameMetadata&) = default;
  DepthFrameMetadata(DepthFrameMetadata&&) = default;
  DepthFrameMetadata& operator=(const DepthFrameMetadata&) = default;
  DepthFrameMetadata& operator=(DepthFrameMetadata&) = default;
  DepthFrameMetadata& operator=(DepthFrameMetadata&&) = default;

  int width(){ return intrinsics.m_width; }
  int height(){ return intrinsics.m_height; }

  template <class Archive>
  void serialize(Archive& archive){
    archive(
      cereal::base_class<scandy::utilities::SensorFrameMetadata>( this ),
      intrinsics,
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
    ar & HIBERLITE_NVP(intrinsics);

    SensorFrameMetadata::hibernate(ar);
  }
#endif
};

}}


#endif // Scandy_DepthFrameMetadata_h
