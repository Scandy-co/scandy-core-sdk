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
 * \file eigen_vector_math.h
 * \brief Defines commonly used vector conversions that are needed throughout
 * Scandy Core. These use Eigen for their math meat.
 */

#ifndef Scandy_eigen_vector_math_h
#define Scandy_eigen_vector_math_h

#include <scandy/utilities/vector_types.h>
#include <scandy/utilities/struct_types.h>
#include <scandy/utilities/CameraIntrinsics.h>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

#include <Eigen/Core>
// NOTE: this fixed bug with EigenM4f.inverse()
// In Eigen/MatrixBase is says incluse LU for some specified ops,
// inverse being one
#include <Eigen/LU>
#include <Eigen/Dense>


namespace scandy { namespace utilities { namespace eigen {

// Bring some frequently used data types into this namespace
using float4 = scandy::utilities::float4;
using CameraIntrinsics = scandy::utilities::CameraIntrinsics;

/* Note: I'm using a column-major representation for Mat4f for ease of use
 * with Eigen. -@kaben
 */
using Mat4f = scandy::utilities::float16;
using EigenM4f = Eigen::Map<Eigen::Matrix4f>;
using EigenV4f = Eigen::Map<Eigen::Vector4f>;
using EigenV3f = Eigen::Map<Eigen::Vector3f>;

/* Creates camera intrinsics matrix from k, with k.x --> fx (focal length in
 * pixel widths), x.y --> fy (focal length in pixel heights), k.z --> cx
 * (principle point x coordinate in pixels), k.w --> cx (principle point y
 * coordinate in pixels).
 */
// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f intrinsicMatrix(const float4& k) {
  Mat4f K;
  /* This uses Eigen to contruct the intrinsics matrix. */
  EigenM4f(K.s) <<
    k.x, 0.0, k.z, 0.0,
    0.0, k.y, k.w, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0;
  return K;
}

// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f intrinsicMatrix(const CameraIntrinsics& k) {
  return intrinsicMatrix(float4{{
    float(k.m_fx),
    float(k.m_fy),
    float(k.m_cx),
    float(k.m_cy)
  }});
}

/* Similar to above, but creates inverse camera intrinsics matrix. */
// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f inverseIntrinsicMatrix(const float4 & k) {
  return intrinsicMatrix(float4{{
    1.0f/k.x,
    1.0f/k.y,
    -k.z/k.x,
    -k.w/k.y
  }});
}

// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f inverseIntrinsicMatrix(const CameraIntrinsics& k) {
  return inverseIntrinsicMatrix(float4{{
    float(k.m_fx),
    float(k.m_fy),
    float(k.m_cx),
    float(k.m_cy)
  }});
}

// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f initialPoseMatrix(Mat4f pose_factor, float4 vol_dim){
  /* Pose matrix. */
  Mat4f p;
  /* Eigen map of pose matrix. */
  EigenM4f P(p.s);
  /* Copy full pose_factor matrix into P, as quick way to copy over rotation
   * coefficients.
   */
  P = EigenM4f(pose_factor.s);
  /* For translation coefficients, multiply pose_factor translation
   * coefficient factors by volume dimensions.
   */
  P(0,3) *= vol_dim.x;
  P(1,3) *= vol_dim.y;
  P(2,3) *= vol_dim.z;
  return p;
}

/* Assuming this is a pose/intrinsic matrix, returns just the rotation. */
// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f rotationPart(Mat4f m){
  Mat4f r;
  EigenM4f(r.s) <<
  m.s0, m.s4, m.s8, 0.0f,
  m.s1, m.s5, m.s9, 0.0f,
  m.s2, m.s6, m.sa, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f;
  return r;
}

/* Assuming this is a pose/intrinsic matrix, returns just the translation. */
// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f translationPart(Mat4f m){
  Mat4f t;
  EigenM4f(t.s) <<
  1.0f, 0.0f, 0.0f, m.sc,
  0.0f, 1.0f, 0.0f, m.sd,
  0.0f, 0.0f, 1.0f, m.se,
  0.0f, 0.0f, 0.0f, 1.0f;
  return t;
}

inline Mat4f identityMat4f(){
  Mat4f t;
  EigenM4f(t.s) <<
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f;
  return t;
}

inline bool isIdentity(Mat4f mat){
  Mat4f eye = identityMat4f();

  bool result = true;
  for(int i = 0; i < 16; i++){
    result = result && (mat.s[i] == eye.s[i]);
  }
  return result;
}

inline bool areEqual(Mat4f mat1, Mat4f mat2){
  bool result = EigenM4f(mat1.s).isApprox(EigenM4f(mat2.s));
  return result;
}

// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f inverse(Mat4f m){
  Mat4f m_i;
  EigenM4f(m_i.s) = EigenM4f(m.s).inverse();
  return m_i;
}

// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
// NOTE: the output Matrix ( Mat4f ) is COLUMN MAJOR
inline Mat4f product(Mat4f t, Mat4f s){
  Mat4f p;
  EigenM4f(p.s) = EigenM4f(t.s)*EigenM4f(s.s);
  return p;
}

// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
inline float4 product(Mat4f t, float4 v){
  float4 p;
  EigenV4f(p.s) = EigenM4f(t.s)*EigenV4f(v.s);
  return p;
}

// normalize a float3 vector
inline float3 normalize(float3 v){
  EigenV3f(v.s).normalize();
  return v;
}

// normalize a float4 vector
inline float4 normalize(float4 v){
  EigenV4f(v.s).normalize();
  return v;
}

}}}

/**
 * Define all the serializers for Eigen
 */

namespace Eigen {

  // the following save/load cover all Eigen Matrix types (Matrix3f,
  // Matrix4d, etc)
  template <
    class Archive,
    class Scalar,
    int Rows,
    int Cols,
    int Options,
    int MaxRows,
    int MaxCols
  >
  inline typename std::enable_if<
    cereal::traits::is_output_serializable<
      cereal::BinaryData<Scalar>,
      Archive
    >::value,
    void
  >::type save(
    Archive & ar,
    Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols> const & m
  ){
    int32_t rows = m.rows();
    int32_t cols = m.cols();
    ar(rows);
    ar(cols);
    ar(cereal::binary_data(m.data(), rows * cols * sizeof(Scalar)));
  }

  template <
    class Archive,
    class Scalar,
    int Rows,
    int Cols,
    int Options,
    int MaxRows,
    int MaxCols
  >
  inline typename std::enable_if<
    cereal::traits::is_input_serializable<
      cereal::BinaryData<Scalar>,
      Archive
    >::value,
    void
  >::type load(
    Archive & ar,
    Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols> & m
  ){
    int32_t rows;
    int32_t cols;
    ar(rows);
    ar(cols);

    m.resize(rows, cols);

    ar(cereal::binary_data(
      m.data(),
      static_cast<std::size_t>(rows * cols * sizeof(Scalar))
    ));
  }


  // the following serializer covers all Eigen Transform types (Affine3f,
  // etc) by serializing the underlying matrix
  template <class Archive, class Scalar, int Dim, int Mode, int Options>
  void serialize(
    Archive& archive,
    Eigen::Transform<Scalar, Dim, Mode, Options>& t
  ){
    archive(t.matrix());
  }
}

#endif // Scandy_eigen_vector_math_h
