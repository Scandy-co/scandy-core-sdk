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

/* This is a convenience header for reducing compilation time. It allows
 * including standard library headers in your own header files, without the
 * need for double include guards, by writing
 *
 *   #include <std_foo.h>
 *
 * instead of
 *
 *   #include <foo>
 *
 * This works for compilers implementing "#pragma once".
 */

#pragma once


#ifndef CL_HPP_MINIMUM_OPENCL_VERSION
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#endif

#ifndef CL_HPP_TARGET_OPENCL_VERSION
#define CL_HPP_TARGET_OPENCL_VERSION 120
#endif

#define CL_HPP_ENABLE_EXCEPTIONS
#define  _VARIADIC_MAX 10

#ifndef OPENCL_VERSION
#include <CL/cl2.hpp>
#else // #ifndef OPENCL_VERSION
#if OPENCL_VERSION == 120
#include <CL/cl.hpp>
#endif // #if OPENCL_VERSION == 120
#endif // #ifndef OPENCL_VERSION
