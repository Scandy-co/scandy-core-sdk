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
  Pose()
  :homogeneous_matrix(scandy::utilities::eigen::identityMat4f())
  ,quaternion({{0,0,0,0}})
  {}

  /**
   * Constructor sets `homogeneous_matrix` to the provided matrix.
   * @param pose The Mat4f to which the homogeneous_matrix is set.
   */
  Pose(scandy::utilities::eigen::Mat4f pose)
  : homogeneous_matrix(pose){}

  Pose(const Pose&) = default;
  Pose(Pose&&) = default;
  Pose& operator=(const Pose&) = default;
  Pose& operator=(Pose&) = default;
  Pose& operator=(Pose&&) = default;

  void setEXIFOrientation(const scandy::utilities::EXIFOrientation exif_orientation) {
      // NOTE: Remember that the homogeneous_matrix is a column-major matrix!
      switch(exif_orientation) {
      case scandy::utilities::EXIFOrientation::ONE:
          // 1: standard (x, y) : [[1, 0], [0, 1]]
          homogeneous_matrix.s0 = 1.0f;
          homogeneous_matrix.s4 = 0.0f;
          homogeneous_matrix.s1 = 0.0f;
          homogeneous_matrix.s5 = 1.0f;
          break;
      case scandy::utilities::EXIFOrientation::TWO:
          // 2: flipped on the y axis (-x, y) : [[-1, 0], [0, 1]]
          homogeneous_matrix.s0 = -1.0f;
          homogeneous_matrix.s4 = 0.0f;
          homogeneous_matrix.s1 = 0.0f;
          homogeneous_matrix.s5 = 1.0f;
          break;
      case scandy::utilities::EXIFOrientation::THREE:
          // 3: 180 degree rotation (-x, -y) : [[-1, 0], [0, -1]]
          homogeneous_matrix.s0 = -1.0f;
          homogeneous_matrix.s4 = 0.0f;
          homogeneous_matrix.s1 = 0.0f;
          homogeneous_matrix.s5 = -1.0f;
          break;
      case scandy::utilities::EXIFOrientation::FOUR:
          // 4: flipped on y axis + 180 degree rotation (x, -y) : [[1, 0], [0, -1]]
          homogeneous_matrix.s0 = 1.0f;
          homogeneous_matrix.s4 = 0.0f;
          homogeneous_matrix.s1 = 0.0f;
          homogeneous_matrix.s5 = -1.0f;
          break;
      case scandy::utilities::EXIFOrientation::FIVE:
          // 5: flipped on y axis + 270 degree (clockwise) rotation (y, x) : [[0, 1], [1, 0]]
          homogeneous_matrix.s0 = 0.0f;
          homogeneous_matrix.s4 = 1.0f;
          homogeneous_matrix.s1 = 1.0f;
          homogeneous_matrix.s5 = 0.0f;
          break;
      case scandy::utilities::EXIFOrientation::SIX:
          // 6: 270 degree rotation (y, -x) : [[0, -1], [1, 0]]
          homogeneous_matrix.s0 = 0.0f;
          homogeneous_matrix.s4 = -1.0f;
          homogeneous_matrix.s1 = 1.0f;
          homogeneous_matrix.s5 = 0.0f;
          break;
      case scandy::utilities::EXIFOrientation::SEVEN:
          // 7: flipped on y axis + 90 degree rotation (-y, -x) : [[0, -1], [-1, 0]]
          homogeneous_matrix.s0 = 0.0f;
          homogeneous_matrix.s4 = -1.0f;
          homogeneous_matrix.s1 = -1.0f;
          homogeneous_matrix.s5 = 0.0f;
          break;
      case scandy::utilities::EXIFOrientation::EIGHT:
          // 8: 90 degree rotation: (-y, x) : [[0, 1], [-1, 0]]
          homogeneous_matrix.s0 = 0.0f;
          homogeneous_matrix.s4 = 1.0f;
          homogeneous_matrix.s1 = -1.0f;
          homogeneous_matrix.s5 = 0.0f;
          break;
      default:
          // TODO: log error
          // Do nothing, as in Orientation 1
          break;
      }
  }

  void setTranslation(const float x_translation, const float y_translation, const float z_translation) {
      // Sets the translation portion of the pose. Units should be the same units as used by the intrinsics
      // matrix, etc.
      homogeneous_matrix.sc = x_translation;
      homogeneous_matrix.sd = y_translation;
      homogeneous_matrix.se = z_translation;
  }
};


}}

#endif // Scandy_Pose_h
