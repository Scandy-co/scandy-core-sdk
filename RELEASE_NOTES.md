# Release Notes

## v0.4.4
### Release Date:
2019-04-09

### Breaking Changes:

* `saveMesh(scandy::core::MeshExportOptions meshExportOptions);` renamed to `exportMesh(scandy::core::MeshExportOptions meshExportOptions);` in `IScandyCore.h`

### New Features:

* default `scandy::core::MeshType` is now `AUTO` for `scandy::core::MeshExportOptions`
* `scandy::core::MeshExportOptions` now supports `m_transform` to apply translation, rotation, and scaling
* added dedicated `setEnableMeshRotation(bool enable_rotate)` to `MeshViewport`

### Bug Fixes:

* Export different file types not always using the latest version of the file
* Fixed `saveScreenShot()` not working consistently on iOS

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.4.3
### Release Date:
2019-04-09

### Breaking Changes:

* [ScandyCoreManager stopScanning], [ScandyCoreManager generateMesh], and [ScandyCoreManager saveMesh] are now async, should you listen for onScannerStop, onGenerateMesh, and onSaveMesh respectively

### New Features:

* stopScanning, generateMesh, saveMesh now run in a background thread and use the onScannerStop, onGenerateMesh, and onSaveMesh callbacks properly.
* extractLargestSurface added to IScandyCore so you can more easily clean up files after a scan.
* adds `getMeshViewport` to IScandyCore to all direct control of the MeshViewport from a client.
* adds `getMeshMemorySize` to IScandyCore to get the number of MBs of the current mesh in the MeshViewport.
* adds FBX to scandy::core::MeshType. The export of this is still experimental and not working exactly as intended.

### Bug Fixes:

* fixed some times losing scale after applying edits to a mesh

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.4.2
### Release Date:
2019-02-22

### Breaking Changes:

* None

### New Features:

* FrameSkip to ISceneKitVisualizer to allow skipping through frames quickly
* Use physics config to ISceneKitVisualizer
* ISceneKitVisualizer detach to remove from pipeline.
* Made saveScreenShot(std::string file_path) work on iOS and exposed to IScandyCore
* Added Draco as scandy::core::MeshType

### Bug Fixes:

* ScandyCore distribution, zip now includes docs, libs, includes, and examples as well as ScandyCore.framework

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.4.1
### Release Date:
2019-02-05

### Breaking Changes:

* None

### New Features:

* Adds more helper functions to utility `Compression.h`
* Adds CompressionType option to MeshExportOptions for volumetric video


### Bug Fixes:

* Fixes ScandyCore.framework clients having to define preprocessor macros.
* Fixes networking bugs for Scandy Pro

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.4.0
### Release Date:
2019-01-31

### Breaking Changes:

* Renamed `ISLAMConfiguration` to `IScandyCoreConfiguration`
* Removed `getStatusString.h` and moved function into `Status.h`
* Removed `getScanStateString.h` and moved function into `ScanState.h`

### New Features:

* Volumetric Video now supports preview to show preview and to stream or record
* Volumetric Video `SCNNode`s have a physics body to be interact-able
* Volumetric Video `SCNNode`s are exposed and controllable


### Bug Fixes:

* Fixed crash that was coming from bad teardown of NetworkManagerWorker
* Fixed OBJ files getting written with out per vertex color
* Red tint during volumetric video recording
* Cross compiling on Linux is good again

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.3.0
### Release Date:
2019-01-11

### New Features:

* Volumetric Video v1.0.0
  * streaming, recording, and playback with synced audio working
  * Networking auto-discovery and streaming
* JSON file processing

### Bug Fixes:

* None

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.2.1
### Release Date:
2018-12-27

### New Features:

* GLB export

### Bug Fixes:

* Triangle filter before saving mesh, should help with a variety of load / display issues on different platforms

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.2.0
### Release Date:
2018-12-17

### New Features:

* Networking
* USDZ export
* Unbounded scanning, aka scan mode v2

### Bug Fixes:

* Tracking did update and preview did update working again

### Known Bugs:

* Android is dead
* OpenCL is dead

## v0.1.3
### Release Date:
2017-04-24

### New Features:

* Updated [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample)

### Bug Fixes:

* Scandy Core's internal license expired. Updated and should be good going forward.
* Fixed `CMakeLists.txt` to properly include `include/scandy_license.h` template again.
* `vtkRenderWindow` not closing properly when `Visualizer` joined.

### Known Bugs:

* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens

## v0.1.2
### Release Date:
2017-04-17

### New Features:

* Changed scandy::core::IScandyCore::factoryCreate() to work better with Qt
* `package_v1.py` now also uploads the packaged binary and release key to S3

### Bug Fixes:

* [ScandyCoreQtExample](https://github.com/Scandy-co/ScandyCoreQtExample/tree/v0.1.2) is now linked to v0.1.2 and working on macOS and Linux

### Known Bugs:

* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens
* [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample) is empty. Going to get with @gtfargo about fixing this soon.


## v0.1.1

### Release Date:
2017-03-31

### New Features:

* Updated LICENSE.txt

### Known bugs:

* Linux experimental build is failing due to a linker order issue
* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens
* [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample) is empty. Going to get with @gtfargo about fixing this soon.
* QtVisualizer has more work to be done, currently buggy with the interaction control

## v0.1.0

### Release Date:
2017-03-31

### New Features:

* license manager
  * cpp: IScandyCore::setLicense(std::string license_json_string)
  * Java: ScandyCore.setLicense(String license_json_string)
* better example code that is in public repos
  * [ScandyCoreCppExamples](http://github.com/scandy-co/ScandyCoreCppExamples)
  * [ScandyCoreQtExample](http://github.com/scandy-co/ScandyCoreQtExample)
  * [ScandyCoreAndroidExample](http://github.com/scandy-co/ScandyCoreAndroidExample)
  * [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample)


### Known bugs:

* Linux experimental build is failing due to a linker order issue
* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens
* [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample) is empty. Going to get with @gtfargo about fixing this soon.
* QtVisualizer has more work to be done, currently buggy with the interaction control

## v0.0.4

### Release Date:
2017-03-24

Features:
* First version of full public API ready in `IScandyCore.h`
* Abstracted interface for ScandyCore via `IScandyCore`
* Improved build system the decouples various objects to improve build times
* New scripts for running build and tests `internal_only/scripts/run_tests.py`
* Only generating `*.cl` -> `*_cl.h` when we need to
* More distributable samples
  * [ScandyCoreQtExample](https://github.com/Scandy-co/ScandyCoreQtExample)
  * `distributable/samples/basic_usage_file_read.cpp`

Known bugs:
* Linux experimental build is failing due to a linker order issue
* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens
