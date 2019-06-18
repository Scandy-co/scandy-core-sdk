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

#ifndef Scandy_CreateMeshFrameFromDracoMesh_h
#define Scandy_CreateMeshFrameFromDracoMesh_h

#include <scandy/utilities/MeshFrame.h>
#include <scandy/utilities/CameraIntrinsics.h>
#include <scandy/utilities/vector_types.h>

#include "draco/mesh/mesh.h"

#include <vtkIdTypeArray.h>

namespace scandy { namespace utilities {

  //--------------------------------------------------------------------------
  // The threaded core of the algorithm
  struct CreateMeshFrameFromDracoMesh
  {
  public:
    const MeshPoint *Points;
    const MeshFace *Cells;
    draco::Mesh * DracoMesh;

    int Pos_att_id;
    int Normal_att_id;
    int Tex_coord_att_id;
    int Color_att_id;
    draco::PointAttribute *Pos_att;
    draco::PointAttribute *Normal_att;
    draco::PointAttribute *Tex_coord_att;


    CreateMeshFrameFromDracoMesh(MeshPoint *points, MeshFace *cells, draco::Mesh * dracoMesh) :
    Points(points), Cells(cells), DracoMesh(dracoMesh)
    {
      Pos_att_id = dracoMesh->GetNamedAttributeId(draco::GeometryAttribute::POSITION);
      Normal_att_id = dracoMesh->GetNamedAttributeId(draco::GeometryAttribute::NORMAL);
      Tex_coord_att_id = dracoMesh->GetNamedAttributeId(draco::GeometryAttribute::TEX_COORD);
      Color_att_id = dracoMesh->GetNamedAttributeId(draco::GeometryAttribute::COLOR);
      Pos_att = dracoMesh->attribute(Pos_att_id);
      Normal_att = dracoMesh->attribute(Normal_att_id);
      Tex_coord_att = dracoMesh->attribute(Tex_coord_att_id);
    }

    void operator() (vtkIdType begin, vtkIdType endPtId)
    {
      MeshPoint *points = (MeshPoint*)this->Points;
      MeshFace *cells= (MeshFace*)this->Cells;
      draco::Mesh* draco_mesh = this->DracoMesh;

      draco::PointAttribute* pos_att = this->Pos_att;
      draco::PointAttribute* normal_att = this->Normal_att;
      draco::PointAttribute* tex_coord_att = this->Tex_coord_att;

      for ( vtkIdType cellId = begin ; cellId < endPtId; cellId++)
      {
        MeshFace& mesh_face = cells[cellId];
        draco::FaceIndex face_idx(cellId);

        const auto &draco_face = draco_mesh->face(face_idx);
        mesh_face.point_ids[0] = draco_face[0].value();
        mesh_face.point_ids[1] = draco_face[1].value();
        mesh_face.point_ids[2] = draco_face[2].value();

        for( uint8_t i = 0; i < 3 ; i++ ){
          // Get the point from the face
          draco::PointIndex pt_idx(mesh_face.point_ids[i]);
          MeshPoint &mesh_point = points[pt_idx.value()];

          // Get the position attribute into the MeshPoint vert
          pos_att->GetValue(pos_att->mapped_index(pt_idx), &mesh_point.vert.s);

          if (this->Normal_att_id >= 0) {
            // Get the normal attribute into the MeshPoint normal
            normal_att->GetValue(normal_att->mapped_index(pt_idx), &mesh_point.normal.s);
          }
          if (this->Tex_coord_att_id >= 0) {
            // Get the texture coord attribute into the MeshPoint uv_pt
            tex_coord_att->GetValue(tex_coord_att->mapped_index(pt_idx), &mesh_point.uv_pt.s);
          }
        } // end i < 3

      } // end for
    } // end () function operator

  }; // end CreateMeshFrameFromDracoMesh

}} //namespace

#endif // #define Scandy_CreateMeshFrameFromDracoMesh_h

#else // #if ENABLE_VTK
struct CreateMeshFrameFromDracoMesh {
  CreateMeshFrameFromDracoMesh()
};
#endif // #if ENABLE_VTK
