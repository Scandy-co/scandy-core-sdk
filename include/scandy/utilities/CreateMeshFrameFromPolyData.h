/****************************************************************************\
 * Copyright (C) 2018 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#if ENABLE_VTK

#ifndef Scandy_CreateMeshFrameFromPolyData_h
#define Scandy_CreateMeshFrameFromPolyData_h

#include <scandy/utilities/MeshFrame.h>
#include <scandy/utilities/CameraIntrinsics.h>
#include <scandy/utilities/vector_types.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>

namespace scandy { namespace utilities {

  //--------------------------------------------------------------------------
  // The threaded core of the algorithm
  struct CreateMeshFrameFromPolyData
  {
  public:
    const MeshPoint *Points;
    const MeshFace *Cells;
    vtkPolyData* PolyData;
    CameraIntrinsics CamIntrinsics;
    Mat4f InversePose;

    CreateMeshFrameFromPolyData(MeshPoint *points, MeshFace *cells, vtkPolyData* polyData, CameraIntrinsics camIntrinsics, Mat4f inversePose) :
    Points(points), Cells(cells), PolyData(polyData), CamIntrinsics(camIntrinsics), InversePose(inversePose)
    {
    }

    void operator() (vtkIdType begin, vtkIdType endPtId)
    {
      MeshPoint *points = (MeshPoint*)this->Points;
      MeshFace *cells= (MeshFace*)this->Cells;
      vtkPolyData* polyData = this->PolyData;
      CameraIntrinsics camIntrinsics = this->CamIntrinsics;
      Mat4f inverse_pose = this->InversePose;
      float *inPts = static_cast<float*>(polyData->GetPoints()->GetVoidPointer(0));
      uchar *inColors = nullptr;
      if( polyData->GetPointData()->GetScalars("RGB") ){
        inColors = static_cast<uchar*>(polyData->GetPointData()->GetScalars("RGB")->GetVoidPointer(0));
      }
      // Point normals
      vtkFloatArray* pointNormals = vtkFloatArray::SafeDownCast(polyData->GetPointData()->GetNormals());
      // Get the texture coordinates
      vtkFloatArray* tc = nullptr;
      if( true ){
        tc = vtkFloatArray::SafeDownCast(polyData->GetPointData()->GetTCoords());
      }

      vtkIdType pointsPerCellR = 3;

      for ( vtkIdType cellId = begin ; cellId < endPtId; cellId++)
      {
        MeshFace& meshFace = cells[cellId];

        vtkSmartPointer<vtkIdList> pointIds = vtkSmartPointer<vtkIdList>::New();
        polyData->GetCellPoints(cellId, pointIds);
        vtkIdType pointsPerCell = pointIds->GetNumberOfIds();
        if( pointsPerCell != pointsPerCellR ){
          // Only support triangles ya jerk
#ifdef MESHFACE_TRIANGLE
          meshFace.point_ids[0] = meshFace.point_ids[1] = meshFace.point_ids[2] = 0;
#else
          meshFace.point_ids = 0;
#endif
          continue;
        }

        for (vtkIdType p = 0; p < pointsPerCellR; p++) {
          vtkIdType ptId = pointIds->GetId(p);
          if( ptId < 0 ){
            // WTF!?
            continue;
          }
          float *pt = inPts + 3 * ptId;
          // Get our current index
          MeshPoint& meshPoint = points[ptId];
#ifdef MESHFACE_TRIANGLE
          meshFace.point_ids[p] = (uint32_t) ptId;
#else
          meshFace.point_ids = (uint32_t) ptId;
#endif
          meshPoint.vert = {{
            static_cast<float>(pt[0]),
            static_cast<float>(pt[1]),
            static_cast<float>(pt[2]),
            1.0f
          }};
          if( pointNormals ) {
            float* normal= pointNormals->GetPointer(ptId);
            meshPoint.normal.s[0] = normal[0];
            meshPoint.normal.s[1] = normal[1];
            meshPoint.normal.s[2] = normal[2];
            meshPoint.normal.s[3] = 1.0f;
          } else {
            meshPoint.normal.s[0] = 0.0f;
            meshPoint.normal.s[1] = 0.0f;
            meshPoint.normal.s[2] = 0.0f;
            meshPoint.normal.s[3] = 1.0f;
          }
#ifdef MESHPOINT_COLOR_UV
          // Do it UV
          if( tc ){
            // TODO: allow configuring reading from vtkPolyData instead of overwriting
            float* uv_pt = (float*) tc->GetPointer(ptId * 2);
            // meshPoint.uv_pt = {{ uv_pt[0], 1.f - uv_pt[1] }};
            // transform the world point to camera coordinates
            float4 cam_pt = transform(inverse_pose, meshPoint.vert);

            // convert the camera coordinates to pixel coordinates
            // TODO use matrix math to look and be cool
            float2 pixel;
            pixel.x = camIntrinsics.m_fx * (cam_pt.x / cam_pt.z) + camIntrinsics.m_cx;
            pixel.y = camIntrinsics.m_fy * (cam_pt.y / cam_pt.z) + camIntrinsics.m_cy;

            // convert pixel to uv
            meshPoint.uv_pt.x = uv_pt[0] = std::min(std::max(pixel.x/camIntrinsics.m_width, 0.0f), 1.0f);
            meshPoint.uv_pt.y = uv_pt[1] = std::min(std::max(pixel.y/camIntrinsics.m_height, 0.0f), 1.0f);
          } else {
            meshPoint.uv_pt = {{ 0.f, 0.f}};
          }
#else
          // Do per vertex
          if( inColors != nullptr ) {
            uchar* color = inColors + 3 * ptId;
            meshPoint.color = {{
              static_cast<float>(color[0]) * 0.003921569f,
              static_cast<float>(color[1]) * 0.003921569f,
              static_cast<float>(color[2]) * 0.003921569f,
              1.f
            }};
          } else {
            meshPoint.color = {{ 1.f, 1.f, 1.f, 1.f }};
          }
#endif
        }
      } // end for
    } // end () function operator

  }; // end CreateMeshFrameFromPolyData

}} //namespace

#endif // #define Scandy_CreateMeshFrameFromPolyData_h

#else // #if ENABLE_VTK
struct CreateMeshFrameFromPolyData {
  CreateMeshFrameFromPolyData()
};
#endif // #if ENABLE_VTK
