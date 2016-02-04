set(X_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "app cmake script directory")

include(CMakeParseArguments)
include("${X_CMAKE_DIR}/x_macros.cmake")
include("${X_CMAKE_DIR}/x_find.cmake")
include("${X_CMAKE_DIR}/x_link.cmake")
include("${X_CMAKE_DIR}/x_utf8.cmake")

####################################################################################################
#                                     EXTERN CALL MACRO PART                                       #
####################################################################################################
# x_add_subdirectory(dir [NONE WIN LINUX])
#					support platform judge: WIN, LINUX.
macro(x_add_subdirectory)
	set(_argn ${ARGN})

	cmake_parse_arguments(WAS "NONE;WIN;LINUX" "" "" ${_argn})
	if(NOT WAS_WIN AND NOT WAS_LINUX AND NOT WAS_NONE)
		set(WAS_WIN ON)
		set(WAS_LINUX ON)
	endif()

	set(_valid NO)
	if(OS_WIN)
		set(_valid ${WAS_WIN})
	elseif(OS_LINUX)
		set(_valid ${WAS_LINUX})
	endif()
	
	if(_valid)
		set(_dir ${WAS_UNPARSED_ARGUMENTS})
		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_dir}")
			add_subdirectory(${_dir})
		else()
			message(FATAL_ERROR "${_dir} does not exists.")
		endif()
	endif()
endmacro()

# x_package(<name>
				#[NONE|STATIC|SHARED|MODULE|EXECUTABLE|CONSOLE]    #package type
				#[BUILD_DEST_PATH <destpath>]    #package output path
				#)
macro(x_package _name)
endmacro(x_package)

# x_add_definitions(def1 def2 ...)
#					support platform judge: WIN, LINUX.
macro(x_add_definitions)
	_args_system_filter(_cur_system_argn ${ARGN})
	list(APPEND X_CURRENT_PACKAGE_DEFINITIONS ${_cur_system_argn})

	if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "STATIC!")
		list(REMOVE_ITEM X_CURRENT_PACKAGE_DEFINITIONS "_USRDLL")
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "SHARED!"
		OR "${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "MODULE!")
		list(REMOVE_ITEM X_CURRENT_PACKAGE_DEFINITIONS "_LIB")
	endif()
endmacro()

# x_include_directories(dir1 dir2 ...)
#						support platform judge: WIN, LINUX.
macro(x_include_directories)
	_args_system_filter(_cur_system_argn ${ARGN})
	include_directories(${_cur_system_argn})
endmacro()

# x_include_packages(package1 package2 ...)
macro(x_include_packages)
endmacro()

# x_add_sources([PCH stdafx.h stdafx.cpp] a.h a.cpp b.h b.cpp ...)
# 					x_add_sources(a.cpp WIN(b.cpp) LINUX(c.cpp))
#					include b.cpp and exclude c.cpp when on Windows, include c.cpp and exclude b.cpp when on Linux.
#                   support platform judge: WIN, LINUX.
macro(x_add_sources)
	_args_system_filter(_cur_system_argn ${ARGN})
	foreach(_f ${_cur_system_argn})
		string(TOLOWER "${_f}" _f)
		if(_f MATCHES "(\\.c|\\.cc|\\.cpp|\\.cxx)")
		elseif(_f MATCHES "(\\.h|\\.hh|\\.hpp|\\.hxx)")
		elseif(_f MATCHES "(\\.m|\\.mm)")
		elseif(_f MATCHES "(\\.inl)")
		elseif(_f MATCHES "(\\.l|\\.y)")
		elseif(_f MATCHES "(\\.rc|\\.idl|\\.def)")
		else()
			message(FATAL_ERROR "Unrecognized source file ${_f}")
		endif()
	endforeach()
	list(APPEND X_CURRENT_PACKAGE_SRCS ${_cur_system_argn} "X_SOURCE_SEPARATOR")
endmacro()

# x_link_packages(package1 package2 ...)
macro(x_link_packages)
endmacro()

# x_declare_fileinfo([FILE_DESCRIPTION "description"] #empty if not write
	# [FILE_VERSION "file_version"] # use external info if not write 
	# [PRODUCT_VERSION "product_version"] # use external info if not write 
	# [COMPANY_NAME "company name"] # Default value: "Application Software Co.,Ltd"
	# [PRODUCT_NAME "product name"] # Default value: "Application"
	# [COPY_RIGHT "copy right"] # Default value: "Copyright(c)1988-2012 Application Corporation.  All rights reserved." 
	# )
macro(x_declare_fileinfo)
	set(oneValueArgs FILE_VERSION PRODUCT_VERSION
		FILE_DESCRIPTION COMPANY_NAME PRODUCT_NAME COPY_RIGHT)
	cmake_parse_arguments(info "" "${oneValueArgs}" "" ${ARGN})
	
	if(info_FILE_VERSION)
		set(X_CURRENT_FILE_VERSION ${info_FILE_VERSION})
	endif()
	if(info_PRODUCT_VERSION)
		set(X_CURRENT_PRODUCT_VERSION ${info_PRODUCT_VERSION})
	endif()
	if(info_FILE_DESCRIPTION)
		set(X_CURRENT_FILE_DESCRIPTION "${info_FILE_DESCRIPTION}")
	endif()
	if(info_COMPANY_NAME)
		set(X_CURRENT_COMPANY_NAME "${info_COMPANY_NAME}")
	else()
		set(X_CURRENT_COMPANY_NAME "Application Software Co.,Ltd")
	endif()
	if(info_PRODUCT_NAME)
		set(X_CURRENT_PRODUCT_NAME "${info_PRODUCT_NAME}")
	else()
		set(X_CURRENT_PRODUCT_NAME "Application")
	endif()
	if(info_COPY_RIGHT)
		set(X_CURRENT_COPY_RIGHT "${info_COPY_RIGHT}")
	else()
		set(X_CURRENT_COPY_RIGHT "${X_COPY_RIGHT_UTF8}")
	endif()
endmacro()

# x_end_package()
macro(x_end_package)
endmacro()

# x_final_deal()
macro(x_final_deal)
	_generate_make_bat()

	string(REPLACE ";" "\n" _project_info "${X_PACKAGE_INFO_LIST}")
	configure_file("${X_CONFIG_TEMPLATE_DIR}/project_info.txt.in" "${X_CONFIGURE_FILE_DIRECTORY}/project_info.txt")
	unset(X_PACKAGE_INFO_LIST CACHE)
endmacro()

macro(_generate_make_bat)
	# It is too trivial to typing "msbuild /m app.sln /t:xxx".Generate "make.bat" to solve it.
	if(CMAKE_GENERATOR MATCHES "^Visual Studio")
		configure_file("${CMAKE_SOURCE_DIR}/cmake/config_template/make.bat.in" "${CMAKE_BINARY_DIR}/make.bat" @ONLY)
	endif()
endmacro()

####################################################################################################
#                                     COMPILER PART                                                #
####################################################################################################
macro(_check_compiler)
	if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_BUILD_TYPE STREQUAL "Release")
		message(FATAL_ERROR "${CMAKE_PROJECT_NAME} currently only support Debug and Release.")
	endif()
	_set_compiler_flags()

	# remove we don't need options
	unset(CMAKE_C_FLAGS_MINSIZEREL CACHE)
	unset(CMAKE_C_FLAGS_RELWITHDEBINFO CACHE)
	unset(CMAKE_CXX_FLAGS_MINSIZEREL CACHE)
	unset(CMAKE_CXX_FLAGS_RELWITHDEBINFO CACHE)
	unset(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL CACHE)
	unset(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO CACHE)
	unset(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL CACHE)
	unset(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO CACHE)
	unset(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL CACHE)
	unset(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO CACHE)
endmacro()

macro(_set_compiler_flags)
	if(NOT X_INITED_COMPILER)
		_uncache_vars(
			CMAKE_EXE_LINKER_FLAGS CMAKE_EXE_LINKER_FLAGS_DEBUG CMAKE_EXE_LINKER_FLAGS_RELEASE
			CMAKE_MODULE_LINKER_FLAGS CMAKE_MODULE_LINKER_FLAGS_DEBUG CMAKE_MODULE_LINKER_FLAGS_RELEASE
			CMAKE_SHARED_LINKER_FLAGS CMAKE_SHARED_LINKER_FLAGS_DEBUG CMAKE_SHARED_LINKER_FLAGS_RELEASE
			)
		set(X_INITED_COMPILER YES CACHE BOOL "Flag seted if app has init compiler flags.")
		mark_as_advanced(X_INITED_COMPILER)
	endif()

	if(NOT CMAKE_C_COMPILER_ID STREQUAL CMAKE_CXX_COMPILER_ID)
		message(FATAL_ERROR "c && c++ compiler is not same.")
	endif()
	string(TOLOWER "${CMAKE_C_COMPILER_ID}" _compiler_id)
	if(NOT EXISTS "${X_CMAKE_DIR}/${_compiler_id}_flags.cmake")
		message(FATAL_ERROR "${CMAKE_PROJECT_NAME} currently do not support ${CMAKE_CXX_COMPILER_ID}.")
	else()
		include("${X_CMAKE_DIR}/${_compiler_id}_flags.cmake")
	endif()

	_recache_vars()
endmacro()

####################################################################################################
#                                     PRESETTING PART                                              #
####################################################################################################
set(X_CONFIG_TEMPLATE_DIR "${X_CMAKE_DIR}/config_template")
# In cmake:
#	*.a *.lib is archive
#	*.so *.dll is library
#	*.exe elf is runtime
set(X_OUTPUT_ROOT_DIRECOTRY "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${X_OUTPUT_ROOT_DIRECOTRY}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${X_OUTPUT_ROOT_DIRECOTRY}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${X_OUTPUT_ROOT_DIRECOTRY}/bin")

set(FILE_VERSION "0.0.0.0" CACHE STRING "file version info")
set(PRODUCT_VERSION "0.0.0.0" CACHE STRING "product version info")
set(X_STATIC_CODE_ANALYZE FALSE CACHE BOOL "app static code analyze.")
set(X_DETECT_MEMORY_LEAK FALSE CACHE BOOL "app detect memory leak.")
set(X_PRINT_TIME_SPENT FALSE CACHE BOOL "app print time log.(linux only)")
set(X_USING_ASAN FALSE CACHE BOOL "using gcc/clang AddressSanitizer.(linux only)")
set(X_USING_CCACHE FALSE CACHE BOOL "using ccache speed up compile.(linux only)")

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)

if("!${CMAKE_SYSTEM_NAME}" STREQUAL "!Windows")
	set(OS_WIN TRUE)
	set(DSK_WIN TRUE)
elseif("!${CMAKE_SYSTEM_NAME}" STREQUAL "!Linux")
	set(OS_LINUX TRUE)
	set(DSK_X11 TRUE)
	set(DSK_XCB TRUE)
else()
	message(FATAL_ERROR "Unknown platform: ${CMAKE_SYSTEM_NAME}!")
endif()

_check_compiler()

if(CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_CONFIGURATION_TYPES STREQUAL CMAKE_BUILD_TYPE)
	# do not support multi-configurations
	set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE}
		CACHE STRING "Configurations, do not change it, change CMAKE_BUILD_TYPE please." FORCE)
endif()

# do not support multi-configurations
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
