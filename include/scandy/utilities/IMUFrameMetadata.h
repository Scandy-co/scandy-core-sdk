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

#ifndef Scandy_IMUFrameMetadata_h
#define Scandy_IMUFrameMetadata_h

#include <scandy/utilities/SensorFrameMetadata.h>

#if ENABLE_HIBERLITE
#include <hiberlite.h>
#endif

namespace scandy { namespace utilities {

/**
 * \brief IMUFrameMetadata contains information related to the IMU sensors an
 * IMU frame was generated by
 */
class IMUFrameMetadata : public SensorFrameMetadata {
public:
  // TODO sensor noise quantified in some way
  float sensor_error;

#if ENABLE_HIBERLITE
  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(sensor_error);

    SensorFrameMetadata::hibernate(ar);
  }
#endif

};

}}

#endif // Scandy_IMUFrameMetadata_h
