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

#ifndef Scandy_FusedTrackMetaData_h
#define Scandy_FusedTrackMetaData_h

#include <scandy/utilities/TrackedMetaData.h>


namespace scandy { namespace utilities {

/**
 * \brief FusedTrackMetaData contains the fused pose from the various sensors
 * that contribute to tracking (i.e. depth sensor, IMU sensors, etc.)
 */
class FusedTrackMetaData : public TrackedMetaData {
public:
  friend class hiberlite::access;
  // keep track of the metadata uids used to fuse this frame
  std::vector<MetadataUID> contributing_uids;

  // metadata of the raw depth sensor frame associated
  SensorFrameMetaData frame_metadata;

  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(contributing_uids);
    ar & HIBERLITE_NVP(frame_metadata);

    TrackedMetaData::hibernate(ar);
  }
};

}}

#endif // Scandy_FusedTrackMetaData_h
