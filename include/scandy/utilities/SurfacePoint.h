/****************************************************************************\
 * Copyright (C) 2018 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

/**
 * \file SurfacePoint.h
 * \brief Furnishes a class for `SurfacePoint`.
 */

#ifndef Scandy_SurfacePoint_h
#define Scandy_SurfacePoint_h

#if !IS_A_CL_HEADER_STRING
#include <scandy/utilities/struct_types.h>
#include <scandy/utilities/vector_types.h>
#endif //endif !IS_A_CL_HEADER_STRING

#if !IS_A_CL_HEADER_STRING
namespace scandy { namespace utilities {
#endif //endif !IS_A_CL_HEADER_STRING

#if !IS_A_CL_HEADER_STRING
typedef half_float::half half;
#endif //endif !IS_A_CL_HEADER_STRING

typedef struct _SCHalf3 {
  half x;
  half y;
  half z;
  // half w;

#if !IS_A_CL_HEADER_STRING
  template <class Archive>
  void serialize(Archive& archive){
    archive((float)x, (float)y, (float)z);
//    archive(x.data_, y.data_, z.data_);
  }
#endif //endif !IS_A_CL_HEADER_STRING

} SCHalf3;

/**
 * \class SurfacePoint
 * \brief A class that represents a point on a surface
 */
typedef struct _SurfacePoint {
  // The color of the point
  uchar4 color;
  // The vertex of the point, in meters
  SCHalf3 vert;
  // The normal of the point
  SCHalf3 normal;

#if !IS_A_CL_HEADER_STRING
  template <class Archive>
  void serialize(Archive& archive){
    archive(color, vert, normal);
  }
#endif //endif !IS_A_CL_HEADER_STRING

} SurfacePoint;

inline SurfacePoint setSurfacePointVertex(SurfacePoint surfacePoint, float4 in){
  surfacePoint.vert.x = in.x;
  surfacePoint.vert.y = in.y;
  surfacePoint.vert.z = in.z;
  // surfacePoint.vert.w = in.w;
  return surfacePoint;
}

inline SurfacePoint setSurfacePointVertex(SurfacePoint surfacePoint, float3 in){
  surfacePoint.vert.x = in.x;
  surfacePoint.vert.y = in.y;
  surfacePoint.vert.z = in.z;
  // surfacePoint.vert.w = 1.0f;
  return surfacePoint;
}

inline float4 getSurfacePointVertexFloat4(SurfacePoint surfacePoint){
  return scandy_make_float4(
    surfacePoint.vert.x,
    surfacePoint.vert.y,
    surfacePoint.vert.z,
    // surfacePoint.vert.w
    1.0f
  );
}

inline SurfacePoint setSurfacePointNormal(SurfacePoint surfacePoint, float4 in){
  surfacePoint.normal.x = in.x;
  surfacePoint.normal.y = in.y;
  surfacePoint.normal.z = in.z;
  // surfacePoint.normal.w = in.w;
  return surfacePoint;
}

inline SurfacePoint setSurfacePointNormal(SurfacePoint surfacePoint, float3 in){
  surfacePoint.normal.x = in.x;
  surfacePoint.normal.y = in.y;
  surfacePoint.normal.z = in.z;
  // surfacePoint.normal.w = 1.0f;
  return surfacePoint;
}

inline float4 getSurfacePointNormalFloat4(SurfacePoint surfacePoint){
  return scandy_make_float4(
    surfacePoint.normal.x,
    surfacePoint.normal.y,
    surfacePoint.normal.z,
    // surfacePoint.normal.w
    1.0f
  );
}

inline SurfacePoint setSurfacePointColor(SurfacePoint surfacePoint, uchar4 in){
  surfacePoint.color.x = in.x;
  surfacePoint.color.y = in.y;
  surfacePoint.color.z = in.z;
  surfacePoint.color.w = in.w;
  return surfacePoint;
}

inline SurfacePoint setSurfacePointColor(SurfacePoint surfacePoint, float4 in){
  surfacePoint.color.x = in.x;
  surfacePoint.color.y = in.y;
  surfacePoint.color.z = in.z;
  surfacePoint.color.w = in.w;
  return surfacePoint;
}

inline SurfacePoint setSurfacePointColor(SurfacePoint surfacePoint, float3 in){
  surfacePoint.color.x = in.x;
  surfacePoint.color.y = in.y;
  surfacePoint.color.z = in.z;
  surfacePoint.color.w = 255;
  return surfacePoint;
}


#if !IS_A_CL_HEADER_STRING
}}
#endif //endif !IS_A_CL_HEADER_STRING


#endif //ifndef Scandy_SurfacePoint_h
