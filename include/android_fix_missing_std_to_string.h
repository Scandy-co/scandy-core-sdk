/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * For distribution.
 *
 \****************************************************************************/

#ifndef Scandy_android_fix_missing_std_to_string_h
#define Scandy_android_fix_missing_std_to_string_h

#include <string>
#include <sstream>
#include <cstdlib>

/* The following fix for Android build error "no member named 'to_string' in
 * namespace 'std'" is based on
 * http://stackoverflow.com/questions/22774009/android-ndk-stdto-string-support
 * @kaben
 */
namespace std {

template <typename T> std::string to_string(T v){
  std::ostringstream os;
  os << v;
  return os.str();
}

/**
 * fix for android missing std::stoll
 * @param  v [description]
 * @return   [description]
 */
template <typename T> long long stoll(T v){
  std::ostringstream os;
  os << v;
  long long l = (long long)std::atoi(os.str().c_str());
  return l;
}

/**
 * fix for android missing std::stoll
 * @param  v [description]
 * @return   [description]
 */
template <typename T> unsigned long long stoull(T v){
  std::ostringstream os;
  os << v;
  unsigned long long l = (unsigned long long)std::atoi(os.str().c_str());
  return l;
}

/**
 * fix for android missing std::stoll
 * @param  v [description]
 * @return   [description]
 */
template <typename T> long double stold(T v){
  std::ostringstream os;
  os << v;
  long double l = (long double)std::atoi(os.str().c_str());
  return l;
}

/**
 * fix for missing std::sscanf
 */
template <typename... Args> int sscanf(const char * dest, const char * format, Args... args) {
  return sscanf(dest, format, args...);
}

/**
 * fix for missing std::sprintf
 */
template <typename... Args> int sprintf(char* dest, const char* format, Args... args) {
  return sprintf(dest, format, args...);
}

} // end namespace

#endif // Scandy_android_fix_missing_std_to_string_h
