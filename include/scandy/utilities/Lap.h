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

#ifndef Scandy_Lap_h
#define Scandy_Lap_h

#include <chrono>

namespace scandy { namespace utilities {

class Lap {
public:
  std::chrono::time_point<std::chrono::system_clock> m_tp;
public:
  Lap()
  : m_tp(std::chrono::system_clock::now())
  {
  }
  double total(){
    auto tp = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = tp - m_tp;
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
