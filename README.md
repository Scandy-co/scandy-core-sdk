# Scandy Core SDK

**Welcome to the wonderful world of 3D!**

## Table of Contents

* [Forward](#forward)
* [Getting Started](#getting-started)
* [Examples](#examples)
* [Definitions](#definitions)
* [Features Overview](#features-overview)

## <a name="forward"></a>Forward

Scandy Core is here to make your life easier as a developer who wants to work with 3D data. Scandy Core provides a set of easy-to-use functions for viewing, loading, downloading, editing, and creating 3D files.

Scandy Core is an SDK that allows developers to easily create 3D models, track position in 3D space, and edit 3D models. Scandy Core is currently optimized to run on Android, Mac OS X, and Linux. Scandy Core is written in cross-platform C++ and has many proprietary optimizations that allow it to run on powerful computing platforms like render servers or workstations, and then to gracefully scale down to operate on processor and memory-constrained devices, like smartphones or tablets. Files created with Scandy Core are capable of running on all platforms regardless of where they were created. Scandy Core also exports industry standard 3D files like OBJ, PLY, and STL.

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

### Typical Usage flow

#### 3D scan to file:

* Initialize the scanner
  * Either using a pre-recorded `.rrf` file or live data from a pico flexx.
* Start a preview, so as to visualize what the depth sensor "sees"
* Adjust scan resolution to fit the use-case
  * Use high resolution for detailed scans
  * Use low resolution for fast scans
  * Use medium resolution for somewhere inbetween
* Adjust the scan size to fit the size of the scan subject
* Start the scan
* Scan for some period of time. Determined by a button press, timer, API call of some sort, etc..
* Stop the scan
* Generate a mesh of the scan
* Save the mesh to a file

### Setup

Scandy Core can be setup in a variety of ways to fit your build target. Scandy Core has been designed to integrate with existing projects, and can be incorporated as a CMake dependency. Please review the [included coding samples](#examples) to determine the best course of action for installation and configuration with your project.

#### CMake

For using Scandy Core with CMake we highly suggest looking at the README for the [ScandyCoreQtExample](https://github.com/Scandy-co/ScandyCoreQtExample/blob/master/README.md)

#### Android

For using Scandy Core with Android we highly suggest looking at the README for the [ScandyCoreAndroidExample](https://github.com/Scandy-co/ScandyCoreAndroidExample)

### Important classes & API

For an index of the functions available at your command, please reference Scandy Core's top-level classes:

* `scandy::core::IScandyCore` will be your main tour guide in C++
* `co.scandy.scandycore.ScandyCore` will your main tour guide in Java

### Setting your License
To use the SLAM features in Scandy Core you will need to provide your license to Scandy Core. This is handled differently for the C++ and Android (Java) implementations. You should have a received a `foo@bar.com-scandycore-license.txt` file when you purchased Scandy Core, we will call this the *license key file*.

#### C++
Update `const char* scandy_core_license` in  `ScandyCore/include/scandy_license.h` to have the contents of your license.

It should look like this when you receive it:

```cpp
const std::string scandy_core_license {R"CLC(
   {
     "vendor": "Scandy LLC",
     "license": {
       "product": "Scandy Core",
       "version": "1.0",
       "expiry": "never",
       "hostid": "any",
       "customer": "Your name",
       "signature": "super!duper!secret!signature!"
     }
   }
)CLC"};
```

Paste the contents of your *license key file* into the `scandy_license.h` replacing the placeholder. It should look something like this now:

```cpp
const std::string scandy_core_license {R"CLC(
   {"vendor":"Scandy LLC","license":{"product":"Scandy Core","version":"1.0","expiry":"never","hostid":"any","customer”:”foo@bar.com”,”userdata":"{}","signature":"49EDA410195D11E79D989C63E968CD3E49EDA410195D11E79D989C63E968CD3E49EDA410195D11E79D989C63E968CD3E49EDA410195D11E79D989C63E968CD3E"}}
)CLC"};
```

Then when you want to use any of the SLAM features in Scandy Core you just set your license by calling `setLicense(std::string license)`

e.g.:

```cpp
#include <scandy/core/IScandyCore.h>
#include <scandy_license.h>

using namespace scandy::core;
using namespace std;

int main(int argc, char *argv[]) {
  scandy::core::Status status;

  // Create the ScandyCore instance with a Visualizer window of 400x400
  auto core = IScandyCore::factoryCreate(400,400);
  if(!core) {
    std::cerr << "ERROR creating ScandyCore" << std::endl;
    return (int) scandy::core::Status::EXCEPTION_IN_HANDLER;;
  }

  // We need to set the ScandyCore license to our internal license
  status = core->setLicense(scandy_core_license);
  if(status != Status::SUCCESS) {
    std::cerr << "ERROR could not set license" << std::endl;
    return (int) status;
  }
}
```

#### Android
The function call is exactly the same for Android, `setLicense(String license)`, but there is a different paradigm for handling the file. The ScandyCoreAndroidExample shows how to use a license file stored in the asset cache to read the license at runtime.

By following the [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample), you can update the [`scandycore_license.json`](https://github.com/Scandy-co/ScandyCoreAndroidExample/blob/master/app/src/main/assets/scandycore_license.json) and then [read that file in](https://github.com/Scandy-co/ScandyCoreAndroidExample/blob/0ad8b2335f8e7f492254abe882fa723d60812fd4/app/src/main/java/co/scandy/example/scandycoreandroidexample/MainActivity.java#L261) and call [`ScandyCore.setLicense(license)`](https://github.com/Scandy-co/ScandyCoreAndroidExample/blob/0ad8b2335f8e7f492254abe882fa723d60812fd4/app/src/main/java/co/scandy/example/scandycoreandroidexample/MainActivity.java#L288) with the contents of the file.


## <a name="examples"></a>Examples

Scandy Core comes with the following examples to help you get started:

* [ScandyCoreCppExamples](http://github.com/scandy-co/ScandyCoreCppExamples)
* [ScandyCoreQtExample](http://github.com/scandy-co/ScandyCoreQtExample)
* [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample)
* [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample)

## <a name="definitions"></a>Definitions

_X is **Supported** means the feature is currently implemented_

| Term  | Supported |  Definition |
|---|:---:|---|
| _SLAM_  | X  | Denotes simultaneous localization and mapping. See Wikipedia entry re: [SLAM](https://en.wikipedia.org/wiki/Simultaneous_localization_and_mapping).|
| _pico flexx_ | X | The [pico flexx](http://pmdtec.com/picoflexx) is a small USB 3D sensor made by [pmd](http://pmdtec.com) that allows capturing of live 3D data. |
| _RRF_ | X  |  Royale raw file. A file extension that denotes/wraps point cloud data as provisioned by a live sensor stream. If you have been using Royale for awhile you might have a few of these laying around that you want to re-examine. |
| _TSDF_ | X | Truncated signed distance function; a voxel representative of a given scan created in memory by Scandy Core; more specifically, `TSDF` stores values used for attempting accurate representation of a volumetric surface. Originally defined in paper ["A Volumetric Method for Building Complex Models from Range Images"](http://graphics.stanford.edu/papers/volrange/volrange.pdf). Also, see Wikipedia entries for [signed distance function](https://en.wikipedia.org/wiki/Signed_distance_function) and on [volume rendering](https://en.wikipedia.org/wiki/Volume_rendering). |
| _Mesh_ | X | A mesh represents a 3D scene or object in a standardized format such as [.OBJ](https://en.wikipedia.org/wiki/Wavefront_.obj_file) or [.PLY](https://en.wikipedia.org/wiki/PLY_(file_format)). Scandy Core can generate a mesh for any scan taken, and then also save that mesh into a PLY or OBJ format. |
| _SCRF_ |  | Scandy Core raw file; a proprietary file extension denoting those contents of a scan file saved to disk. Packages a live sensor stream (or `RRF`), along with the parameters used to capture a given volume (i.e., scanning configuration). In future versions, `SCRF`s may also be extended to include depth maps and color frames. More generally, SCRF refers to those contents of a scan file distinguishable from any derivative meshes. |
| _IMU_  |   | Inertial measurement unit. Data encompassing a host device's specific force and angular orientation is fed into Scandy Core for enhancements in tracking. See [Wikipedia entry](https://en.wikipedia.org/wiki/Inertial_measurement_unit).  |


## <a name="features-overview"></a>Features Overview

### 3D Tracking (SLAM)

Keeping track of where you are in 3D space is one of the most fundamental aspects of a 3D scanning or AR application; accordingly Scandy Core has a powerful SLAM implementation that runs in real-time on a background thread. Scandy Core allows developers to easily receive location updates by simply initializing Scandy Core and turning on tracking.

Checkout these C++ classes:

* scandy::utilities::Pose
* scandy::utilities::PointCloudMetaData

### 3D Scanning

Scandy Core provides a stable, fast, and precise 3D scanning interface. Flexibility is key in 3D scanning, which is why Scandy Core allows you to scan something as small as an action figure and as large as a couch. 3D scanning allows developers to easily create a 3D avatar, bring real world objects into a video game, or take accurate measurements.

Checkout these examples:

* [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample)
* [ScandyCoreCppExamples](http://github.com/scandy-co/ScandyCoreCppExamples)


### Meshing

The Scandy Core Meshing is capable of generating a high-resolution dense mesh which is perfect for 3D printing or obtaining accurate measurements, or a low-polygon mesh that is suitable for use in games or VR apps. This versatility makes it easy for the developer to start working with a 3D mesh that suits their needs faster. Configuring the `ScanResolution` prior to `startScanning` adjusts how high the resolution of the resulting mesh will be.

Use these functions:

* Java
  * co.scandy.scandycore.ScandyCore::generateMesh()
  * co.scandy.scandycore.ScandyCore::saveMesh()
* C++
  * scandy::core::IScandyCore::generateMesh()
  * scandy::core::IScandyCore::saveMesh()

### Visualizing

Scandy Core's visualizer instance can be deployed for visualizing scan data at run-time and as a 3D mesh viewer. The best part of the Scandy Core Visualizer is you don't have to configure OpenGL or a 3D viewer library—it just works!

Checkout the visualizer:

* Java: co.scandy.scandycore.ScandyCoreVisualizer
* C++: scandy::core::Visualizer

Or some examples:

* [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample)
  * With Android all you have to do is include the Visualizer in your layout.
* [ScandyCoreCppExamples](http://github.com/scandy-co/ScandyCoreCppExamples)
  * With C++ all you have to do is `auto visualizer = core->createVisualizer(width, height);`

### Editing *(coming soon)*

When working with 3D scan files you frequently end up with a file that is the wrong scale, doesn’t have enough contrast, or has extra artifacts in it; to make this easier, Scandy Core provides developers with an easy way to make adjustments to 3D files. Our goal with the 3D editing piece of Scandy Core is to provide the most common and necessary features from CAD software so that developers can more easily make Scandy Core work for their application.
