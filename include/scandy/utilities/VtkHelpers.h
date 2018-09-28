/****************************************************************************\
 * Copyright (C) 2017 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

/**
 * \file VtkHelpers.h
 * \brief Useful helpers for common VTK operations
 */

#ifndef Scandy_VtkHelpers_h
#define Scandy_VtkHelpers_h

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
class vtkPolyDataAlgorithm;
class vtkPolyData;

#include <scandy/utilities/vector_types.h>

namespace scandy { namespace utilities {

void colorizePolyData(vtkSmartPointer<vtkPolyData> poly_data, const float rgb[3], bool color_points=false);
void colorizePolyData(vtkSmartPointer<vtkPolyData> poly_data, const float r, const float g, const float b, bool color_points=false);

vtkSmartPointer<vtkPolyData> combinePolyData(vtkPolyData* poly_data_1, vtkPolyData* poly_data_2);
vtkSmartPointer<vtkPolyData> combinePolyData(vtkPolyDataAlgorithm *algo_1, vtkPolyDataAlgorithm *algo_2);

vtkSmartPointer<vtkMatrix4x4> getVtkMatrix4x4FromMat4f(scandy::utilities::Mat4f mat4f);
scandy::utilities::Mat4f getMat4fFromVtkMatrix4x4(vtkSmartPointer<vtkMatrix4x4> matrix);
void printVtkMatrix4x4(vtkSmartPointer<vtkMatrix4x4> matrix, const char* name="matrix");

vtkSmartPointer<vtkPolyData> loadMesh(std::string file_path, bool clean_data=false);
bool savePLY(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data);
bool saveOBJ(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data);
bool saveSTL(std::string file_path, vtkSmartPointer<vtkPolyData> poly_data);

vtkSmartPointer<vtkPolyData> cleanAndRegenerateNormalsPolyData(vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> decimatePolyData(float percent, vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> smoothPolyData(int iterations, vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> fillHolesPolyData(float hole_size, vtkSmartPointer<vtkPolyData> poly_data);
vtkSmartPointer<vtkPolyData> adjustHSVPolyData(float percent[3], vtkSmartPointer<vtkPolyData> poly_data, bool color_points=true);

void createTextureCoords(vtkSmartPointer<vtkPolyData> polydata);

}}

#endif // Scandy_VtkHelpers_h
