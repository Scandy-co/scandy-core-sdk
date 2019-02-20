/****************************************************************************\
 * Copyright (C) 2019 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#if ENABLE_VTK && ENABLE_DRACO

#ifndef Scandy_CreateDracoMeshFromPolyData_h
#define Scandy_CreateDracoMeshFromPolyData_h

#include <scandy/utilities/vector_types.h>

#include <draco/mesh/mesh.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkIdTypeArray.h>

namespace scandy { namespace utilities {

  //--------------------------------------------------------------------------
  // The threaded core of the algorithm
  struct CreateDracoMeshFromPolyData
  {
  public:
    vtkPolyData* PolyData;

    draco::Mesh * DracoMesh;

    int Pos_att_id;
    int Normal_att_id;
    int Tex_coord_att_id;
    int Color_att_id;
    draco::PointAttribute *Pos_att;
    draco::PointAttribute *Normal_att;
    draco::PointAttribute *Tex_coord_att;


    CreateDracoMeshFromPolyData(draco::Mesh * dracoMesh, vtkPolyData* polyData) :
    DracoMesh(dracoMesh), PolyData(polyData)
    {
      uchar *inColors = nullptr;
      if( polyData->GetPointData()->GetScalars("RGB") ){
        inColors = static_cast<uchar*>(polyData->GetPointData()->GetScalars("RGB")->GetVoidPointer(0));
      }
      // Point normals
      vtkFloatArray* vert_normals = vtkFloatArray::SafeDownCast(polyData->GetPointData()->GetNormals());
      // Get the texture coordinates
      vtkFloatArray* texture_coords = vtkFloatArray::SafeDownCast(polyData->GetPointData()->GetTCoords());

      // Encode vertex data.
      int num_points = polyData->GetNumberOfPoints();
      int num_faces = polyData->GetNumberOfCells();
      dracoMesh->set_num_points(num_points);
      dracoMesh->SetNumFaces(num_faces);

      bool use_identity_mapping = true;
      if( vert_normals ){
        draco::GeometryAttribute normal_va;
        normal_va.Init(draco::GeometryAttribute::NORMAL, nullptr, 3, draco::DT_FLOAT32, false, sizeof(float) * 3, 0);
        Normal_att_id = dracoMesh->AddAttribute(normal_va, use_identity_mapping, num_points);
      }

      if( texture_coords){
        draco::GeometryAttribute texture_va;
        texture_va.Init(draco::GeometryAttribute::TEX_COORD, nullptr, 2, draco::DT_FLOAT32, false, sizeof(float) * 2, 0);
        Tex_coord_att_id = dracoMesh->AddAttribute(texture_va, use_identity_mapping, num_points);
      }

      // TODO: replace (GeometryAttribute::TYPE, nullptr) -> (GeometryAttribute::Type, DataBuffer(vtkType))
      draco::GeometryAttribute va;
      va.Init(draco::GeometryAttribute::POSITION, nullptr, 3, draco::DT_FLOAT32, false, draco::DataTypeLength(draco::DT_FLOAT32) * 3, 0);
      Pos_att_id = dracoMesh->AddAttribute(va, use_identity_mapping, num_points);

      Pos_att = dracoMesh->attribute(Pos_att_id);
      Normal_att = dracoMesh->attribute(Normal_att_id);
      Tex_coord_att = dracoMesh->attribute(Tex_coord_att_id);
    }

    void operator() (vtkIdType begin, vtkIdType endPtId)
    {
      draco::Mesh* dracoMesh = this->DracoMesh;
      vtkPolyData* polyData = this->PolyData;
      float *inPts = static_cast<float*>(polyData->GetPoints()->GetVoidPointer(0));
      uchar *inColors = nullptr;
      if( polyData->GetPointData()->GetScalars("RGB") ){
        inColors = static_cast<uchar*>(polyData->GetPointData()->GetScalars("RGB")->GetVoidPointer(0));
      }
      // Point normals
      vtkFloatArray* vert_normals = vtkFloatArray::SafeDownCast(polyData->GetPointData()->GetNormals());
      // Get the texture coordinates
      vtkFloatArray* texture_coords = vtkFloatArray::SafeDownCast(polyData->GetPointData()->GetTCoords());

      draco::PointAttribute* pos_att = this->Pos_att;
      draco::PointAttribute* normal_att = this->Normal_att;
      draco::PointAttribute* tex_coord_att = this->Tex_coord_att;

      vtkIdType pointsPerCellR = 3;

      for ( vtkIdType cellId = begin ; cellId < endPtId; cellId++)
      {
        vtkSmartPointer<vtkIdList> pointIds = vtkSmartPointer<vtkIdList>::New();
        polyData->GetCellPoints(cellId, pointIds);
        vtkIdType pointsPerCell = pointIds->GetNumberOfIds();

        draco::Mesh::Face draco_face;

        if( pointsPerCell != pointsPerCellR ){
          // Only support triangles ya jerk
          draco_face[0] = draco_face[1] = draco_face[2] = 0;
          continue;
        }

        for (vtkIdType p = 0; p < pointsPerCellR; p++) {
          vtkIdType ptId = pointIds->GetId(p);
          if( ptId < 0 ){
            // WTF!?
            continue;
          }
          float *pt = inPts + 3 * ptId;
          // Set the draco_face to the right
          draco_face[p] = (uint64_t) ptId;

          pos_att->SetAttributeValue(draco::AttributeValueIndex(ptId), pt);
          if( vert_normals ){
            float* normal = vert_normals->GetPointer(ptId);
            normal_att->SetAttributeValue(draco::AttributeValueIndex(ptId), normal);
          }
          if( texture_coords ){
            float* uv_pt = (float*) texture_coords->GetPointer(ptId * 2);
            tex_coord_att->SetAttributeValue(draco::AttributeValueIndex(ptId), uv_pt);
          }

        } // end p < pointsPerCellR

        draco::FaceIndex face_index(cellId);
        dracoMesh->SetFace(face_index, draco_face);

      } // end for
    } // end () function operator

  }; // end CreateDracoMeshFromPolyData

}} //namespace

#endif // #define Scandy_CreateDracoMeshFromPolyData_h

#else // #if ENABLE_VTK
struct CreateDracoMeshFromPolyData {
  CreateDracoMeshFromPolyData()
};
#endif // #if ENABLE_VTK
