# cross-platform-desktop-app
This is a framework for helping develops to quick developing cross platform desktop application.

## Description
CMAkE is an open-source, cross-platform family of tools designed to build, test and package software.
I have write some useful macros to help you to configure your project. 

## Depends
cmake and Qt are needed.

## How to use
* Write a CMakeLists.txt at your root folder. Such as:
```Bash
cmake_minimum_required(VERSION 2.8.0)
include(cmake/x_precheck.cmake)
project(SolutionName)
include(cmake/x.cmake)
x_add_subdirectory(subdirectory)
x_final_deal()
```

* Write CMakeLists.txt for project. Such as:
```Bash
x_package(app EXECUTABLE) // STATIC or SHARED
	x_add_definitions() // definitions
	x_include_directories() // include directories
	x_add_sources() // source files
	x_link_packages() // link modules
x_end_package()
```

* CMakeLists.txt should be write in each directory (including subdirectories). Such as:
```Bash
x_add_subdirectory(subdirectory)
```

## Build step
* Enter Solution's root folder.
* Create a build folder.
* Enter build folder.
* Run cmake -DQT_PATH=YourQtPath . ../
* Then it will create a Visual Studio project on Windows platform or Makefile on Linux platform.
* Now you can build your project, and build result are all in SolutionName folder.
