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

/**
 * \file RelativePose.h
 * \brief Furnishes class for `RelativePose`.
 */

#ifndef Scandy_RelativePose_h
#define Scandy_RelativePose_h

#include <scandy/utilities/Pose.h>
#include <scandy/utilities/ID_types.h>

namespace scandy { namespace utilities {

/**
 * \class RelativePose
 * \brief Affords `Pose` as it is relative to the stream ID and to the camera ID.
 *
 * For a chronology of the relative pose problem, see:
 * http://www.ignaciomellado.es/blog/The-relative-pose-problem-A-chronology
 */
class RelativePose {
public:
  SensorID m_relative_to_sensor_id;
  DeviceID m_relative_to_device_id;
  Pose m_pose;
public:
  RelativePose(
    const SensorID& relative_to_sensor_id = "",
    const DeviceID& relative_to_device_id = ""
  );

};

}}

#endif // Scandy_RelativePose_h
