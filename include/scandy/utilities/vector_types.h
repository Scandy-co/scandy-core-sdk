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
 * \file vector_types.h
 * \brief Defines commonly used vectors that are needed throughout Scandy Core.
 *
 * \warning Scandy Core does not use the following data types because they have
 * inconsistencies with how different GPUs handle them:
 *   - `float3`: we declare `float3` as a `float4`, and we pad with 0
 */

#ifndef Scandy_vector_types_h
#define Scandy_vector_types_h

#ifdef ENABLE_EXPERIMENTAL
#include <hiberlite.h>
#endif

// if we are typedef this from foo.cl -> foo_cl.h char* generator then we don't
// need to include all the things
#ifndef IS_A_CL_HEADER_STRING
#define IS_A_CL_HEADER_STRING 0
#endif

// if we are IS_A_CL_HEADER_STRING we don't need to import other stuff
#if !IS_A_CL_HEADER_STRING
// #include <scandycore_cl.h>
// #include <cstdint>
#include <stdint.h>
#define HALF_ENABLE_CPP11_CMATH 0
#include <half.hpp>
#endif //!IS_A_CL_HEADER_STRING


// if we are IS_A_CL_HEADER_STRING don't use a namespace
#if !IS_A_CL_HEADER_STRING
// Put this in the scandy::utilities namespace
namespace scandy { namespace utilities {
//endif !IS_A_CL_HEADER_STRING
#endif

typedef unsigned int uint;

typedef unsigned char uchar;


/**
 * \union uchar2
 * \brief Ensures maximal compatability for storage via `union`s for two (2) unsigned
 * characters. A `union` is a structure in which all members are stored at the same
 * address, so as prevent memory fragmentation, namely by creating a standard size for
 * certain data.
 *
 * Such is to say, provided a Cartesian coordinate:
 *
 * - Were Scandy Core to reference a point using using `x` and `y`; and then
 * - Were a library such as OpenCL to reference the same point -- but using `s0` and
 * `s1`;
 *
 * We minimize potential breakage. Thus:
 *
 * ```
 * uchar2 foo;
 * foo.x = 2;
 * foo.y = foo.s0;
 * std::cout << foo[0] << " " << foo[1] << std::endl;
 * ```
 *
 * And, in light of our `union`, the output will be:
 *
 * ```
 * 2 2
 * ```
 */
typedef union { //uchar2
  // uint8_t  CL_ALIGNED(2) s[2];
  uchar s[2];
  struct{ uchar x, y; };
  struct{ uchar s0, s1; };
  struct{ uchar lo, hi; };
  // cl_uchar2 v2;
} uchar2;

/**
 * \union uchar3
 * \brief Ensures maximal compatability for storage via `union`s for three (3) unsigned
 * characters, such as `x`, `y`, and `z` or `r`, `g`, and `b`.
 */
typedef union { //uchar3
  uchar s[3];
  struct{ uchar x, y, z; };
  struct{ uchar r, g, b; };
} uchar3;

/**
 * \union uchar4
 * \brief Ensures maximal compatability for storage via `union`s for four (4) unsigned
 * characters, such as `r`, `g`, `b`, and `a`.
 */
typedef union { //uchar4
  // uint8_t  CL_ALIGNED(4) s[4];
  uchar s[4];
  struct{ uchar   x, y, z, w; };
  struct{ uchar   r, g, b, a; };
  struct{ uchar   s0, s1, s2, s3; };
  struct{ uchar2  lo, hi; };
  uchar2     v2[2];
  uchar3 xyz;
  uchar3 rgb;
  // cl_uchar4     v4;
} uchar4;

/**
 * \union uchar8
 * \brief Ensures maximal compatability for storage via `union`s for eight (8) unsigned
 * characters, such as `x`, `y`, and `z` or `r`, `g`, and `b`.
 *
 * `struct{ uchar x, y, z, w; }` and `struct{ uchar r, g, b, a; };` are included for
 * convenience, enabling procedures such as:
 *
 * ```cpp
 * uchar8 foo;
 * uchar4 bar = {{ 255, 0, 128, 0 }};
 * foo.x = bar.x;
 * foo.z = bar.w;
 * ```
 */
typedef union { //uchar8
  // uint8_t   CL_ALIGNED(8) s[8];
  unsigned char   s[8];
  struct{ uchar   x, y, z, w; };
  struct{ uchar   r, g, b, a; };
  struct{ uchar   s0, s1, s2, s3, s4, s5, s6, s7; };
  struct{ uchar4  lo, hi; };
  uchar2     v2[4];
  uchar4     v4[2];
//  cl_uchar8     v8;
} uchar8;

/**
 * \union uchar16
 * \brief Ensures maximal compatability for storage via `union`s for sixteen (16) unsigned
 * characters.
 */
typedef union { //uchar16
//  uint8_t  CL_ALIGNED(16) s[16];
  unsigned char   s[16];
  struct{ uchar  x, y, z, w, __spacer4, __spacer5, __spacer6, __spacer7, __spacer8, __spacer9, sa, sb, sc, sd, se, sf; };
  struct{ uchar  s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, sA, sB, sC, sD, sE, sF; };
  struct{ uchar8 lo, hi; };
  uchar2     v2[8];
  uchar4     v4[4];
  uchar8     v8[2];
//  cl_uchar16    v16;
} uchar16;

/**
 * \union short2
 * \brief Ensures maximal compatability for storage via `union`s for two (2) `short`s.
 */
typedef union { //short2
//  int16_t  CL_ALIGNED(4) s[2];
  short   s[2];
  struct{ short  x, y; };
  struct{ short  s0, s1; };
  struct{ short  lo, hi; };
//  cl_short2 v2;
} short2;

/**
 * \union short4
 * \brief Ensures maximal compatability for storage via `union`s for four (4) `short`s.
 */
typedef union { //short4
//  int16_t  CL_ALIGNED(8) s[4];
  int16_t   s[4];
  struct{ int16_t   x, y, z, w; };
  struct{ int16_t   s0, s1, s2, s3; };
  struct{ short2  lo, hi; };
  short2     v2[2];
//  cl_short4     v4;
} short4;

/**
 * \union short8
 * \brief Ensures maximal compatability for storage via `union`s for eight (8) `short`s.
 */
typedef union { //short8
//  int16_t   CL_ALIGNED(16) s[8];
  int16_t    s[8];
  struct{ int16_t   x, y, z, w; };
  struct{ int16_t   s0, s1, s2, s3, s4, s5, s6, s7; };
  struct{ short4  lo, hi; };
  short2     v2[4];
  short4     v4[2];
//  cl_short8     v8;
} short8;

/**
 * \union short16
 * \brief Ensures maximal compatability for storage via `union`s for sixteen (16)
 * `short`s.
 */
typedef union { //short16
//  int16_t  CL_ALIGNED(32) s[16];
  int16_t   s[16];
  struct{ int16_t  x, y, z, w, __spacer4, __spacer5, __spacer6, __spacer7, __spacer8, __spacer9, sa, sb, sc, sd, se, sf; };
  struct{ int16_t  s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, sA, sB, sC, sD, sE, sF; };
  struct{ short8 lo, hi; };
  short2     v2[8];
  short4     v4[4];
  short8     v8[2];
//  cl_short16    v16;
} short16;

/**
 * \union uint2
 * \brief Ensures maximal compatability for storage via `union`s for two (2) unsigned
 * `int`s.
 */
typedef union { //uint2
//  uint32_t  CL_ALIGNED(8) s[2];
  uint32_t   s[2];
  struct{ uint32_t  x, y; };
  struct{ uint32_t  s0, s1; };
  struct{ uint32_t  lo, hi; };
//  cl_uint2 v2;
} uint2;

/**
 * \union uint3
 * \brief Ensures maximal compatability for storage via `union`s for three (3) unsigned
 * `int`s.
 */
typedef union { //uint3
  uint32_t   s[3];
  struct{ uint32_t  x, y, z; };
  struct{ uint32_t  r, g, b; };
} uint3;

/**
 * \union uint4
 * \brief Ensures maximal compatability for storage via `union`s for four (4) unsigned
 * `int`s.
 */
typedef union { //uint4
//  uint32_t  CL_ALIGNED(16) s[4];
  uint32_t   s[4];
  struct{ uint32_t   x, y, z, w; };
  struct{ uint32_t   s0, s1, s2, s3; };
  struct{ uint2  lo, hi; };
  uint2 v2[2];
  uint3 xyz;
//  cl_uint4 v4;
} uint4;

/**
 * \union uint8
 * \brief Ensures maximal compatability for storage via `union`s for eight (8) unsigned
 * `int`s.
 */
typedef union { //uint8
//  uint32_t   CL_ALIGNED(32) s[8];
  uint32_t    s[8];
  struct{ uint32_t   x, y, z, w; };
  struct{ uint32_t   s0, s1, s2, s3, s4, s5, s6, s7; };
  struct{ uint4  lo, hi; };
  uint2 v2[4];
  uint4 v4[2];
//  cl_uint8 v8;
} uint8;

/**
 * \union uint16
 * \brief Ensures maximal compatability for storage via `union`s for sixteen (16)
 * unsigned `int`s.
 */
typedef union { //uint16
//  uint32_t  CL_ALIGNED(64) s[16];
  uint32_t   s[16];
  struct{ uint32_t  x, y, z, w, __spacer4, __spacer5, __spacer6, __spacer7, __spacer8, __spacer9, sa, sb, sc, sd, se, sf; };
  struct{ uint32_t  s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, sA, sB, sC, sD, sE, sF; };
  struct{ uint8 lo, hi; };
  uint2 v2[8];
  uint4 v4[4];
  uint8 v8[2];
//  cl_uint16 v16;
} uint16;

/**
 * \union float2
 * \brief Ensures maximal compatability for storage via `union`s for two (2) single
 * precision floating points.
 */
typedef union { //float2
//  float  CL_ALIGNED(8) s[2];
  float   s[2];
  struct{ float  x, y; };
  struct{ float  s0, s1; };
  struct{ float  lo, hi; };
//  cl_float2 v2;
} float2;

/**
 * \union float3
 * \brief Ensures maximal compatability for storage via `union`s for three (3) single
 * precision floating points.
 *
 * \attention Scandy Core does not use `float3`s, as there are inconsistencies in how
 * varying GPUs handle them. We, therfore, declare `float3` as a `float4` and
 * accordingly pad with 0.
 */
typedef union { //float3
  float s[4];
  struct{ float x, y, z, w; };

#ifdef ENABLE_EXPERIMENTAL
  friend class hiberlite::access;
  template<class Archive>
  void hibernate(Archive & ar)
  {
    ar & HIBERLITE_NVP(x);
    ar & HIBERLITE_NVP(y);
    ar & HIBERLITE_NVP(z);
    ar & HIBERLITE_NVP(w);
  }
#endif
} float3;

/**
 * \union float4
 * \brief Ensures maximal compatability for storage via `union`s for four (4)
 * single precision floating points.
 */
typedef union { //float4
//  float  CL_ALIGNED(16) s[4];
  float   s[4];
  struct{ float   x, y, z, w; };
  struct{ float   s0, s1, s2, s3; };
  struct{ float2  lo, hi; };
  float2 v2[2];
  float3 xyz;
//  cl_float4 v4;
} float4;

/**
 * \union float8
 * \brief Ensures maximal compatability for storage via `union`s for eight (8)
 * single precision floating points.
 */
typedef union { //float8
//  float   CL_ALIGNED(32) s[8];
  float    s[8];
  struct{ float   x, y, z, w; };
  struct{ float   s0, s1, s2, s3, s4, s5, s6, s7; };
  struct{ float4  lo, hi; };
  float2 v2[4];
  float4 v4[2];
//  cl_float8 v8;
} float8;

/**
 * \union float16
 * \brief Ensures maximal compatability for storage via `union`s for sixteen
 * (16) single precision floating points.
 */
typedef union { //float16
//  float  CL_ALIGNED(64) s[16];
  float   s[16];
  struct{ float  x, y, z, w, __spacer4, __spacer5, __spacer6, __spacer7, __spacer8, __spacer9, sa, sb, sc, sd, se, sf; };
  struct{ float  s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, sA, sB, sC, sD, sE, sF; };
  struct{ float8 lo, hi; };
  float2 v2[8];
  float4 v4[4];
  float8 v8[2];
//  cl_float16 v16;
} float16;

typedef float16 Mat4f;

/**
 * \struct _half4
 * \brief Define `struct` for half floats.
 * \attention We do not need to define `half4` if we are on CL.
 */
#if !IS_A_CL_HEADER_STRING
typedef struct _half4{
  half_float::half x, y, z, w; ;
} half4;
#endif // endif !IS_A_CL_HEADER_STRING


// if we didn't IS_A_CL_HEADER_STRING we need to close the namespace
#if !IS_A_CL_HEADER_STRING
}}
#endif // endif !IS_A_CL_HEADER_STRING


#endif // Scandy_vector_types_h
