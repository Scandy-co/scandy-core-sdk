/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * For distribution.
 \****************************************************************************/

/* Scandy test macros. See example usage in
 * distributable/test/test_macro_tests.cpp.
 */

#ifndef Scandy_test_macros_h
#define Scandy_test_macros_h


#include <scandy.h>
#include <gtest/gtest.h>


#define SHORT_TEST_NAME(test_case_name, test_name) \
  #test_case_name#test_name

#define SCANDY_TEST_NAME(test_case_name, test_name) \
  ScandyCoreTest_ ## test_case_name ## _ ## test_name

#define SCANDY_TEST_BODY(test_case_name, test_name, ...) \
  void SCANDY_TEST_NAME(test_case_name, test_name)(__VA_ARGS__)

#define SCANDY_TEST_DECL(test_case_name, test_name, ...) \
  void SCANDY_TEST_NAME(test_case_name, test_name)(__VA_ARGS__);

#define SCANDY_NS_TEST_DECL(cpp_namespace, test_case_name, test_name, ...) \
  namespace cpp_namespace { \
    void SCANDY_TEST_NAME(test_case_name, test_name)(__VA_ARGS__); \
  }

#define SCANDY_TEST_CALL(test_case_name, test_name, ...) \
  SCANDY_TEST_NAME(test_case_name, test_name)(__VA_ARGS__);

#define SCANDY_GTEST_CALL(test_case_name, test_name, ...) \
  GTEST_TEST(test_case_name, test_name) { \
    SCANDY_TEST_CALL(test_case_name, test_name, __VA_ARGS__); \
  };

#define SCANDY_TEST(test_case_name, test_name) \
  void SCANDY_TEST_NAME(test_case_name, test_name)(); \
  SCANDY_GTEST_CALL(test_case_name, test_name) \
  SCANDY_TEST_BODY(test_case_name, test_name)


#endif // Scandy_test_macros_h
