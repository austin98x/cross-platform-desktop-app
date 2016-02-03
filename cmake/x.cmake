set(X_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "app cmake script directory")

include("${X_CMAKE_DIR}/x_internal.cmake")
include("${X_CMAKE_DIR}/x_find.cmake")
include("${X_CMAKE_DIR}/x_link.cmake")
include("${X_CMAKE_DIR}/x_utf8.cmake")

# x_include_directories(dir1 dir2 ...)
macro(x_include_directories)
	_args_system_filter(_cur_system_argn ${ARGN})
	include_directories(${_cur_system_argn})
endmacro()

# x_package(<name>
				#[NONE|STATIC|SHARED|MODULE|EXECUTABLE|CONSOLE|LNG_LEGACY]    #package type
				#[BUILD_DEST_PATH <destpath>]    #package output path
				#)
macro(x_package _name)
	cmake_parse_arguments(_X 
		"" 
		"BUILD_DEST_PATH" 
		"" 
		${ARGN})

	if(DEFINED _X_BUILD_DEST_PATH)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${X_OUTPUT_ROOT_DIRECOTRY}/${_X_BUILD_DEST_PATH}")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${X_OUTPUT_ROOT_DIRECOTRY}/${_X_BUILD_DEST_PATH}")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	endif()

	set(_argn ${_X_UNPARSED_ARGUMENTS})
	set(pkg_types "NONE|STATIC|SHARED|MODULE|EXECUTABLE|CONSOLE|LNG_LEGACY")
	_token_radio_option(_argn ${pkg_types} "NONE" _type)

	if(_argn)
		message(FATAL_ERROR "\nthe package type your set could not find in TypeList.\nThe correct TypeList is ${pkg_types}\n")
	endif()

	set(X_CURRENT_PACKAGE_NAME "${_name}")
	set(X_CURRENT_PACKAGE_BUNDLE_NAME "${_name}")
	set(X_CURRENT_PACKAGE_TYPE "${_type}")
	set(X_CURRENT_PACKAGE_SRCS)
	set(X_CURRENT_PACKAGE_INCLUDE_PKG_DIRS)
	set(X_CURRENT_PACKAGE_LINK_PKGS)
	set(X_CURRENT_PACKAGE_LINK_LIBRARYS)
	set(X_CURRENT_PACKAGE_DEPEND_PKGS)
	set(X_CURRENT_PACKAGE_HAS_PUBLIC_HEADER)
	set(X_CURRENT_PACKAGE_GENERATEE_FILES)
	set(X_CURRENT_PACKAGE_DEFINITIONS)
	set(X_CURRENT_PACKAGE_RESES)
	set(X_CURRENT_PACKAGE_PREFIX_HEADER)
	set(X_CURRENT_RESES_GROUP_DESTPATH)
	set(X_CURRENT_PACKAGE_FULLPATH)
	set(X_CURRENT_PACKAGE_FILENAME)
	set(X_CURRENT_PACKAGE_SUFFIX)
	set(X_CURRENT_FILE_DESCRIPTION)
	set(X_CURRENT_FILE_VERSION)
	set(X_CURRENT_PRODUCT_VERSION)
	set(X_EXECUTABLE_ENTRYPOINT "main")
	set(X_CURRENT_PACKAGE_RUNTIME_LIBRARY_TYPE "MD")
	if("!${CMAKE_BUILD_TYPE}" STREQUAL "!Debug")
		set(X_CURRENT_PACKAGE_RUNTIME_LIBRARY_TYPE "MDd")
	endif()
	set(X_CURRENT_PACKAGE_OPTIMIZATION "${CXX_OPTIMIZATION_MINSIZE_FLAGS}")
	if("!${CMAKE_BUILD_TYPE}" STREQUAL "!Debug")
		set(X_CURRENT_PACKAGE_OPTIMIZATION "${CXX_OPTIMIZATION_NONE_FLAGS}")
	endif()

	x_include_directories(${CMAKE_CURRENT_BINARY_DIR})
	x_include_directories("${CMAKE_BINARY_DIR}/public_header")
	x_include_directories(".")

	_x_get_cur_pkg_main_output()
	_verity_pkg_name()

	if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "STATIC!")
		list(APPEND X_CURRENT_PACKAGE_DEFINITIONS "_LIB")
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "SHARED!"
		OR "${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "MODULE!")
		list(APPEND X_CURRENT_PACKAGE_DEFINITIONS "_USRDLL")
	endif()
endmacro(x_package)