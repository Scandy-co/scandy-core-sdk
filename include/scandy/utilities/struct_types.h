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
 * \file struct_types.h
 * Defines commonly used structs that are needed throughout Scandy
 */

#ifndef Scandy_struct_types_h
#define Scandy_struct_types_h

//if we are using this from foo.cl -> foo_cl.h char* generator then we don't need to include all the things
#ifndef IS_A_CL_HEADER_STRING
#define IS_A_CL_HEADER_STRING 0
#endif

// if we are IS_A_CL_HEADER_STRING we don't need namespace or includes
#if !IS_A_CL_HEADER_STRING
#include <scandy/utilities/vector_types.h>
// Put this in the scandy::utilities namespace
namespace scandy { namespace utilities {
//endif !IS_A_CL_HEADER_STRING
#endif

#if !IS_A_CL_HEADER_STRING
typedef float16 Mat4f;
#else
typedef union {
  float   s[16];
  struct{ float  x, y, z, w, __spacer4, __spacer5, __spacer6, __spacer7, __spacer8, __spacer9, sa, sb, sc, sd, se, sf; };
  struct{ float  s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, sA, sB, sC, sD, sE, sF; };
  float2 v2[8];
  float4 v4[4];
} Mat4f;
#endif

// Helper function to prevent incompability issues between CPU/GPU
inline Mat4f __attribute__((overloadable)) make_Mat4f(float s0, float s1, float s2, float s3, float s4, float s5, float s6, float s7, float s8, float s9, float sA, float sB, float sC, float sD, float sE, float sF) {
  Mat4f mat;
  mat.s0 = s0; mat.s1 = s1; mat.s2 = s2; mat.s3 = s3; mat.s4 = s4; mat.s5 = s5; mat.s6 = s6; mat.s7 = s7; mat.s8 = s8; mat.s9 = s9; mat.sA = sA; mat.sB = sB; mat.sC = sC; mat.sD = sD; mat.sE = sE; mat.sF = sF;
  return mat;
}

// Helper function to prevent incompability issues between CPU/GPU
inline Mat4f __attribute__((overloadable)) make_Mat4f(float arr[16]){
  Mat4f mat = make_Mat4f(
    arr[0], arr[1], arr[2], arr[3],
    arr[4], arr[5], arr[6], arr[7],
    arr[8], arr[9], arr[10], arr[11],
    arr[12], arr[13], arr[14], arr[15]
  );
  return mat;
}

// NOTE: We use scandy_make_floatn to prevent inconsistencies between diffferent
// OpenCL implementations that have or don't have make_floatn defined.
//

// Helper function to prevent incompability issues between CPU/GPU
inline float3 __attribute__((overloadable)) scandy_make_float3(float4 a){
  float3 f;
  f.x = a.x; f.y = a.y; f.z = a.z;
  return f;
}

// Helper function to prevent incompability issues between CPU/GPU
inline float3 __attribute__((overloadable)) scandy_make_float3(float x, float y, float z) {
  float3 f;
  f.x = x;
  f.y = y;
  f.z = z;
  return f;
}

// Helper function to prevent incompability issues between CPU/GPU
inline float4 __attribute__((overloadable)) scandy_make_float4(float x, float y, float z, float w) {
  float4 f;
  f.x = x;
  f.y = y;
  f.z = z;
  f.w = w;
  return f;
}

// Helper function to prevent incompability issues between CPU/GPU
inline float4 __attribute__((overloadable)) scandy_make_float4(float3 a){
  float4 f;
  f.x = a.x; f.y = a.y; f.z = a.z; f.w = 1.f;
  return f;
}

// Helper function to prevent incompability issues between CPU/GPU
inline uchar4 __attribute__((overloadable)) scandy_make_uchar4(unsigned char x, unsigned char y, unsigned char z, unsigned char w) {
  uchar4 f;
  f.x = x;
  f.y = y;
  f.z = z;
  f.w = w;
  return f;
}


// if we didn't IS_A_CL_HEADER_STRING we need to close the namespace
#if IS_A_CL_HEADER_STRING == 0
}}
//endif !IS_A_CL_HEADER_STRING
#endif


#endif // Scandy_struct_types_h
