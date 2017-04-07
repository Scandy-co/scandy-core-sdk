/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_NormalsViewport_h
#define Scandy_NormalsViewport_h

#include <scandy/core/status.h>
#include <scandy/core/visualizer/Viewport.h>

/* Begin VTK includes */
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkTexture.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkLine.h>

#include <vtksys/SystemTools.hxx>
/* End VTK includes */

/* Begin cpp includes */
#include <string>
/* End cpp includes */

namespace scandy { namespace core {

/**
 * \class NormalsViewport
 * \brief NormalsViewport is a subclass of Viewport with the specific purpose of
 * visualizing normals.
 */
class NormalsViewport : public Viewport {
public:
  /* These are for visualizing vertices, as green dots, for which we could
   * compute the approximate surface normal; typically, these are non-edge
   * vertices.
   */
  vtkPoints *m_vertices;
  vtkPolyData *m_vertex_poly;
  vtkVertexGlyphFilter *m_vertex_filter;
  vtkPolyDataMapper *m_vertex_mapper;
  vtkActor *m_vertex_actor;
  /* We visualize edge vertices as red dots. We can't get a good approximation
   * for the surface normal at these points.
   */
  vtkPoints *m_edge_vertices;
  vtkPolyData *m_edge_vertex_poly;
  vtkVertexGlyphFilter *m_edge_vertex_filter;
  vtkPolyDataMapper *m_edge_vertex_mapper;
  vtkActor *m_edge_vertex_actor;
  /* We visualize surface normals as short white lines. Each of these should be
   * attached to a green dot corresponding to the surface point where we're
   * computing the approximate normal.
   */
  vtkPoints *m_normals;
  vtkLine *m_normal_line;
  vtkCellArray *m_normal_lines;
  vtkPolyData *m_normal_poly;
  vtkPolyDataMapper *m_normal_mapper;
  vtkActor *m_normal_actor;
public:
  NormalsViewport();
  ~NormalsViewport();
};

}}

#endif // Scandy_NormalsViewport_h
