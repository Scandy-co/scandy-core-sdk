# Scandy Core SDK

**Welcome to the wonderful world of 3D!**

## Table of Contents

* [Forward](#forward)
* [Definitions](#definitions)
* [Features Overview](#features-overview)
* [Getting Started](#getting-started)
* [Examples](#examples)

## <a name="forward"></a>Forward

Scandy Core is here to make your life easier as developer who wants to work with 3D data. Scandy Core provides a set of easy-to-use functions for viewing, loading, downloading, editing, and creating 3D files.

Scandy Core is a SDK that allows developers to easily create 3D models, track position in 3D space, and edit 3D models. Scandy Core is currently optimized to run on Android, Mac OS X, and Linux. Scandy Core is written in cross-platform C++ and has many proprietary optimizations that allow it to run on powerful computing platforms like render servers or workstations, and then to gracefully scale down to operate on processor and memory-constrained devices, like smart phones or tablets. Files created with Scandy Core are capable of running on all platforms regardless of where they were created. Scandy Core also exports industry standard 3D files like OBJ, PLY, and STL.

## <a name="definitions"></a>Definitions

_X is **Supported** means the feature is currently implemented_

| Term  | Supported |  Definition |
|---|:---:|---|
| _SLAM_  | X  | Denotes simultaneous localization and mapping. See Wikipedia entry re: [SLAM](https://en.wikipedia.org/wiki/Simultaneous_localization_and_mapping).|
| _pico flexx_ | X | The [pico flexx](http://pmdtec.com/picoflexx) is a small USB 3D sensor made by [pmd](pmdtec.com) that allows capturing of live 3D data. |
| _RRF_ | X  |  Royale raw file. A file extension that denotes/wraps point cloud data as provisioned by a live sensor stream. If you have been using royale for awhile you might have a few of these laying around that you want to re-examine. |
| _TSDF_ | X | Truncated signed distance function; a voxel representative of a given scan created in memory by Scandy Core; more specifically, `TSDF` stores values used for attempting accurate representation of a volumetric surface. Originally defined in paper ["A Volumetric Method for Building Complex Models from Range Images"](http://graphics.stanford.edu/papers/volrange/volrange.pdf). Also, see Wikipedia entries for [signed distance function](https://en.wikipedia.org/wiki/Signed_distance_function) and on [volume rendering](https://en.wikipedia.org/wiki/Volume_rendering). |
| _Mesh_ | X | A mesh represents a 3D scene or object in a standardized format such as [.OBJ](https://en.wikipedia.org/wiki/Wavefront_.obj_file) or [.PLY](https://en.wikipedia.org/wiki/PLY_(file_format)). Scandy Core can generate a mesh for any scan taken, and then also save that mesh into a PLY or OBJ format. |
| _SCRF_ |  | Scandy Core raw file; a proprietary file extension denoting those contents of a scan file saved to disk. Packages a live sensor stream (or `RRF`), along with the parameters used to capture a given volume (i.e., scanning configuration). In future versions, `SCRF`s may also be extended to include depths maps and color frames. More generally, SCRF refers to those contents of a scan file distinguishable from any derivative meshes. |
| _IMU_  |   | Inertial measurement unit. Data encompassing a host device's specific force and angular orientation is fed into Scandy Core for enhancements in tracking. See [Wikipedia entry](https://en.wikipedia.org/wiki/Inertial_measurement_unit).  |


## <a name="features-overview"></a>Features Overview

### 3D Tracking (SLAM)

Keeping track of where you are in 3D space is one of the most fundamental aspects of a 3D scanning or AR applications; accordingly Scandy Core has a powerful SLAM implementation that runs in real-time on a background thread. Scandy Core allows developers to easily receive location updates by simply initializing Scandy Core and turning on tracking.

Checkout these C++ classes:

* scandy::utilities::Pose
* scandy::utilities::PointCloudMetaData

### 3D Scanning

Scandy Core provides a stable, fast, and precise 3D scanning interface. Flexibility is key in 3D scanning, which is why Scandy Core allows you to scan something as small as an action figure and as large as a couch. 3D scanning allows developers to easily create a 3D avatar, bring real world objects into a video game, or take accurate measurements.

Checkout these examples:

* [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample)
* [ScandyCoreCppExamples](http://github.com/scandy-co/ScandyCoreCppExamples)


### Meshing

The Scandy Core Meshing is capable of generating a super high resolution dense mesh for use in a printing or measuring context, or a low polygon mesh that is suitable for use in games or VR apps. This versatility makes it easy for the developer to start working with a 3D mesh that suits their needs faster. Configuring the `ScanResolution` prior to `startScanning` adjusts how high resolution of the resulting mesh will be.

Use these functions:

* Java
  * co.scandy.scandycore.ScandyCore::generateMesh()
  * co.scandy.scandycore.ScandyCore::saveMesh()
* C++
  * scandy::core::IScandyCore::generateMesh()
  * scandy::core::IScandyCore::saveMesh()

### Visualizing

Scandy Core's visualizer instance can be deployed for visualizing scan data at run-time and as a 3D mesh viewer. The best part the Scandy Core Visualizer is you don't have to configure OpenGL or any 3D viewer library - it just works!

Checkout the visualizer:

* Java: co.scandy.scandycore.ScandyCoreVisualizer
* C++: scandy::core::Visualizer

Or some examples:

* [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample)
  * With Android all you have to do is include the Visualizer in your layout.
* [ScandyCoreCppExamples](http://github.com/scandy-co/ScandyCoreCppExamples)
  * With C++ all you have to do `auto visualizer = core->createVisualizer(width, height);`

### Editing *(coming soon)*

When working with 3D scan files you frequently end up with a file that is the wrong scale, doesn’t have enough contrast, or has extra artifacts in it; to make this easier, Scandy Core provides developers with an easy way to make adjustments to 3D files. Our goal with the 3D Editing piece of Scandy Core is to provide the most common and necessary features from CAD software so that developers can more easily make Scandy Core work for their application.


## <a name="getting-started"></a>Getting Started

### Language bindings

Scandy Core SDK currently supports bindings for:

* C++
* Java
* JavaScript

Upcoming bindings:

* Unity
* Python
* C#

### Operating systems

Scandy Core supports the following operating systems:

* OS X (tested on 10.11, 10.12)
* Android (minimum Android version 5.0)
* Linux (tested on Ubuntu 14.04, 16.04)

**All operating systems must have OpenCL >= v1.1**

Upcoming systems:

* Windows
* Linux ARM


### Setup

The nature of your setup is contingent upon your build target. Scandy Core has been architected to integrate with existing projects, and can be incorporated as a CMake dependency. Please review the [included coding samples](#examples) to determine the best course of action for installation and configuration with your project.

#### CMake

For using Scandy Core with CMake we highly suggest looking at the README for the [ScandyCoreQtExample](https://github.com/Scandy-co/ScandyCoreQtExample/blob/master/README.md)

#### Android

For using Scandy Core with Android we highly suggest looking at the README for the [ScandyCoreAndroidExample](https://github.com/Scandy-co/ScandyCoreAndroidExample)


<!-- We also need more explanation on the “flow", i.e. create a Scandy Core instance -->

A typical instantiation of Scandy Core may resemble the following:

* Initialize the scanner, subscribing to either a pre-recorded file or pico flexx;
* Start a preview, so as to visualize what the scanner "sees";
* Adjust scan resolution to fit the use-case; use high resolution for detailed scans, low resolution for fast scans;
* Adjust scan size to fit the size of the scan subject;
* Start the scan

### Important classes & API

For an index of the functions available at your command, please reference Scandy Core's top-level classes:

* `scandy::core::IScandyCore` will be your main tour guide in Cpp
* `co.scandy.scandycore.ScandyCore` will your main tour guide in Java

## <a name="examples"></a>Examples

Scandy Core comes with the following examples to help you get started:

* [ScandyCoreCppExamples](http://github.com/scandy-co/ScandyCoreCppExamples)
* [ScandyCoreQtExample](http://github.com/scandy-co/ScandyCoreQtExample)
* [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample)
* [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample)


<!--

# Notes:

- Should we not state up front assumptions re: intended readership
- High-resolution, full-color, on-device, 3D-scanning and meshing

## Abstract

> The goal of the Scandy Core SDK is to simplify the development process so you can blah, blah blah. Although we currently only provide and support bindings for C++, Java, and Javascript, something about how we promise the world.
> Scandy Core SDK performs heavy lifting; it takes care you of your computer vision problems, so you can focus on creating a stellar app. We handle the meshing; you do wonderful things with it.

## Foreword

- 3D is a growing ecosystem, one to be reckoned with, yet one presenting a wealth of problems inherently brutal. Leverage Scandy Core SDK to do the heavy lifting, so you can proceed with actually developing your app.
- Entry into 3D app development can be a daunting prospect. And is not without a litany of brutal problems, each of them Goliath. Scandy Core SDK presents you with a slingshot.
- Scanning, by nature, is a precarious process. We at Scandy are rethinking the way we capture scans; we are rethinking scanning as an accessible and interactive activity.
- Scandy Core SDK works to accommodate the bulk of developers who are not specialists of 3D --- and yet who would like to incorporate 3D into their project, namely by furnishing a suite of powerful tooling for interfacing with 3D data...
- We, the makers of Scandy, believe you should not have to be an expert in computer vision to make use of it in your app.

# Example Apps

- We could do a sample maze one, just tell the user to turn whenever the point cloud data says an obstacle is ahead

-->
