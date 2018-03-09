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
 * \file Pose.h
 * \brief Furnishes class for `Pose`.
 */

#ifndef Scandy_Pose_h
#define Scandy_Pose_h

#include <scandy/utilities/eigen_vector_math.h>
#include <scandy/utilities/EXIFOrientation.h>

namespace scandy { namespace utilities {

/**
 * \class Pose
 * \brief Pose is a 4x4 rotation matrix that represents rotation and translation
 * in 3D space.
 */
class Pose {
public:
  /*
   * The Mat4f holding the data for this class. Read more about homogenous here:
   * https://en.wikipedia.org/wiki/System_of_linear_equations#Homogeneous_systems
   */
  scandy::utilities::eigen::Mat4f homogeneous_matrix;

  scandy::utilities::eigen::float4 quaternion;

  /**
   * Default constructor sets `homogeneous_matrix` to an identity matrix.
   */
  Pose();

  /**
   * Constructor sets `homogeneous_matrix` to the provided matrix.
   * @param pose The Mat4f to which the homogeneous_matrix is set.
   */
  Pose(scandy::utilities::eigen::Mat4f pose);

  Pose(const Pose&) = default;
  Pose(Pose&&) = default;
  Pose& operator=(const Pose&) = default;
  Pose& operator=(Pose&) = default;
  Pose& operator=(Pose&&) = default;

  void setEXIFOrientation(const scandy::utilities::EXIFOrientation exif_orientation);

  void setTranslation(const float x_translation, const float y_translation, const float z_translation);
};

}}

#endif // Scandy_Pose_h
