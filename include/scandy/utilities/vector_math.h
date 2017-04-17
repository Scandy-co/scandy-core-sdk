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

#ifndef Scandy_vector_math_h
#define Scandy_vector_math_h

/**
 * vector_math defines commonly used vector conversions that
 * are needed throughout Scandy
*/


//if we are using this from foo.cl -> foo_cl.h char* generator then we don't need to include all the things
#ifndef IS_A_CL_HEADER_STRING
#define IS_A_CL_HEADER_STRING 0
#endif

#if !IS_A_CL_HEADER_STRING
#include <scandy/utilities/vector_types.h>
#include <scandy/utilities/struct_types.h>
//endif !IS_A_CL_HEADER_STRING
#endif

// if we are IS_A_CL_HEADER_STRING we don't need namespace
#if !IS_A_CL_HEADER_STRING
// Put this in the scandy::utilities namespace
namespace scandy { namespace utilities {
//endif !IS_A_CL_HEADER_STRING
#endif

inline float sq(float r) {
  return r * r;
}

inline float __attribute__((overloadable)) scandy_dot(float3 a, float3 b){
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float __attribute__((overloadable)) scandy_dot(float4 a, float4 b){
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
 * Takes a row major pose/intrinsic matrix and returns just the rotation part.
 * @param  M A row major 4x4 matrix
 * @return   A 4x4 matrix with just the rotation information
 */
inline Mat4f rotationPart(const Mat4f M){
  return make_Mat4f(
    M.s0, M.s4, M.s8, 0.0f,
    M.s1, M.s5, M.s9, 0.0f,
    M.s2, M.s6, M.sA, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}


/**
 * Takes a row major pose/intrinsic matrix and returns just the translation part.
 * @param  M A row major 4x4 matrix
 * @return   A 4x4 matrix with just the translation information
 */
inline Mat4f translationPart(const Mat4f M){
  return make_Mat4f(
    1.0f, 0.0f, 0.0f, M.sC,
    0.0f, 1.0f, 0.0f, M.sD,
    0.0f, 0.0f, 1.0f, M.sE,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

// Returns a transpose of the matrix passed in
// NOTE: the passed in Matrix ( 16 floats ) is assumed to be ROW MAJOR
// NOTE: the output Matrix ( Mat4f ) is ROW MAJOR
inline Mat4f __attribute__((overloadable)) transpose(float s0, float s1, float s2, float s3, float s4, float s5, float s6, float s7, float s8, float s9, float sA, float sB, float sC, float sD, float sE, float sF) {
  Mat4f mat;
  mat.s0 = s0; mat.s4 = s1; mat.s8 = s2; mat.sC = s3;
  mat.s1 = s4; mat.s5 = s5; mat.s9 = s6; mat.sD = s7;
  mat.s2 = s8; mat.s6 = s9; mat.sA = sA; mat.sE = sB;
  mat.s3 = sC; mat.s7 = sD; mat.sB = sE; mat.sF = sF;
  return mat;
}

// NOTE: the passed in Matrix ( Mat4f ) is assumed to be ROW MAJOR
// NOTE: the output Matrix ( Mat4f ) is ROW MAJOR
inline Mat4f __attribute__((overloadable)) transpose(const Mat4f M){
  Mat4f mat;
  mat.s0 = M.s0; mat.s4 = M.s1; mat.s8 = M.s2; mat.sC = M.s3;
  mat.s1 = M.s4; mat.s5 = M.s5; mat.s9 = M.s6; mat.sD = M.s7;
  mat.s2 = M.s8; mat.s6 = M.s9; mat.sA = M.sA; mat.sE = M.sB;
  mat.s3 = M.sC; mat.s7 = M.sD; mat.sB = M.sE; mat.sF = M.sF;
  return mat;
}


// NOTE: the passed in Matrix ( Mat4f ) is assumed to be ROW MAJOR
inline float4 translationVector(const Mat4f M){
  return scandy_make_float4(M.sC, M.sD, M.sE, 1.0f);
}

// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
inline float4 __attribute__((overloadable)) rotation(const Mat4f M, const float4 v) {
  return scandy_make_float4(
    scandy_dot(scandy_make_float4(M.s0, M.s4, M.s8, 0.0f), v),
    scandy_dot(scandy_make_float4(M.s1, M.s5, M.s9, 0.0f), v),
    scandy_dot(scandy_make_float4(M.s2, M.s6, M.sA, 0.0f), v),
    scandy_dot(scandy_make_float4(0.0f, 0.0f, 0.0f, 1.0f), v)
  );
}


// NOTE: the passed in Matrix ( Mat4f ) is assumed to be COLUMN MAJOR
inline float4 transform(const Mat4f M, const float4 v) {
  return scandy_make_float4(
    scandy_dot(scandy_make_float4(M.s0, M.s4, M.s8, M.sC), v),
    scandy_dot(scandy_make_float4(M.s1, M.s5, M.s9, M.sD), v),
    scandy_dot(scandy_make_float4(M.s2, M.s6, M.sA, M.sE), v),
    scandy_dot(scandy_make_float4(M.s3, M.s7, M.sB, M.sF), v)
  );
}

inline float3 Mat4TimeFloat3(const Mat4f M, const float3 v) {
  return scandy_make_float3(
    scandy_dot((scandy_make_float3)(M.s0, M.s4, M.s8), v) + M.sc,
    scandy_dot((scandy_make_float3)(M.s1, M.s5, M.s9), v) + M.sd,
    scandy_dot((scandy_make_float3)(M.s2, M.s6, M.sa), v) + M.se
  );
}

inline float3 Mat4RotateFloat3(const Mat4f M, const float3 v) {
  return scandy_make_float3(
    scandy_dot((scandy_make_float3)(M.s0, M.s4, M.s8), v),
    scandy_dot((scandy_make_float3)(M.s1, M.s5, M.s9), v),
    scandy_dot((scandy_make_float3)(M.s2, M.s6, M.sa), v)
  );
}


#if !IS_A_CL_HEADER_STRING
// use this method to take a quaternion stored as float4 and generate a
// rotation matrix from it
// from https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/hardware/SensorManager.java
inline void getRotationMatrixFromVector(
 Mat4f& rot_matrix,
 float4 rot_data
)
{
   float q0 = rot_data.w;
   float q1 = rot_data.x;
   float q2 = rot_data.y;
   float q3 = rot_data.z;

   float sq_q1 = 2 * q1 * q1;
   float sq_q2 = 2 * q2 * q2;
   float sq_q3 = 2 * q3 * q3;
   float q1_q2 = 2 * q1 * q2;
   float q3_q0 = 2 * q3 * q0;
   float q1_q3 = 2 * q1 * q3;
   float q2_q0 = 2 * q2 * q0;
   float q2_q3 = 2 * q2 * q3;
   float q1_q0 = 2 * q1 * q0;

   rot_matrix.s0 = 1 - sq_q2 - sq_q3;
   rot_matrix.s4 = q1_q2 - q3_q0;
   rot_matrix.s8 = q1_q3 + q2_q0;
   rot_matrix.sC = 0.0f;
   rot_matrix.s1 = q1_q2 + q3_q0;
   rot_matrix.s5 = 1 - sq_q1 - sq_q3;
   rot_matrix.s9 = q2_q3 - q1_q0;
   rot_matrix.sD = 0.0f;
   rot_matrix.s2 = q1_q3 - q2_q0;
   rot_matrix.s6 = q2_q3 + q1_q0;
   rot_matrix.sA = 1 - sq_q1 - sq_q2;
   rot_matrix.sE = 0.0f;
   rot_matrix.s3 = rot_matrix.s7 = rot_matrix.sB = 0.0f;
   rot_matrix.sF = 1.0f;
}

// use this method to take accelerometer and magnetometer data and create
// a rotation matrix. obtained form SensorManager source for android but
// changed to be row-major to match scandy-core's Mat4f general orientation
// from https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/hardware/SensorManager.java
inline bool getRotationMatrix(
 Mat4f& rot_matrix,
 float3 accel_data,
 float3 magnet_data
)
{
  float Ax = accel_data.x;
  float Ay = accel_data.y;
  float Az = accel_data.z;

  const float normsqA = (Ax*Ax + Ay*Ay + Az*Az);
  const float g = 9.81f;
  const float freeFallGravitySquared = 0.01f * g * g;
  if (normsqA < freeFallGravitySquared) {
      // gravity less than 10% of normal value
      return false;
  }
  const float Ex = magnet_data.x;
  const float Ey = magnet_data.y;
  const float Ez = magnet_data.z;
  float Hx = Ey*Az - Ez*Ay;
  float Hy = Ez*Ax - Ex*Az;
  float Hz = Ex*Ay - Ey*Ax;
  const float normH = (float)sqrt(Hx*Hx + Hy*Hy + Hz*Hz);
  if (normH < 0.1f) {
      // device is close to free fall (or in space?), or close to
      // magnetic north pole. Typical values are  > 100.
      return false;
  }

  const float invH = 1.0f / normH;
  Hx *= invH;
  Hy *= invH;
  Hz *= invH;
  const float invA = 1.0f / (float)sqrt(Ax*Ax + Ay*Ay + Az*Az);
  Ax *= invA;
  Ay *= invA;
  Az *= invA;
  const float Mx = Ay*Hz - Az*Hy;
  const float My = Az*Hx - Ax*Hz;
  const float Mz = Ax*Hy - Ay*Hx;

  // rot_matrix.s0  = Hx;    rot_matrix.s1  = Mx;    rot_matrix.s2  = Ax;   rot_matrix.s3  = 0;
  // rot_matrix.s4  = Hy;    rot_matrix.s5  = My;    rot_matrix.s6  = Ay;   rot_matrix.s7  = 0;
  // rot_matrix.s8  = Hz;    rot_matrix.s9  = Mz;    rot_matrix.sA = Az;   rot_matrix.sB = 0;
  // rot_matrix.sC = 0;     rot_matrix.sD = 0;     rot_matrix.sE = 0;    rot_matrix.sF = 1;

  // original from android SensorManager
  // rot_matrix.s0  = Hx;    rot_matrix.s1  = Hy;    rot_matrix.s2  = Hz;   rot_matrix.s3  = 0;
  // rot_matrix.s4  = Mx;    rot_matrix.s5  = My;    rot_matrix.s6  = Mz;   rot_matrix.s7  = 0;
  // rot_matrix.s8  = Ax;    rot_matrix.s9  = Ay;    rot_matrix.sA = Az;   rot_matrix.sB = 0;
  // rot_matrix.sC = 0;     rot_matrix.sD = 0;     rot_matrix.sE = 0;    rot_matrix.sF = 1;

  // trying switching x and z components
  rot_matrix.s0  = Hz;    rot_matrix.s1  = Hy;    rot_matrix.s2  = Hx;   rot_matrix.s3  = 0;
  rot_matrix.s4  = Mz;    rot_matrix.s5  = My;    rot_matrix.s6  = Mx;   rot_matrix.s7  = 0;
  rot_matrix.s8  = Az;    rot_matrix.s9  = Ay;    rot_matrix.sA = Ax;   rot_matrix.sB = 0;
  rot_matrix.sC = 0;     rot_matrix.sD = 0;     rot_matrix.sE = 0;    rot_matrix.sF = 1;
  return true;

}

// use this method to take rotation matrix and create an orientation vector
// takes a row-major matrix
// from https://android.googlesource.com/platform/frameworks/base/+/master/core/java/android/hardware/SensorManager.java
inline void getOrientation(
 Mat4f rotation,
 float3& orientation
 )
 {
   orientation.x = (float)asin(-rotation.s9);                  // pitch
   orientation.y = (float)atan2(-rotation.s8, rotation.sA);    // roll
   orientation.z = (float)atan2(rotation.s1, rotation.s5);     // azimuth
 }

#endif

// if we didn't IS_A_CL_HEADER_STRING we need to close the namespace
#if IS_A_CL_HEADER_STRING == 0
}}
//endif !IS_A_CL_HEADER_STRING
#endif


#endif // Scandy_vector_math_h
