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

#ifndef Scandy_mac_metal_h
#define Scandy_mac_metal_h

// If we're compiled as Objective C/C++ get the real stuff
// #if defined(__OBJC__) || defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
// #else
// // Otherwise, just forward declare it
// class NSError{};
// class MTLDevice{};
// class MTLBuffer{};
// class MTLCommandQueue{};
// class MTLCommandBuffer{};
// class MTLComputeCommandEncoder{};
// class MTLFunction{};
// class MTLComputePipelineState{};
// class MTLLibrary{};
// class MTLSize{};
//
// template<typename T> class id{};
//
// #define nil nullptr
//
// #endif

#endif // Scandy_mac_metal_h
