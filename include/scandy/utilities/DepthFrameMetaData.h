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

#ifndef Scandy_DepthFrameMetaData_h
#define Scandy_DepthFrameMetaData_h

#include <scandy/utilities/SensorFrameMetaData.h>


namespace scandy { namespace utilities {

/**
 * \brief DepthFrameMetaData contains metadata relating to the depth frame
 * and the device it's from
 */
class DepthFrameMetaData : public SensorFrameMetaData {
public:
  friend class hiberlite::access;

  // The intrinsics for camera that captured this depth frame
  scandy::utilities::CameraIntrinsics intrinsics;

  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(intrinsics);

    SensorFrameMetaData::hibernate(ar);
  }
};

}}


#endif // Scandy_DepthFrameMetaData_h
