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

#include <scandy/utilities/hiberliteApplication.h>

#include <hiberlite.h>

using namespace hiberlite;
using namespace std;

namespace scandy { namespace utilities {

/**
 * \brief DepthTrackMetadata
 */
class DepthTrackMetadata : public TrackedMetadata {
public:
  friend class hiberlite::access;
  float icp_cost;

  // metadata of the raw sensor frame associated
  DepthFrameMetadata frame_metadata;

  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(icp_cost);
    ar & HIBERLITE_NVP(frame_metadata);

    TrackedMetadata::hibernate(ar);
  }
};

}}

#endif // Scandy_DepthTrackMetadata_h
