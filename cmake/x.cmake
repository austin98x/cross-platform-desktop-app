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
	cmake_parse_arguments(_WP 
		"" 
		"BUILD_DEST_PATH" 
		"" 
		${ARGN})
	if(DEFINED _WP_BUILD_DEST_PATH)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${X_OUTPUT_ROOT_DIRECOTRY}/${_WP_BUILD_DEST_PATH}")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${X_OUTPUT_ROOT_DIRECOTRY}/${_WP_BUILD_DEST_PATH}")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	endif()

	set(_argn ${_WP_UNPARSED_ARGUMENTS})
	set(pkg_types "NONE|STATIC|SHARED|MODULE|EXECUTABLE|CONSOLE")
	_token_radio_option(_argn ${pkg_types} "NONE" _type)

	if(_argn)
		message(FATAL_ERROR "\nthe package type your set could not find in TypeList.\nThe correct TypeList is ${pkg_types}\n")
	endif()
	
	set(X_CURRENT_PACKAGE_NAME "${_name}")
	set(X_CURRENT_PACKAGE_TYPE "${_type}")
	set(X_CURRENT_PACKAGE_SRCS)
	set(X_CURRENT_PACKAGE_INCLUDE_PKG_DIRS)
	set(X_CURRENT_PACKAGE_LINK_PKGS)
	set(X_CURRENT_PACKAGE_LINK_LIBRARYS)
	set(X_CURRENT_PACKAGE_DEPEND_PKGS)
	set(X_CURRENT_PACKAGE_DEFINITIONS)
	set(X_CURRENT_PACKAGE_HAS_PUBLIC_HEADER)

	set(X_CURRENT_FILE_VERSION)
	set(X_CURRENT_PRODUCT_VERSION)
	set(X_CURRENT_FILE_DESCRIPTION)

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
	x_include_directories(".")

	if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "STATIC!")
		list(APPEND X_CURRENT_PACKAGE_DEFINITIONS "_LIB")
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "SHARED!"
		OR "${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "MODULE!")
		list(APPEND X_CURRENT_PACKAGE_DEFINITIONS "_USRDLL")
	endif()
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
	#message(STATUS ${X_CURRENT_PACKAGE_DEFINITIONS})
endmacro()

# x_include_directories(dir1 dir2 ...)
#						support platform judge: WIN, LINUX.
macro(x_include_directories)
	_args_system_filter(_cur_system_argn ${ARGN})
	include_directories(${_cur_system_argn})
	#message(STATUS ${_cur_system_argn})
endmacro()

# x_add_sources([PCH stdafx.h stdafx.cpp] [QT_AUTOMOC] a.h a.cpp b.h b.cpp ...)
# 					x_add_sources(a.cpp WIN(b.cpp) LINUX(c.cpp))
#					include b.cpp and exclude c.cpp when on Windows, include c.cpp and exclude b.cpp when on Linux.
#                   support platform judge: WIN, LINUX.
macro(x_add_sources)
	_args_system_filter(_cur_system_argn ${ARGN})
	foreach(_f ${_cur_system_argn})
		if(_f MATCHES "(PCH|QT_AUTOMOC)")
		else()
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
		endif()
	endforeach()
	list(APPEND X_CURRENT_PACKAGE_SRCS ${_cur_system_argn} "X_SOURCE_SEPARATOR")
	#message(STATUS ${X_CURRENT_PACKAGE_SRCS})
endmacro()

# x_link_packages(package1 package2 ...)
#					support platform judge: WIN, LINUX.
macro(x_link_packages)
	_args_system_filter(_cur_system_argn ${ARGN})
	list(APPEND X_CURRENT_PACKAGE_LINK_PKGS ${_cur_system_argn})
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

# x_custom_compile(<_compiler>    #_compiler only support qrc and lrelease
				#<INPUT src_qrc_path>
				#<OUTPUT dst_file_path>
				#)
macro(x_custom_compile _compiler)
	cmake_parse_arguments(_WCC 
		"" 
		"OUTPUT" 
		"INPUT" 
		${ARGN})
	
	set(_output_file ${X_OUTPUT_ROOT_DIRECOTRY}/${_WCC_OUTPUT})
	get_filename_component(_output_path ${_output_file} PATH)
	if(NOT IS_DIRECTORY ${_output_path})
		if(EXISTS ${_output_path})
			message(FATAL_ERROR "\"${_output_path}\" is file, can not make directory.")
		endif()
		file(MAKE_DIRECTORY ${_output_path})
	endif()

	set(_input_files)
	foreach(_file ${_WCC_INPUT})
		list(APPEND _input_files ${CMAKE_CURRENT_SOURCE_DIR}/${_file})
	endforeach()
	
	if("!${_compiler}" STREQUAL "!qrc")
		x_find_qt_rcc()

		set(_qresource_list)
		foreach(_file ${_input_files})
			_x_scan_qrc(${_WCC_INPUT} X_CURRENT_PACKAGE_SRCS _res_list)
			list(APPEND _qresource_list ${_res_list})
		endforeach()
		
		add_custom_command(
			OUTPUT ${_output_file}
			COMMAND ${X_QT_RCC} "-binary" -no-compress ${_input_files} -o "${_output_file}"
			DEPENDS ${_input_files} ${_qresource_list}
			COMMENT "Compiling ${_WCC_INPUT} to ${_WCC_OUTPUT}"
			)
		source_group(qrc FILES ${_WCC_INPUT})
	elseif("!${_compiler}" STREQUAL "!lrelease")
		x_find_qt_lrelease()
		add_custom_command(
			OUTPUT ${_output_file}
			COMMAND ${X_QT_LRELEASE} ${_input_files} -qm "${_output_file}"
			DEPENDS ${_input_files}
			)
	else()
		message(FATAL_ERROR "Unknown Compiler:${_compiler}!")
	endif()
	list(APPEND X_CURRENT_PACKAGE_RESES ${_output_file})
endmacro()

# x_end_package()
macro(x_end_package)
	if(OS_WIN)
		_generate_binary_info_file()
	endif()

	set(_srcs_for_compile ${X_CURRENT_PACKAGE_SRCS})
	_deal_sources(_srcs_for_compile)

	if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "STATIC!")
		add_library(${X_CURRENT_PACKAGE_NAME} STATIC ${_srcs_for_compile})
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "SHARED!")
		add_library(${X_CURRENT_PACKAGE_NAME} SHARED ${_srcs_for_compile})
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "MODULE!")
		add_library(${X_CURRENT_PACKAGE_NAME} MODULE ${_srcs_for_compile})
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "EXECUTABLE!")
		if(OS_WIN)
			add_executable(${X_CURRENT_PACKAGE_NAME} WIN32 ${_srcs_for_compile})
			if(X_EXECUTABLE_ENTRYPOINT)
				_append_target_property_string(${X_CURRENT_PACKAGE_NAME} LINK_FLAGS " /ENTRY:\"${X_EXECUTABLE_ENTRYPOINT}CRTStartup\" ")
			endif()
		else()
			add_executable(${X_CURRENT_PACKAGE_NAME} ${_srcs_for_compile})
		endif()
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "CONSOLE!")
		add_executable(${X_CURRENT_PACKAGE_NAME} ${_srcs_for_compile})
	elseif("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "NONE!")
		add_custom_target(${X_CURRENT_PACKAGE_NAME} ALL
			DEPENDS ${_srcs_for_compile} ${X_CURRENT_PACKAGE_GENERATEE_FILES}
			SOURCES ${_srcs_for_compile}
			)
	else()
		message(FATAL_ERROR "Unknown package type.\n")
	endif()

	_disable_analysis_for_generated_file(_srcs_for_compile)

	_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
			COMPILE_FLAGS " ${X_CURRENT_PACKAGE_OPTIMIZATION} ")
	if(OS_WIN)
		_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
				COMPILE_FLAGS " /${X_CURRENT_PACKAGE_RUNTIME_LIBRARY_TYPE} ")
	endif()
	
	if(OS_WIN AND 
		("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "EXECUTABLE!" OR 
		"${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "CONSOLE!"))
		
		if(X_UAC_EXECUTION_LEVEL)
			_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
					LINK_FLAGS " /level='${X_UAC_EXECUTION_LEVEL}' ")
		endif()
		if(X_CURRENT_PACKAGE_DEP)
			_append_target_property_string(${X_CURRENT_PACKAGE_NAME} LINK_FLAGS " /${X_CURRENT_PACKAGE_DEP} ")
		endif()
	endif()
	
	if(OS_WIN)
		if (DEFINED X_CURRENT_EXTRA_LINK_FLAGS)
			_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
					LINK_FLAGS " ${X_CURRENT_EXTRA_LINK_FLAGS}")
		endif()
	endif()
	
	if(OS_WIN AND
		DEFINED CMAKE_USE_LTCG AND
		DEFINED X_CURRENT_USE_PGO AND
		"!${CMAKE_BUILD_TYPE}" STREQUAL "!Release"
		)
		_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
					COMPILE_FLAGS " /GL /Gy")

		if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "EXECUTABLE!" OR
			"${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "SHARED!")
			if("!${CMAKE_USE_LTCG}" STREQUAL "!PGInstrument")
				_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
						LINK_FLAGS " /LTCG:PGInstrument")
			elseif("!${CMAKE_USE_LTCG}" STREQUAL "!PGOptimize")
				_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
						LINK_FLAGS " /LTCG:PGOptimize")
			else()
				_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
						LINK_FLAGS " /LTCG")
			endif()
		endif()
	endif()

	if(OS_WIN)
		if (DEFINED X_CURRENT_DOTNET_CLR)
			_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
					VS_DOTNET_TARGET_FRAMEWORK_VERSION "v2.0")

			_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
					VS_GLOBAL_KEYWORD "ManagedCProj")
			
			_append_target_property_string(${X_CURRENT_PACKAGE_NAME} 
					COMPILE_FLAGS "/clr /EHa")

			if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
				string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
			endif()

			if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
				string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
			endif()
		endif()
	endif()	

	if(OS_LINUX)
		x_find_split_symbol()
		if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "EXECUTABLE!" OR
			"${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "CONSOLE!")
			set(_out_file ${X_CURRENT_PACKAGE_NAME})
			add_custom_command(TARGET ${X_CURRENT_PACKAGE_NAME} POST_BUILD
				COMMAND ${X_SPLIT_SYMBOL} ${X_SPLIT_SYMBOL_ARGS} ${_out_file}
				WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
				)
		endif()
		if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "SHARED!" OR
			"${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "MODULE!")
			set(_out_file "lib${X_CURRENT_PACKAGE_NAME}.so")
			add_custom_command(TARGET ${X_CURRENT_PACKAGE_NAME} POST_BUILD
				COMMAND ${X_SPLIT_SYMBOL} ${X_SPLIT_SYMBOL_ARGS} ${_out_file}
				WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
				)
		endif()
	endif()

	if(X_CURRENT_PACKAGE_DEFINITIONS)
		set_property(TARGET ${X_CURRENT_PACKAGE_NAME} 
				PROPERTY COMPILE_DEFINITIONS "${X_CURRENT_PACKAGE_DEFINITIONS}")
	endif()

	if(X_CURRENT_PACKAGE_LINK_LIBRARYS)
		target_link_libraries(${X_CURRENT_PACKAGE_NAME} ${X_CURRENT_PACKAGE_LINK_LIBRARYS})
		set_property(TARGET ${X_CURRENT_PACKAGE_NAME} PROPERTY X_LINK_LIBRARYS ${X_CURRENT_PACKAGE_LINK_LIBRARYS})
	endif()
	if(X_CURRENT_PACKAGE_LINK_PKGS)
		set(X_PACKAGE_LINK_DEPENDS ${X_PACKAGE_LINK_DEPENDS} 
			${X_CURRENT_PACKAGE_NAME}
			${X_CURRENT_PACKAGE_LINK_PKGS}
			"X_PACKAGE_LINK_DEPENDS_SEPARATOR"
			CACHE INTERNAL "" FORCE)
	endif()
	if(X_CURRENT_PACKAGE_DEPEND_PKGS)
		add_dependencies(${X_CURRENT_PACKAGE_NAME} ${X_CURRENT_PACKAGE_DEPEND_PKGS})
	endif()

	if(X_CURRENT_PACKAGE_HAS_PUBLIC_HEADER)
		set(_pub_dir "${CMAKE_CURRENT_BINARY_DIR}/include")
		set_property(TARGET ${X_CURRENT_PACKAGE_NAME} PROPERTY X_PUBLIC_HEADER_DIR "${_pub_dir}")
	endif()

	set_property(TARGET ${X_CURRENT_PACKAGE_NAME} PROPERTY X_PACKAGE_TYPE "${X_CURRENT_PACKAGE_TYPE}")

	set(X_PACKAGE_INFO_LIST "${X_PACKAGE_INFO_LIST}${X_CURRENT_PACKAGE_NAME}    ${X_CURRENT_PACKAGE_TYPE}    ${CMAKE_CURRENT_SOURCE_DIR};" CACHE INTERNAL "" FORCE)
endmacro()

# x_extern_package(_pkg_name _pkg_type
#					<LOCATION _location>
#					[IMP_LOCATION _imp_location]
#					[BINARY_NAMES _name]
#					[BINARY_NAMES_DEBUG _name_dbg]
#					[BINARY_NAMES_RELEASE _name_rls]
#					[PUBLIC_HEADER _pub_hdr]
#					[DEPENDS ...]
#					[SYS_LIB]
macro(x_extern_package _pkgname _type)
	# a bug on imported target? imported target could not referenced by other file.
	set(_args ${ARGN})
	cmake_parse_arguments(
		X_EXTERN_PACKAGE 
		"SYS_LIB"
		"LOCATION;IMP_LOCATION"
		"PUBLIC_HEADER;DEPENDS;BINARY_NAMES;BINARY_NAMES_DEBUG;BINARY_NAMES_RELEASE"
		${_args}
		)

	set(_names ${X_EXTERN_PACKAGE_BINARY_NAMES} ${X_EXTERN_PACKAGE_BINARY_NAMES_${BUILD_TYPE_UPPER}})
	if(NOT X_EXTERN_PACKAGE_IMP_LOCATION)
		set(X_EXTERN_PACKAGE_IMP_LOCATION ${X_EXTERN_PACKAGE_LOCATION})
	endif()
	set(_package_destdir "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")	
	set(_output_files)

	foreach(_name ${_names})
		if(OS_WIN)
			set(_location "${X_EXTERN_PACKAGE_LOCATION}/${_name}.dll")
			set(_implib "${X_EXTERN_PACKAGE_IMP_LOCATION}/${_name}.lib")
		elseif(OS_LINUX)
			set(_location "${X_EXTERN_PACKAGE_LOCATION}/lib${_name}.so")
			set(_implib "${X_EXTERN_PACKAGE_IMP_LOCATION}/lib${_name}.so")
		else()
			message(FATAL_ERROR "Unknow platform!")
		endif()
		
		if(OS_WIN AND NOT X_EXTERN_PACKAGE_SYS_LIB)
			get_filename_component(_filename_we "${_location}" NAME_WE)
			get_filename_component(_location_path "${_location}" PATH)
			if(EXISTS "${_location_path}/${_filename_we}.pdb")
				set(_setup_dbg_symbol_command COMMAND ${CMAKE_COMMAND} -E copy ${_location_path}/${_filename_we}.pdb ${_package_destdir}/${_filename_we}.pdb)
			endif()
		endif()

		if(OS_LINUX AND NOT X_EXTERN_PACKAGE_SYS_LIB)
			set(_so_file_name "lib${_name}.so")
			x_find_split_symbol()
			set(_setup_dbg_symbol_command COMMAND ${X_SPLIT_SYMBOL} ${X_SPLIT_SYMBOL_ARGS} ${_so_file_name})
		endif()
		
		if("${_type}!" STREQUAL "SHARED!" OR "${_type}!" STREQUAL "MODULE!")
			get_filename_component(_filename "${_location}" NAME)
			if(OS_WIN)
				set(_cp_command COMMAND ${CMAKE_COMMAND} -E copy ${_location} ${_package_destdir})
			elseif(OS_LINUX)
				if(NOT EXISTS ${_package_destdir})
					file(MAKE_DIRECTORY "${_package_destdir}")
				endif()
				if (X_EXTERN_PACKAGE_SYS_LIB)
					x_find_copy_syslib()
					set(_cp_command COMMAND ${X_COPY_SYSLIB} ${_location} ${_package_destdir})
				else()
					set(_cp_command COMMAND cp -R ${_location}* ${_package_destdir})
				endif()
			else()
				message(FATAL_ERROR "Unknow platform!")
			endif()

			if(NOT EXISTS "${_location}")
				add_custom_command(
					OUTPUT ${_package_destdir}/${_filename}
					${_cp_command}
					${_setup_dbg_symbol_command}
					WORKING_DIRECTORY ${_package_destdir}
					)
			else()
				add_custom_command(
					OUTPUT ${_package_destdir}/${_filename}
					${_cp_command}
					${_setup_dbg_symbol_command}
					WORKING_DIRECTORY ${_package_destdir}
					MAIN_DEPENDENCY "${_location}"
					)
			endif()
			
			list(APPEND _output_files ${_package_destdir}/${_filename})
		endif()
	endforeach()
	
	if("${_type}!" STREQUAL "STATIC!")
		add_custom_target(${_pkgname})
	elseif("${_type}!" STREQUAL "SHARED!" OR "${_type}!" STREQUAL "MODULE!")
		add_custom_target(
			${_pkgname} ALL
			DEPENDS ${_output_files}
			)
	else()
		message(FATAL_ERROR "${_type} is not a valid extern package type.")
	endif()

	if(X_EXTERN_PACKAGE_DEPENDS)
		add_dependencies(${_pkgname} ${X_EXTERN_PACKAGE_DEPENDS})
	endif()

	if(X_EXTERN_PACKAGE_PUBLIC_HEADER)
		set_property(TARGET ${_pkgname} 
			PROPERTY X_PUBLIC_HEADER_DIR "${X_EXTERN_PACKAGE_PUBLIC_HEADER}")
	endif()

	set_property(TARGET ${_pkgname} PROPERTY IMPORTED_LOCATION "${_location}")
	set_property(TARGET ${_pkgname} PROPERTY IMPORTED_IMPLIB "${_implib}")
	set_property(TARGET ${_pkgname} PROPERTY X_PACKAGE_TYPE "EXTERN")
endmacro()

# x_include_packages()
macro(x_include_packages)
	_args_system_filter(_cur_system_argn ${ARGN})
	foreach(_pkg ${_cur_system_argn})
		if(NOT TARGET ${_pkg})
			message(FATAL_ERROR "${_pkg} is not a valid package.")
		endif()
		get_property(_pkg_type TARGET ${_pkg} PROPERTY X_PACKAGE_TYPE)
		if(NOT ${_pkg_type} STREQUAL "NONE")
			get_property(_pub_dir TARGET ${_pkg} PROPERTY X_PUBLIC_HEADER_DIR)
			if(NOT _pub_dir)
				message(WARNING "${_pkg} do not has public header.")
			endif()
			include_directories(${_pub_dir})
			list(APPEND X_CURRENT_PACKAGE_DEPEND_PKGS ${_pkg})
			list(APPEND X_CURRENT_PACKAGE_INCLUDE_PKG_DIRS ${_pub_dir})
		endif()
	endforeach()
endmacro()

# x_final_deal()
macro(x_final_deal)
	_deal_link_packages()

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

# x_set_executable_entrypoint(point) this is for windows platform.
macro(x_set_executable_entrypoint ep)
	set(X_EXECUTABLE_ENTRYPOINT ${ep})
endmacro()

# x_set_uac_execution_level(level) this is for windows platform.
#								level: asInvoker, highestAvailable, requireAdministrator.
macro(x_set_uac_execution_level _level)
	set(X_UAC_EXECUTION_LEVEL ${_level})
endmacro()

# x_set_incompatible_dep() this is for windows platform.
macro(x_set_incompatible_dep)
	set(X_CURRENT_PACKAGE_DEP "NXCOMPAT:NO")
endmacro()

# x_set_runtime_library_type(type) this is for windows platform.
#								Release: MD MT, Debug: MDd MTd.
macro(x_set_runtime_library_type _type)
	set(X_CURRENT_PACKAGE_RUNTIME_LIBRARY_TYPE "${_type}")
	if("!${CMAKE_BUILD_TYPE}" STREQUAL "!Debug")
		set(X_CURRENT_PACKAGE_RUNTIME_LIBRARY_TYPE "${_type}d")
	endif()
endmacro()

# x_set_optimization(level) 
#						only work at Release.
#						level: NONE MIN_SIZE MAX_SPEED, default: MIN_SIZE.
macro(x_set_optimization _level)
	if("!${CMAKE_BUILD_TYPE}" STREQUAL "!Release")
		if("!${_level}" STREQUAL "!NONE")
			set(X_CURRENT_PACKAGE_OPTIMIZATION "${CXX_OPTIMIZATION_NONE_FLAGS}")
		elseif("!${_level}" STREQUAL "!MIN_SIZE")
			set(X_CURRENT_PACKAGE_OPTIMIZATION "${CXX_OPTIMIZATION_MINSIZE_FLAGS}")
		elseif("!${_level}" STREQUAL "!MAX_SPEED")
			set(X_CURRENT_PACKAGE_OPTIMIZATION "${CXX_OPTIMIZATION_MAXSPEED_FLAGS}")
		else()
			message(FATAL_ERROR "macro x_set_optimization does not recognize argument: \"${_level}\"")
		endif()
	endif()
endmacro()

# x_add_link_flags(opt) 
macro(x_add_link_flags _opt)
	set(X_CURRENT_EXTRA_LINK_FLAGS ${_opt})
endmacro()

# x_add_dependencies()
macro(x_add_dependencies)
	_args_system_filter(_cur_system_argn ${ARGN})
	set(X_CURRENT_PACKAGE_DEPEND_PKGS ${X_CURRENT_PACKAGE_DEPEND_PKGS} ${_cur_system_argn})
endmacro()

# x_set_pgo() this is for windows platform.
macro(x_set_pgo)
	set(X_CURRENT_USE_PGO "yes")
endmacro()

# x_set_dotnet_clr() this is for windows platform.
macro(x_set_dotnet_clr)
	set(X_CURRENT_DOTNET_CLR "yes")
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
set(X_CONFIGURE_FILE_DIRECTORY "${CMAKE_BINARY_DIR}/x_configure_file")
set(X_PACKAGE_INFO_LIST "" CACHE INTERNAL "app package info list for project_info.txt" FORCE)
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
