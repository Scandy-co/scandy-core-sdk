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
 * \file quaternion_math.h
 * \brief Defines operations for quaterions
 */

#ifndef Scandy_quaternion_math_h
#define Scandy_quaternion_math_h

//if we are using this from foo.cl -> foo_cl.h char* generator then we don't need to include all the things
#ifndef IS_A_CL_HEADER_STRING
#define IS_A_CL_HEADER_STRING 0
#endif

#if !IS_A_CL_HEADER_STRING
#include <scandy/utilities/vector_math.h>
//endif !IS_A_CL_HEADER_STRING
#endif

// if we are IS_A_CL_HEADER_STRING we don't need namespace
#if !IS_A_CL_HEADER_STRING
// Put this in the scandy::utilities namespace
namespace scandy { namespace utilities {
//endif !IS_A_CL_HEADER_STRING
#endif

inline scandy::utilities::float4 quaternion_multiply(scandy::utilities::float4 q1, scandy::utilities::float4 q2){
  scandy::utilities::float4 product = {{0,0,0,0}};

  product.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
  product.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
  product.y = q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z;
  product.z = q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x;

  return product;
}

inline float quaternion_norm(scandy::utilities::float4 q){
  float norm = q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z;

  return norm;
}

// TODO move into utilities
inline scandy::utilities::float4 quaternion_inverse(scandy::utilities::float4 q){
  scandy::utilities::float4 q_inv = {{0, 0, 0, 0}};

  float norm = quaternion_norm(q);
  scandy::utilities::float4 conjugate = {{-q.x, -q.y, -q.z, q.w}};

  q_inv.w = conjugate.w/norm;
  q_inv.x = conjugate.x/norm;
  q_inv.y = conjugate.y/norm;
  q_inv.z = conjugate.z/norm;

  return q_inv;
}


inline scandy::utilities::float4 quaternion_normalize(scandy::utilities::float4 q){
  scandy::utilities::float4 normalized_quat;

  float norm = quaternion_norm(q);
  float magnitude = sqrt(norm);

  normalized_quat.x = q.x/magnitude;
  normalized_quat.y = q.y/magnitude;
  normalized_quat.z = q.z/magnitude;
  normalized_quat.w = q.w/magnitude;

  return normalized_quat;
}

// quaternion_distance returns the "distance" in rotation between two
// quaternions. the result is in radians and should be between [0, π/2]
inline float quaternion_distance(scandy::utilities::float4 q1, scandy::utilities::float4 q2){
  float theta = acos(q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z);

  if(theta > M_PI/2){
    theta = M_PI - theta;
  }

  return theta;
}

// inspiration from:
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
inline scandy::utilities::float4 matrix2quaternion(scandy::utilities::Mat4f m){
  scandy::utilities::float4 q = {{0,0,0,0}};

  // add the diagonal elements to calculate the trace
  double trace = m.s0 + m.s5 + m.sA;

  if(trace > 0){
    double s = sqrt(trace + 1.f) * 2; // S=4*qw
    q.w = (0.25f * s);
    q.x = (m.s9 - m.s6) / s;
    q.y = (m.s2 - m.s8) / s;
    q.z = (m.s4 - m.s1) / s;
  }
  else if ((m.s0 > m.s5) & (m.s0 > m.sA)) {
    double s = sqrt(1.0 + m.s0 - m.s5 - m.sA) * 2; // S=4*qx
    q.w = (m.s9 - m.s6) / s;
    q.x = 0.25f * s;
    q.y = (m.s1 + m.s4) / s;
    q.z = (m.s2 + m.s8) / s;
  }
  else if (m.s5 > m.sA) {
    double s = sqrt(1.0 + m.s5 - m.s0 - m.sA) * 2; // S=4*qy
    q.w = (m.s2 - m.s8) / s;
    q.x = (m.s1 + m.s4) / s;
    q.y = 0.25f * s;
    q.z = (m.s6 + m.s9) / s;
  }
  else {
    double s = sqrt(1.0 + m.sA - m.s0 - m.s5) * 2; // S=4*qz
    q.w = (m.s4 - m.s1) / s;
    q.x = (m.s2 + m.s8) / s;
    q.y = (m.s6 + m.s9) / s;
    q.z = 0.25f * s;
  }

  return q;
}

// inspiration from:
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
inline scandy::utilities::Mat4f quaternion2matrix(scandy::utilities::float4 q){
  scandy::utilities::Mat4f m;

  double q0 = q.w;
  double q1 = q.x;
  double q2 = q.y;
  double q3 = q.z;

  double sq_q1 = 2 * q1 * q1;
  double sq_q2 = 2 * q2 * q2;
  double sq_q3 = 2 * q3 * q3;
  double q1_q2 = 2 * q1 * q2;
  double q3_q0 = 2 * q3 * q0;
  double q1_q3 = 2 * q1 * q3;
  double q2_q0 = 2 * q2 * q0;
  double q2_q3 = 2 * q2 * q3;
  double q1_q0 = 2 * q1 * q0;

  m.s0 = 1 - sq_q2 - sq_q3;
  m.s1 = q1_q2 - q3_q0;
  m.s2 = q1_q3 + q2_q0;
  m.s3 = 0.0f;
  m.s4 = q1_q2 + q3_q0;
  m.s5 = 1 - sq_q1 - sq_q3;
  m.s6 = q2_q3 - q1_q0;
  m.s7 = 0.0f;
  m.s8 = q1_q3 - q2_q0;
  m.s9 = q2_q3 + q1_q0;
  m.sA = 1 - sq_q1 - sq_q2;
  m.sB = 0.0f;
  m.sC = m.sD = m.sE = 0.0f;
  m.sF = 1.0f;

  return m;
}

// inspiration from:
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
inline scandy::utilities::float3 quaternion2euler(scandy::utilities::float4 q){
  scandy::utilities::float3 angles;
  double q_w = q.w;
  double q_x = q.x;
  double q_y = q.y;
  double q_z = q.z;


  double sqx = q_x * q_x;
  double sqy = q_y * q_y;
  double sqz = q_z * q_z;

  double test = q_x*q_y + q_z*q_w;
  if (test > 0.499) { // singularity at north pole
    angles.y = 2 * atan2(q_x,q_w);
    angles.z = M_PI/2;
    angles.x = 0;
  }
  else if (test < -0.499) { // singularity at south pole
    angles.y = -2 * atan2(q_x,q_w);
    angles.z = - M_PI/2;
    angles.x = 0;
  }
  else{
    angles.y = atan2(2*q_y*q_w-2*q_x*q_z , 1 - 2*sqy - 2*sqz);
    angles.z = asin(2*test);
    angles.x = atan2(2*q_x*q_w-2*q_y*q_z , 1 - 2*sqx - 2*sqz);
  }

  return angles;
}

// NOTE based on https://github.com/apacha/sensor-fusion-demo/blob/master/app/src/main/java/org/hitlabnz/sensor_fusion_demo/representation/Quaternion.java slerp function
/**
 * Get a linear interpolation between this quaternion and the input quaternion,
 * storing the result in the output quaternion.
 *
 * @param q1 The quaternion to slerp.
 * @param q2 The quaternion be slerped with q1.
 * @param t The ratio between the two quaternions where 0 <= t <= 1.0 .
 * Increase value of t will bring rotation closer to the q2 quaternion .
 */
inline scandy::utilities::float4 quaternion_slerp(scandy::utilities::float4 q1, scandy::utilities::float4 q2, float t){
  scandy::utilities::float4 output_quat = {{0, 0, 0 ,0}};
  scandy::utilities::float4 buffer_quat = {{0, 0, 0 ,0}};

  // Calculate angle between them.
  float cosHalftheta = scandy::utilities::scandy_dot(q1, q2);

  if (cosHalftheta < 0) {
    cosHalftheta = -cosHalftheta;
    buffer_quat.x = -q2.x;
    buffer_quat.y = -q2.y;
    buffer_quat.z = -q2.z;
    buffer_quat.w = -q2.w;
  } else {
    buffer_quat = q2;
  }

  // if qa=qb or qa=-qb then theta = 0 and we can return qa
  if (fabs(cosHalftheta) >= 1.0) {
    output_quat.x = q1.x;
    output_quat.y = q1.y;
    output_quat.z = q1.z;
    output_quat.w = q1.w;
  } else {
    float sinHalfTheta = sqrt(1.0 - cosHalftheta * cosHalftheta);
    float halfTheta = acos(cosHalftheta);

    float ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
    float ratioB = sin(t * halfTheta) / sinHalfTheta;

    //Calculate Quaternion
    output_quat.w = q1.w * ratioA + buffer_quat.w * ratioB;
    output_quat.x = q1.x * ratioA + buffer_quat.x * ratioB;
    output_quat.y = q1.y * ratioA + buffer_quat.y * ratioB;
    output_quat.z = q1.z * ratioA + buffer_quat.z * ratioB;
  }

  return output_quat;
}

// if we didn't IS_A_CL_HEADER_STRING we need to close the namespace
#if IS_A_CL_HEADER_STRING == 0
}}
//endif !IS_A_CL_HEADER_STRING
#endif


#endif // Scandy_quaternion_math_h
