/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef Scandy_GridPositions_h
#define Scandy_GridPositions_h

#include <vector>


namespace scandy { namespace core {

class GridPositions {
public:
  bool m_is_locked;
  int m_w, m_h, m_rows, m_cols;
  double m_dx, m_dy;
  std::vector<int> m_xs, m_ys;
public:
  GridPositions(int width, int height, int cols, int rows);
  bool configure(int width, int height, int cols, int rows);
  int posCt();
  double minX(int col);
  double minY(int row);
  double maxX(int col);
  double maxY(int row);
  void extents(int idx, double& mx, double& my, double& Mx, double& My);
  int getWidth();
  int getHeight();
};

}}

#endif // Scandy_GridPositions_h
