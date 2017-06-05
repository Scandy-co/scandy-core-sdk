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

#ifndef Scandy_DepthTrackMetaData_h
#define Scandy_DepthTrackMetaData_h

#include <scandy/utilities/TrackedMetaData.h>
#include <scandy/utilities/DepthFrameMetaData.h>

#include <scandy/utilities/hiberliteApplication.h>

#include <hiberlite.h>

using namespace hiberlite;
using namespace std;

namespace scandy { namespace utilities {

/**
 * \brief DepthTrackMetaData
 */
class DepthTrackMetaData : public TrackedMetaData {
public:
  friend class hiberlite::access;
  float icp_cost;

  // metadata of the raw sensor frame associated
  DepthFrameMetaData frame_metadata;

  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(icp_cost);
    ar & HIBERLITE_NVP(frame_metadata);

    TrackedMetaData::hibernate(ar);
  }
};

}}

#endif // Scandy_DepthTrackMetaData_h
