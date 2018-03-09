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

#ifndef Scandy_FusedTrackMetadata_h
#define Scandy_FusedTrackMetadata_h


#include <scandy/utilities/TrackedMetadata.h>

#if ENABLE_HIBERLITE
#include <hiberlite.h>
#endif

#include <scandy/utilities/ID_types.h>
#include <vector>

namespace scandy { namespace utilities {

/**
 * \brief FusedTrackMetadata contains the fused pose from the various sensors
 * that contribute to tracking (i.e. depth sensor, IMU sensors, etc.)
 */
class FusedTrackMetadata : public TrackedMetadata {
public:
  // keep track of the metadata uids used to fuse this frame
  std::vector<MetadataUID> contributing_uids;

  // metadata of the raw depth sensor frame associated
  SensorFrameMetadata frame_metadata;

#if ENABLE_HIBERLITE
  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(contributing_uids);
    ar & HIBERLITE_NVP(frame_metadata);

    TrackedMetadata::hibernate(ar);
  }
#endif
};

}}

#endif // Scandy_FusedTrackMetadata_h
