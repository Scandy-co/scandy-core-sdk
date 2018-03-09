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
 * \file HeadTrackData.h
 * \brief Furnishes class for `HeadTrackData`.
 */

#ifndef Scandy_HeadTrackData_h
#define Scandy_HeadTrackData_h

#include <scandy/utilities/eigen_vector_math.h>

namespace scandy { namespace utilities {

/**
 * \class HeadTrackData
 * \brief HeadTrackData contains information regarding camera rotation around
 * a subject, as well as if an image has been saved and direction of movement
 */
class HeadTrackData {
public:
  /**
   * unit quaternion representing rotation offset from initial position about
   * the world's up vector (opposite of gravity direction)
   */
  scandy::utilities::eigen::float4 quaternion;

  /**
   * flag to say if we should move right or left around subject being captured
   */
  bool should_move_right;

  /**
   * flag to say whether we are currently aligned
   */
  bool is_aligned;

  /**
   * flag to indicate whether the image corresponding to this rotation was
   * saved or not
   */
  bool did_save_image;

  /**
   * Default constructor sets `quaternion` to an identity matrix.
   */
  HeadTrackData();

  HeadTrackData(const HeadTrackData&) = default;
  HeadTrackData(HeadTrackData&&) = default;
  HeadTrackData& operator=(const HeadTrackData&) = default;
  HeadTrackData& operator=(HeadTrackData&) = default;
  HeadTrackData& operator=(HeadTrackData&&) = default;
};

}}

#endif // Scandy_HeadTrackData_h
