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
 * \file Lap.h
 * \brief Furnishes class for `Lap`, a timer utility.
 */

#ifndef Scandy_Lap_h
#define Scandy_Lap_h

#include <chrono>

namespace scandy { namespace utilities {

/**
 * \class Lap
 * \breif Furnishes helper methods for measuring temporal durations spanning
 * time points.
 *
 * Uses time library `<chrono>`.
 * For more inforamtion, see: http://www.cplusplus.com/reference/chrono/
 */
class Lap {
public:
  std::chrono::time_point<std::chrono::system_clock> m_tp;
  std::chrono::time_point<std::chrono::system_clock> m_tp_0;
public:
  Lap()
  : m_tp(std::chrono::system_clock::now())
  , m_tp_0(m_tp)
  {
  }
  double total(){
    auto tp = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = tp - m_tp_0;
    return elapsed.count();
  }
  double operator()(){
    auto tp = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = tp - m_tp;
    m_tp = tp;
    return elapsed.count();
  }
};
}}

#endif // Scandy_Lap_h
