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

#include <scandy/tests/test_macros.h>


namespace test_macro_tests { namespace inner_ns {
  /* TODO@kaben: propagate convention of placing entire body of test in
   * namespace based on file name. */
  
  /* Expands to body of
   *
   *   ScandyCoreTest_TestMacros_Separated1(int blah);
   */
  SCANDY_TEST_BODY(TestMacros, Separated1, int blah){
    int foo = blah; blah = foo;
  }
  GTEST_TEST(TestMacros, CallSeparated1){
    /* Direct call to
     *
     *   ScandyCoreTest_TestMacros_Separated1(int blah);
     */
    ScandyCoreTest_TestMacros_Separated1(1);
  }

  /* Expands to declaration of
   *
   *   ScandyCoreTest_TestMacros_Separated2(int blah);
   *
   * and definition
   *
   *   ScandyCoreTest_TestMacros_Separated2(int blah){
   *     int foo = blah; blah = foo;
   *   }
   *   
   */
  SCANDY_TEST_DECL(TestMacros, Separated2, int blah);
  SCANDY_TEST_BODY(TestMacros, Separated2, int blah){
    int foo = blah; blah = foo;
  }
  GTEST_TEST(TestMacros, CallSeparated2){
    /* Expands to call to
     *
     *   ScandyCoreTest_TestMacros_Separated2(int blah);
     */
    SCANDY_TEST_CALL(TestMacros, Separated2, 1);
  }
  /* Expands to Google Test calling
   *
   *   ScandyCoreTest_TestMacros_Separated2(int blah);
   */
  SCANDY_GTEST_CALL(TestMacros, Separated2, 1);
  
  /* Similar to above, a separate definition and call of
   *
   *   ScandyCoreTest_TestMacros_Separated3();
   *
   * which has no arguments.
   */
  SCANDY_TEST_BODY(TestMacros, Separated3){
    int foo; foo = 1;
  }
  SCANDY_GTEST_CALL(TestMacros, Separated3);
  
  /* Similar to above, a combined definition and call of
   *
   *   ScandyCoreTest_TestMacros_Combined();
   *
   * which has no arguments.
   */
  SCANDY_TEST(TestMacros, Combined){
    int foo; foo = 1;
  }
}}

GTEST_TEST(TestMacros, Call2Separated1){
  /* Expands to call to namespaced
   *
   *   test_macro_tests::ScandyCoreTest_TestMacros_Separated1(int blah);
   */
  test_macro_tests::inner_ns::SCANDY_TEST_CALL(TestMacros, Separated1, 1);
}

/* Expands to namespaced declaration:
 *
 *   test_macro_tests::ScandyCoreTest_TestMacros_Separated2(int blah);
 */

namespace test_macro_tests { namespace inner_ns {
SCANDY_TEST_DECL(TestMacros, Separated2, int blah);
}}
GTEST_TEST(TestMacros, Call2Separated2){
  test_macro_tests::inner_ns::SCANDY_TEST_CALL(TestMacros, Separated2, 1);
}
