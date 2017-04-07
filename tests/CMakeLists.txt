# Copyright (C) 2016 Scandy
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 3.1)
project(ScandyCoreTests)

# if the ScandyCore_DIR is not set, set it to the default location
if( NOT ScandyCore_DIR)
  set(ScandyCore_DIR "${ScandyCoreCppExamples_SOURCE_DIR}/dependencies/ScandyCore/")
endif()
# And now add the Scandy Core package
find_package(ScandyCore)

# Scandy Core relies on C++14
set(CMAKE_CXX_STANDARD 14)

# link the ScandyCore lib directory
link_directories(
  "${ScandyCore_LIB_DIRS}"
)

# include the ScandyCore include directory
include_directories(
  "${ScandyCore_INCLUDE_DIRS}"
)

add_gtest(test_macro_tests "${common_test_libs}")
