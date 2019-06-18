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
 * \file MeshFrame.h
 * \brief Furnishes class for `MeshFrame` and struct for `sMeshFrame`.
 */

#ifndef Scandy_MeshFrame_h
#define Scandy_MeshFrame_h

#if !IS_A_CL_HEADER_STRING
#include <scandy/utilities/DepthTrackMetadata.h>
#include <cereal/types/vector.hpp>
#endif //endif !IS_A_CL_HEADER_STRING

#if !IS_A_CL_HEADER_STRING
namespace scandy { namespace utilities {
#endif //endif !IS_A_CL_HEADER_STRING

// Define which mode to use
// #undef MESHFACE_TRIANGLE
#define MESHFACE_TRIANGLE

// Define which mode to use
// #undef MESHPOINT_COLOR_UV
#define MESHPOINT_COLOR_UV

typedef struct _MeshFace {
  // Using pure triangle meshes
#ifdef MESHFACE_TRIANGLE
  uint32_t point_ids[3];
#else
  uint32_t point_ids;
#endif

#if !IS_A_CL_HEADER_STRING
  template <class Archive>
  void serialize(Archive& archive){
    archive(point_ids);
  }
#endif //endif !IS_A_CL_HEADER_STRING

} MeshFace;

typedef struct _MeshPoint {
#ifdef MESHPOINT_COLOR_UV
  float2 uv_pt;
#else
  // The color of the point
  float4 color;
#endif

  // The vertex of the point, in meters
  float4 vert;

  // The normal of the point
  float4 normal;

#if !IS_A_CL_HEADER_STRING
  template <class Archive>
  void serialize(Archive& archive){
#ifdef MESHPOINT_COLOR_UV
    archive(uv_pt, vert, normal);
#else
    archive(color, vert, normal);
#endif
  }
#endif //endif !IS_A_CL_HEADER_STRING

  // TODO: @hcwiley figure out how to save / load as a half for smaller packets
  // template <class Archive>
  // void save( Archive& archive ) const {
  //   half4 h_color;
  //   h_color.x = color.x;
  //   h_color.y = color.y;
  //   h_color.z = color.z;
  //   h_color.w = color.w;
  //
  //   half4 h_vert;
  //   h_vert.x = vert.x;
  //   h_vert.y = vert.y;
  //   h_vert.z = vert.z;
  //   h_vert.w = vert.w;
  //
  //   half4 h_normal;
  //   h_normal.x = normal.x;
  //   h_normal.y = normal.y;
  //   h_normal.z = normal.z;
  //   h_normal.w = normal.w;
  //   archive(h_color, h_vert, h_normal);
  // }
  //
  // template <class Archive>
  // void load( Archive& archive ){
  //   half4 h_color, h_vert, h_normal;
  //   archive(h_color, h_vert, h_normal);
  //
  //   color.x = h_color.x;
  //   color.y = h_color.y;
  //   color.z = h_color.z;
  //   color.w = h_color.w;
  //   vert.x = h_vert.x;
  //   vert.y = h_vert.y;
  //   vert.z = h_vert.z;
  //   vert.w = h_vert.w;
  //   normal.x = h_normal.x;
  //   normal.y = h_normal.y;
  //   normal.z = h_normal.z;
  //   normal.w = h_normal.w;
  // }

} MeshPoint;


#if !IS_A_CL_HEADER_STRING
typedef struct _MeshFrame {
  std::vector<MeshPoint> m_mesh_points;
  // std::vector<float4> m_mesh_verts;
  // std::vector<float4> m_mesh_colors;
  // std::vector<float4> m_mesh_normals;
  std::vector<MeshFace> m_mesh_faces;
  scandy::utilities::DepthTrackMetadata m_metadata;

  template <class Archive>
  void serialize(Archive& archive){
   archive(m_metadata, m_mesh_points, m_mesh_faces);
    // archive(m_metadata, m_mesh_verts, m_mesh_colors, m_mesh_faces);
  }
} MeshFrame;
#endif //endif !IS_A_CL_HEADER_STRING

#if !IS_A_CL_HEADER_STRING
}} // end namespace
#endif //endif !IS_A_CL_HEADER_STRING

#if !IS_A_CL_HEADER_STRING
#endif // Scandy_MeshFrame_h
#endif //endif !IS_A_CL_HEADER_STRING
