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

#ifndef Scandy_DepthTrackMetadata_h
#define Scandy_DepthTrackMetadata_h

#include <scandy/utilities/TrackedMetadata.h>
#include <scandy/utilities/DepthFrameMetadata.h>

#if ENABLE_HIBERLITE
#include <scandy/utilities/hiberliteApplication.h>
#include <hiberlite.h>
#endif


namespace scandy { namespace utilities {

/**
 * \brief DepthTrackMetadata
 */
class DepthTrackMetadata : public TrackedMetadata {
public:
  float icp_cost;

  // metadata of the raw sensor frame associated
  DepthFrameMetadata frame_metadata;

#if ENABLE_HIBERLITE
  friend class hiberlite::access;

  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(icp_cost);
    ar & HIBERLITE_NVP(frame_metadata);

    TrackedMetadata::hibernate(ar);
  }
#endif

};

}}

#endif // Scandy_DepthTrackMetadata_h
