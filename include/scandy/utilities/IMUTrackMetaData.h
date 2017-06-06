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

#ifndef Scandy_IMUTrackMetadata_h
#define Scandy_IMUTrackMetadata_h

#include <scandy/utilities/TrackedMetadata.h>


namespace scandy { namespace utilities {

/**
 * \brief IMUTrackMetadata
 */
class IMUTrackMetadata : public TrackedMetadata {
public:
  // sensor noise based on known values for each type of sensor
  // TODO make multiple of these as necessary
  float sensor_error;

  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(sensor_error);

    TrackedMetadata::hibernate(ar);
  }
};

}}

#endif // Scandy_IMUTrackMetadata_h
