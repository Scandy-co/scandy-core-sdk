# Scandy Core Change Log
<!--- For distribution -->

## v0.1.3
### Release Date:
2017-04-24

### New Features:

* Updated [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample)

### Bug Fixes:

* Scandy Core's internal license expired. Updated and should be good going forward.
* Includes `include/scandy_license.h` template again.

### Known Bugs:

* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens

## v0.1.2
### Release Date:
2017-04-17

### New Features:

* Changed scandy::core::IScandyCore::factoryCreate() to work better with Qt

### Bug Fixes:

* [ScandyCoreQtExample](https://github.com/Scandy-co/ScandyCoreQtExample/tree/v0.1.2) is now linked to v0.1.2 and working on macOS

### Known Bugs:

* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens
* [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample) is empty. Going to get with @gtfargo about fixing this soon.

## v0.1.1
### Release Date:
2017-03-31

### New Features:

* Updated LICENSE.txt

### Bug Fixes:
### Known Bugs:

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


### Bug Fixes:
### Known Bugs:

* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens
* [ScandyCoreReactNativeExample](http://github.com/scandy-co/ScandyCoreReactNativeExample) is empty. Going to get with @gtfargo about fixing this soon.
* QtVisualizer has more work to be done, currently buggy with the interaction control

## v0.0.4
### Release Date:
2017-03-24

First version of full public API ready in `IScandyCore.h`

### Features:

* Abstracted interface for ScandyCore via `IScandyCore`
* More distributable samples:
  * [ScandyCoreQtExample](https://github.com/Scandy-co/ScandyCoreQtExample)
  * `distributable/samples/basic_usage_file_read.cpp`

### Bug Fixes:

* Color scanning on S6 does not crash after ~1 minute

### Known Bugs:

* pico flexx on Android is not super stable. i.e. cable gets jiggled loose bad state happens

## v0.0.3
### Release Date:
2017-02-13

### Features:

* Better OpenCL exception handling and logging
* Color on Android
* IMU tracking added into experimental build
* New UI for `scandycoreandroidapp` that is a better dev tool
* Android runs all SLAM related operations on a [Service](https://developer.android.com/reference/android/app/Service.html)

### Bug Fixes:
### Known Bugs:

* Galaxy S6 is crashing after ~1 minute of color scanning. (S7 seems fine for long periods)

## v0.0.2
### Release Date:
2017-01-18
### Features:

* ScandyCore cpp, Java, and JavaScript bindings:
    * `initializeScanner(filepath)`
    * `startScanning()`
    * `stopScanning()`
    * `generateMesh()`
    * `saveMesh()`
    * `loadMesh(filepath, filepath="")`
* Java, and JavaScript bindings:
    * `loadMeshFromURL(url)`

### Bug Fixes:
### Known Bugs:


## v0.0.1
### Release Date:
2016-07-09

### Features:

* Added Semantic versioning to CMake

### Bug Fixes:
### Known Bugs:

## v0.0.0
### Release Date:
2016-07-09

### Features:

* Initialized Scandy Core

### Bug Fixes:
### Known Bugs:
