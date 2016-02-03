if(EXISTS ${CMAKE_BINARY_DIR}/CMakeLists.txt)
	message(FATAL_ERROR 
		"In order to prevent commit rubbish into source server, "
		"App do not support in-source build. "
		"Remove CMakeCache.txt and CMakeFiles and then use out-of-souce build,Please.\n"
		"See also: http://www.vtk.org/Wiki/CMake_FAQ#Out-of-source_build_trees\n"
		)
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
endif()
if(CMAKE_GENERATOR MATCHES "^Visual Studio")
	set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "Configurations, do not change it, change CMAKE_BUILD_TYPE please.")
endif()
