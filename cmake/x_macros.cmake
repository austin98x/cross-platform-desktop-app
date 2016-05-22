macro(_args_system_filter _filtered_args_ref)
	set(${_filtered_args_ref})
	_impl_args_system_filter(${_filtered_args_ref} ${ARGN})
endmacro()

macro(_impl_args_system_filter _filtered_args_ref)
	set(_argn ${ARGN})
	set(_a)
	while(NOT "!${_argn}" STREQUAL "!")
		_token_list_element(_argn 0 _a)
		if(_a MATCHES "(^WIN$|^LINUX$)")
			list(GET _argn 0 _b)
			if("!${_b}" STREQUAL "!(")
				list(REMOVE_AT _argn 0)
				if(OS_${_a})
					_impl_args_system_filter(${_filtered_args_ref} ${_argn})
				else()
					_del_args()
				endif()
			else()
				list(APPEND ${_filtered_args_ref} "${_a}")
			endif()
		elseif("!${_a}" STREQUAL "!)")
			break()
		else()
			list(APPEND ${_filtered_args_ref} "${_a}")
		endif()
	endwhile()
endmacro()

macro(_token_list_element _tle_list_ref _tle_list_index _tle_element_ref)
	list(GET ${_tle_list_ref} ${_tle_list_index} ${_tle_element_ref})
	list(REMOVE_AT ${_tle_list_ref} ${_tle_list_index})
endmacro()

macro(_del_args)
	_token_list_element(_argn 0 _a)
	while(NOT "!${_a}" STREQUAL "!)")
		if("!${_a}" STREQUAL "!(")
			_del_args()
		endif()
		_token_list_element(_argn 0 _a)
	endwhile()
endmacro()

macro(_uncache_vars)
	foreach(_v_ref ${ARGN})
		get_property(${_v_ref}_CACHE_TYPE CACHE ${_v_ref} PROPERTY TYPE)
		if(NOT ${_v_ref}_CACHE_TYPE)
			message(FATAL_ERROR "Cache entry: ${_v_ref} not exists.")
		endif()
		get_property(${_v_ref}_CACHE_HELPSTRING CACHE ${_v_ref} PROPERTY HELPSTRING)
		get_property(${_v_ref}_CACHE_ADVANCED CACHE ${_v_ref} PROPERTY ADVANCED)
		set(_tmp ${${_v_ref}})
		unset(${_v_ref} CACHE)
		set(${_v_ref} ${_tmp})
		list(APPEND _UNCACHED_VARIANTS_LIST ${_v_ref})
	endforeach()
endmacro()

macro(_recache_vars)
	foreach(_v_ref ${_UNCACHED_VARIANTS_LIST})
		set(${s_v_ref} ${${_v_ref}} CACHE ${${_v_ref}_CACHE_TYPE} ${${_v_ref}_CACHE_HELPSTRING})
		if(${_v_ref}_CACHE_ADVANCED)
			mark_as_advanced(${_v_ref})
		endif()
	endforeach()
endmacro()

# find _radio_options in _input and then remove it in _input
# if no found _default is returned. if more then one found error occused
# example: _token_radio_option(ARGN "AAA|BBB|CC" "BBB" _result)
function(_token_radio_option _input _radio_options _default _output)
	set(_l ${${_input}})
	string(REGEX MATCHALL "[^|]+" _opts "${_radio_options}")
	set(_nhit 0)
	set(_hit)
	foreach(_x ${_l})
		list(FIND _opts "${_x}" _idx)
		if(NOT _idx EQUAL -1)
			math(EXPR _nhit "${_nhit}+1")
			set(_hit "${_x}")
		endif()
	endforeach()
	if(_nhit EQUAL 0)
		set(${_output} ${_default} PARENT_SCOPE)
	elseif(_nhit EQUAL 1)
		set(${_output} ${_hit} PARENT_SCOPE)
		list(REMOVE_ITEM _l "${_hit}")
		set(${_input} ${_l} PARENT_SCOPE)
	else()
		message(FATAL_ERROR "radio option check error!")
	endif()
endfunction()

macro(_generate_binary_info_file)
	if(NOT "${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "NONE!" AND
		NOT	"${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "STATIC!")
		if(X_CURRENT_FILE_VERSION)
			set(X_FILE_VERSION ${X_CURRENT_FILE_VERSION})
		elseif(FILE_VERSION)
			set(X_FILE_VERSION ${FILE_VERSION})
		endif()		
		string(REPLACE "." "," X_FILE_VERSION ${X_FILE_VERSION})
		string(REPLACE "." "," X_PRODUCT_VERSION ${PRODUCT_VERSION})

		string(TOLOWER ${X_CURRENT_PACKAGE_NAME} _lower_package_name)

		if(X_CURRENT_PRODUCT_VERSION)
			set(X_PRODUCT_VERSION ${X_CURRENT_PRODUCT_VERSION})
		endif()

		set(X_FILE_DESCRIPTION ${X_CURRENT_FILE_DESCRIPTION})
		set(X_INTERNAL_NAME ${X_CURRENT_PACKAGE_NAME})
		set(X_COMPANY_NAME ${X_CURRENT_COMPANY_NAME})
		set(X_COPYRIGHT ${X_CURRENT_COPY_RIGHT})
		set(X_PRODUCT_NAME ${X_CURRENT_PRODUCT_NAME})

		set(_rc_file_temp "${X_CONFIG_TEMPLATE_DIR}/Version.rc.in")
		if(X_CURRENT_VERSION_RC_NAME_AFFIX)
			set(_rc_file "${CMAKE_CURRENT_BINARY_DIR}/Version_${X_CURRENT_VERSION_RC_NAME_AFFIX}.rc")
		else()
			set(_rc_file "${CMAKE_CURRENT_BINARY_DIR}/Version.rc")
		endif()
		configure_file(${_rc_file_temp} ${_rc_file}.tmp)
		if("${_rc_file}.tmp" IS_NEWER_THAN "${_rc_file}" AND NOT "!${CMAKE_USE_LTCG}" STREQUAL "!PGOptimize")
			_convert_file_code("UTF-8" "${_rc_file}.tmp" "UTF-16LE" "${_rc_file}")
		endif()
		x_add_sources(${_rc_file})
	endif()	
endmacro()

macro(_deal_link_packages)
	set(_deps)
	foreach(_pkg ${X_PACKAGE_LINK_DEPENDS})
		if(NOT _pkg STREQUAL "X_PACKAGE_LINK_DEPENDS_SEPARATOR")
			list(APPEND _deps ${_pkg})
		else()
			_deal_link_packages_internal(${_deps})
			set(_deps)
		endif()
	endforeach()
	unset(X_PACKAGE_LINK_DEPENDS CACHE)
endmacro()

macro(_deal_link_packages_internal _pkg)
	set(_link_libs)
	set(_link_flags)
	get_property(_pkg_compile_flags TARGET ${_pkg} PROPERTY COMPILE_FLAGS)
	set(X_PACKAGE_${_pkg}_LINK_PACKAGES)
	string(REGEX MATCH "/M[DT]+" _pkg_runtime_lib_type "${_pkg_compile_flags}")
	foreach(_d_pkg ${ARGN})
		if(NOT TARGET ${_d_pkg})
			message(FATAL_ERROR "package ${_d_pkg} not exist. referenced by ${_pkg}")
		endif()
		get_property(_d_pkg_compile_flags TARGET ${_d_pkg} PROPERTY COMPILE_FLAGS)
		string(REGEX MATCH "/M[DT]+" _d_pkg_runtime_lib_type "${_d_pkg_compile_flags}")
		get_property(_d_pkg_type TARGET ${_d_pkg} PROPERTY X_PACKAGE_TYPE)
		if(_d_pkg_runtime_lib_type AND "!${_d_pkg_type}" STREQUAL "!STATIC" AND NOT "!${_pkg_runtime_lib_type}" STREQUAL "!${_d_pkg_runtime_lib_type}")
			message(FATAL_ERROR "package ${_pkg} is ${_pkg_runtime_lib_type}, but ${_d_pkg} is ${_d_pkg_runtime_lib_type}.")
		endif()

		_get_target_implib(${_d_pkg} ${_pkg} _implib)
		list(APPEND _link_libs ${_implib})
		if(X_PACKAGE_${_d_pkg}_LINK_PACKAGES)
			list(APPEND _link_libs ${X_PACKAGE_${_d_pkg}_LINK_PACKAGES})
		endif()
		if(X_PACKAGE_${_d_pkg}_LINK_FLAGS)
			list(APPEND _link_flags ${X_PACKAGE_${_d_pkg}_LINK_FLAGS})
		endif()
	endforeach()

	if(_link_libs)
		list(REMOVE_DUPLICATES _link_libs)
	endif()
	if(_link_flags)
		list(REMOVE_DUPLICATES _link_flags)
	endif()

	get_property(_pkg_package_type TARGET ${_pkg} PROPERTY X_PACKAGE_TYPE)
	if(${_pkg_package_type} STREQUAL "STATIC")
		set(X_PACKAGE_${_pkg}_LINK_PACKAGES ${_link_libs})
		get_property(_pkg_link_librarys TARGET ${_pkg} PROPERTY X_LINK_LIBRARYS)
		set(X_PACKAGE_${_pkg}_LINK_FLAGS ${_link_flags} ${_pkg_link_librarys})
	else()
		if(OS_UNIX)
			set(_extern_link_flags)
			foreach(_link_flag ${_link_flags})
				if(NOT ${_link_flag} MATCHES "^/"
					AND NOT ${_link_flag} MATCHES "^-l")
					set(_link_flag "-l${_link_flag}")
				endif()
				list(APPEND _extern_link_flags ${_link_flag})
			endforeach()
			set(_link_flags ${_extern_link_flags})
		endif()

		set(_extern_link_arg)
		foreach(_link_lib ${_link_libs} ${_link_flags})
			set(_extern_link_arg "${_extern_link_arg} ${_link_lib}")
		endforeach()

		if(_extern_link_arg)
			_append_target_property_string(${_pkg} LINK_FLAGS ${_extern_link_arg})
			set_property(TARGET ${_pkg} APPEND PROPERTY LINK_DEPENDS ${_link_libs})
		endif()
	endif()

	add_dependencies(${_pkg} ${ARGN})
endmacro()

macro(_get_target_implib _gti_pkg _proj _output_ref)
	if(TARGET ${_gti_pkg})
		get_property(_pkg_type TARGET ${_gti_pkg} PROPERTY X_PACKAGE_TYPE)
		if(NOT _pkg_type)
			message(FATAL_ERROR "${_gti_pkg} is not a valid source package. Error in ${_proj}")
		endif()
		if("${_pkg_type}!" STREQUAL "STATIC!")
			if(OS_WIN)
				set(${_output_ref} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${_gti_pkg}.lib")
			elseif(OS_LINUX)
				set(${_output_ref} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib${_gti_pkg}.a")
			else()
				message(FATAL_ERROR "Unknow platform!")
			endif()
		elseif("${_pkg_type}!" STREQUAL "SHARED!")
			if(OS_WIN)
				set(${_output_ref} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${_gti_pkg}.lib")
			elseif(OS_LINUX)
				set(${_output_ref} "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${_gti_pkg}.so")
			else()
				message(FATAL_ERROR "Unknow platform!")
			endif()
		elseif("${_pkg_type}!" STREQUAL "EXECUTABLE!" OR "${_pkg_type}!" STREQUAL "CONSOLE!")
			if(OS_WIN)
				set(${_output_ref} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${_gti_pkg}.lib")
			elseif(OS_LINUX)
				set(${_output_ref} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_gti_pkg}")
			else()
				message(FATAL_ERROR "Unknow platform!")
			endif()
		elseif("${_pkg_type}!" STREQUAL "EXTERN!")
			get_property(${_output_ref} TARGET ${_gti_pkg} PROPERTY IMPORTED_IMPLIB)
		elseif("${_pkg_type}!" STREQUAL "NONE!")
			set(${_output_ref})
		else()
			message(FATAL_ERROR "${_gti_pkg} is a ${_pkg_type} package, do not support be linked.")
		endif()
	else()
		message(FATAL_ERROR "Current Project ${_proj} could not find package named ${_gti_pkg}")
	endif()
endmacro()

macro(_deal_sources _srcs_ref)
	set(_wds_srcs ${${_srcs_ref}})

	set(_wds_uic_gen)
	_deal_uic(_wds_srcs _wds_uic_gen)
	if(_wds_uic_gen)
		x_include_directories("${CMAKE_CURRENT_BINARY_DIR}/uic")
	endif()

	set(_wds_qrc_gen)
	_deal_qrc(_wds_srcs _wds_qrc_gen)
	if(_wds_qrc_gen)
		x_include_directories("${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}")
	endif()

	set(_wds_ts_gen)
	_deal_ts(_wds_srcs _wds_ts_gen)

	set(_srcs_for_compile)
	set(_srcs_grouped)
	set(_group_idx 0)
	foreach(_src ${_wds_srcs})
		if(NOT _src STREQUAL "X_SOURCE_SEPARATOR")
			list(APPEND _srcs_grouped ${_src})
			if(IS_ABSOLUTE ${_src})
				file(RELATIVE_PATH _group_path ${CMAKE_CURRENT_SOURCE_DIR} ${_src})
			else()
				file(RELATIVE_PATH _group_path ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${_src})
			endif()
			get_filename_component(_group_path ${_group_path} PATH)
			file(TO_NATIVE_PATH "${_group_path}" _group_path)
			string(REPLACE "/" "\\" _group_path "${_group_path}")
			source_group("${_group_path}" FILES ${_src})
		else()
			if(_srcs_grouped)
				_deal_sources_group(_srcs_grouped ${_group_idx})
				list(APPEND _srcs_for_compile ${_srcs_grouped})
			endif()
			set(_srcs_grouped)
			math(EXPR _group_idx "${_group_idx}+1")
		endif()
	endforeach()

	set(${_srcs_ref} ${_srcs_for_compile})
endmacro()

macro(_deal_sources_group _srcs_ref _group_idx)
	set(_wdsg_srcs ${${_srcs_ref}})

	set(_qt_automoc NO)
	set(_pch_header "")
	set(_pch_source "")

	list(FIND _wdsg_srcs "QT_AUTOMOC" _automoc_idx)
	if(NOT _automoc_idx EQUAL -1)
		list(REMOVE_AT _wdsg_srcs ${_automoc_idx})
		set(_qt_automoc YES)
	endif()

	list(FIND _wdsg_srcs "PCH" _pch_idx)
	if(NOT _pch_idx EQUAL -1)
		list(REMOVE_AT _wdsg_srcs ${_pch_idx})
		list(GET _wdsg_srcs ${_pch_idx} _pch_header)
		list(REMOVE_AT _wdsg_srcs ${_pch_idx})
		list(GET _wdsg_srcs ${_pch_idx} _pch_source)
		list(REMOVE_AT _wdsg_srcs ${_pch_idx})
	endif()

	# deal automoc before pch, because of automoc will create source file.
	if(_qt_automoc)
		_deal_automoc(_wdsg_srcs "${_pch_header}" ${_group_idx})
	endif()
	
	if(_pch_header)
		_deal_pch(_wdsg_srcs ${_pch_header} ${_pch_source})
	endif()	

	set(${_srcs_ref} ${_wdsg_srcs})
endmacro()

macro(_deal_automoc _srcs_ref _pch_header _group_idx)
	x_find_qt_automoc()

	set(_wda_srcs ${${_srcs_ref}})

	_get_definitions(_ds)
	get_property(_is DIRECTORY PROPERTY INCLUDE_DIRECTORIES)

	set(_headers)
	foreach(_f ${_wda_srcs})
		if(_f MATCHES "(\\.c$|\\.cpp$|\\.cc$|\\.cxx$)")
			get_filename_component(_filename ${_f} NAME_WE)
			set(_moc_filename "${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/${_filename}.moc")
			add_custom_command(
				OUTPUT ${_moc_filename}
				COMMAND ${CMAKE_COMMAND} "-DDEFINITIONS=\"${_ds}\""
										 "-DINCLUDES=\"${_is}\"" 
										 "-DMOC_BIN=\"${X_QT_MOC}\""
										 "-DINPUT_FILE=\"${CMAKE_CURRENT_SOURCE_DIR}/${_f}\""
										 "-DOUTPUT_FILE=\"${_moc_filename}\""
										 -P \"${X_QT_AUTOMOC_CXX_SCRIPT}\"
				DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${_f}"
				)
			get_property(_obj_dep SOURCE "${_f}" PROPERTY OBJECT_DEPENDS)
			if(_obj_dep)
				set(_obj_dep "${_obj_dep};")
			endif()
			set_property(SOURCE "${_f}" PROPERTY OBJECT_DEPENDS "${_obj_dep}${_moc_filename}")
			if(NOT MSVC)
				# Makefile can not deal OBJECT_DEPENDS?
				list(APPEND _wda_srcs ${_moc_filename})
			endif()
			source_group("Generated Files" FILES "${_moc_filename}")
		elseif(_f MATCHES "(\\.h$|\\.hpp$|\\.hh$|\\.hxx$)" AND NOT _f STREQUAL _pch_header)
			list(APPEND _headers "${CMAKE_CURRENT_SOURCE_DIR}/${_f}")
		endif()
	endforeach()

	if(_headers)
		list(SORT _headers)
		list(REMOVE_DUPLICATES _headers)
	endif()

	set(_idx 0)
	while(_headers)
		_list_shift_n(_headers 30 _headers_part)
		set(_list_file_cont "")
		foreach(_h ${_headers_part})
			set(_list_file_cont "${_list_file_cont}${_h}\n")
		endforeach()
		configure_file("${X_CONFIG_TEMPLATE_DIR}/moc_list.in" "${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/moc_list_${_group_idx}_${_idx}")
		add_custom_command(
			OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/_automoc_${_group_idx}_${_idx}.cpp"
			COMMAND ${CMAKE_COMMAND} "-DDEFINITIONS=\"${_ds}\""
									 "-DINCLUDES=\"${_is}\"" 
									 "-DMOC_BIN=\"${X_QT_MOC}\""
									 "-DLIST_FILE=\"${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/moc_list_${_group_idx}_${_idx}\""
									 "-DOUTPUT_FILE=\"${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/_automoc_${_group_idx}_${_idx}.cpp\""
									 "-DPCH_HEADER=\"${_pch_header}\""
									 -P \"${X_QT_AUTOMOC_H_SCRIPT}\"
			DEPENDS ${_headers_part} "${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/moc_list_${_group_idx}_${_idx}"
			)

		# large file put frist to speed up the speed of concurrent compilation
		list(INSERT _wda_srcs 0 "${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/_automoc_${_group_idx}_${_idx}.cpp")
		source_group("Generated Files" FILES "${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/_automoc_${_group_idx}_${_idx}.cpp")
		math(EXPR _idx "${_idx}+1")
	endwhile()

	set(${_srcs_ref} ${_wda_srcs})
endmacro()

macro(_deal_pch _srcs_ref _pch_header _pch_source)
	set(_deal_pch_srcs ${${_srcs_ref}})
	if(MSVC)
		if(CMAKE_GENERATOR MATCHES "^Visual Studio")
			foreach(_x ${_deal_pch_srcs})
				if(_x MATCHES "(\\.cpp$|\\.cc$|\\.cxx$)")
					set_property(SOURCE "${_x}" PROPERTY COMPILE_FLAGS "/Yu\"${_pch_header}\"")
				endif()
			endforeach()
			list(APPEND _deal_pch_srcs ${_pch_header} ${_pch_source})
			set_property(SOURCE "${_pch_source}" PROPERTY COMPILE_FLAGS "/Yc\"${_pch_header}\"")
		else()
			set(_pch_pch ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${X_CURRENT_PACKAGE_NAME}.dir/${_pch_header}.pch)
			set(_pch_obj ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${X_CURRENT_PACKAGE_NAME}.dir/${_pch_source}.obj)
			_get_compile_args(CXX _args)
			_get_pdb_output_fullpath(_pdb_pos)
			foreach(_x ${_deal_pch_srcs})
				if(_x MATCHES "(\\.cpp$|\\.cc$|\\.cxx$)")
					get_property(_flags SOURCE "${_x}" PROPERTY COMPILE_FLAGS)
					set_property(SOURCE "${_x}" 
						PROPERTY COMPILE_FLAGS "${_flags} /Yu\"${_pch_header}\" /Fp\"${_pch_pch}\"")
					get_property(_obj_dep SOURCE "${_x}" PROPERTY OBJECT_DEPENDS)
					if(_obj_dep)
						set(_obj_dep "${_obj_dep};")
					endif()
					set_property(SOURCE "${_x}" PROPERTY OBJECT_DEPENDS "${_obj_dep}${_pch_pch}")
				endif()
			endforeach()
			list(APPEND _deal_pch_srcs ${_pch_header}) # pch's source do not add back to src list
			list(APPEND X_CURRENT_PACKAGE_LINK_LIBRARYS "${_pch_obj}")
			add_custom_command(
				OUTPUT ${_pch_pch} ${_pch_obj}
				COMMAND ${CMAKE_CXX_COMPILER} /c ${_args} ${X_CURRENT_PACKAGE_OPTIMIZATION} /Yc\"${_pch_header}\" 
						/Fp\"${_pch_pch}\" /Fd\"${_pdb_pos}\" /Fo\"${_pch_obj}\"
						"${CMAKE_CURRENT_SOURCE_DIR}/${_pch_source}"
				MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${_pch_source}
				IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${_pch_source}
				COMMENT "Creating Precompiler header..."
				)
		endif()
	else()
		_get_compile_args(CXX _args)
		# pch's source do not used, build same as normal source file.
		list(APPEND _deal_pch_srcs ${_pch_header} ${_pch_source}) 
		_create_include_ref("${_pch_header}" "${CMAKE_CURRENT_BINARY_DIR}/${_pch_header}")
		set(_pch_pch "${CMAKE_CURRENT_BINARY_DIR}/${_pch_header}.gch")
		foreach(_x ${_deal_pch_srcs})
			if(_x MATCHES "(\\.cpp$|\\.cc$|\\.cxx$)")
				set_property(SOURCE "${_x}" PROPERTY OBJECT_DEPENDS "${_pch_pch}")
			endif()
		endforeach()
		if ("${CMAKE_GENERATOR}!" STREQUAL "Ninja!")
			if("${X_CURRENT_PACKAGE_TYPE}!" STREQUAL "SHARED!")
				set(_args ${_args} -D${X_CURRENT_PACKAGE_NAME}_EXPORTS)
			endif()
			add_custom_command(
				OUTPUT ${_pch_pch}
				COMMAND ${X_COMPILER_LEADER} ${CMAKE_CXX_COMPILER} -x c++-header ${_args} ${X_CURRENT_PACKAGE_OPTIMIZATION} "${CMAKE_CURRENT_SOURCE_DIR}/${_pch_header}" -o "${_pch_pch}"
				MAIN_DEPENDENCY ${_pch_header}
				IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${_pch_header}
				COMMENT "Creating Precompiler header..."
				)
		else()
			add_custom_command(
				OUTPUT ${_pch_pch}
				COMMAND ${X_COMPILER_LEADER} ${CMAKE_CXX_COMPILER} -x c++-header "$(CXX_DEFINES)" "$(CXX_FLAGS)" "$(CXX_INCLUDES)" ${X_CURRENT_PACKAGE_OPTIMIZATION} "${CMAKE_CURRENT_SOURCE_DIR}/${_pch_header}" -o "${_pch_pch}"
				MAIN_DEPENDENCY ${_pch_header}
				IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${_pch_header}
				COMMENT "Creating Precompiler header..."
				)
		endif()
		if("!${CMAKE_CXX_COMPILER_ID}" STREQUAL "!GNU")
			foreach(_x ${_deal_pch_srcs})
				if(_x MATCHES "(\\.cpp$|\\.cc$|\\.cxx$)")
					get_property(_flags SOURCE "${_x}" PROPERTY COMPILE_FLAGS)
					set_property(SOURCE "${_x}" 
						PROPERTY COMPILE_FLAGS "${_flags} -fpch-preprocess -include ${CMAKE_CURRENT_BINARY_DIR}/${_pch_header}")
				endif()
			endforeach()
		elseif("!${CMAKE_CXX_COMPILER_ID}" STREQUAL "!Clang")
			foreach(_x ${_deal_pch_srcs})
				if(_x MATCHES "(\\.cpp$|\\.cc$|\\.cxx$)")
					get_property(_flags SOURCE "${_x}" PROPERTY COMPILE_FLAGS)
					set_property(SOURCE "${_x}" 
						PROPERTY COMPILE_FLAGS "${_flags} -include-pch ${_pch_pch}")
				endif()
			endforeach()
		endif()
	endif()
	set(${_srcs_ref} ${_deal_pch_srcs})
endmacro()

macro(_deal_uic _srcs_ref _gen_ref)
	if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/uic/)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/uic/)
	endif()

	set(__srcs ${${_srcs_ref}})
	foreach(_x ${__srcs})
		if(_x MATCHES "\\.ui$")
			x_find_qt_uic()
			get_filename_component(_fname "${_x}" NAME_WE)
			set(_out_name "ui_${_fname}.h")
			set(_out_fullname "${CMAKE_CURRENT_BINARY_DIR}/uic/${_out_name}")

			add_custom_command(
				OUTPUT ${_out_fullname}
				COMMAND ${X_QT_UIC} -o ${_out_fullname} "${CMAKE_CURRENT_SOURCE_DIR}/${_x}"
				MAIN_DEPENDENCY ${_x}
				COMMENT "Compiling ${_x}..."
				)
			list(APPEND ${_gen_ref} ${_out_fullname})
			source_group("Generated Files" FILES "${_out_fullname}")
		endif()
	endforeach()
endmacro()

macro(_deal_qrc _srcs_ref _gen_ref)
	set(__srcs ${${_srcs_ref}})
	set(_qrc_list)
	foreach(_x ${__srcs})
		if(_x MATCHES "\\.qrc$")
			x_find_qt_rcc()
			_scan_qrc(${_x} __srcs _qresource_list)
			list(APPEND _qrc_list ${_x})
			get_filename_component(_fname "${_x}" NAME_WE)
			set(_out_name "qrc_${_fname}.cpp")
			set(_out_fullname "${CMAKE_CURRENT_BINARY_DIR}/moc/${X_CURRENT_PACKAGE_NAME}/${_out_name}")
			add_custom_command(
				OUTPUT ${_out_fullname}
				COMMAND ${X_QT_RCC} -name "${_fname}" -no-compress "${CMAKE_CURRENT_SOURCE_DIR}/${_x}" -o "${_out_fullname}"
				MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/${_x}"
				DEPENDS ${_qresource_list}
				COMMENT "Compiling ${_x}..."
				)
			list(APPEND ${_gen_ref} ${_out_fullname})
			source_group("Generated Files" FILES "${_out_fullname}")
		endif()
	endforeach()
	if(_qrc_list)
		source_group(qrc FILES ${_qrc_list})
	endif()
	set(${_srcs_ref} ${__srcs})
endmacro()

macro(_deal_ts _srcs_ref _gen_ref)
	set(__srcs ${${_srcs_ref}})
	set(_ts_list)
	foreach(_x ${__srcs})
		if(_x MATCHES "\\.ts$")
			list(APPEND _ts_list ${_x})
		endif()
	endforeach()
	if(_ts_list)
		x_find_qt_lrelease()
		x_find_qt_rcc()

		set(_ts_langs)
		foreach(_x ${_ts_list})
			_get_ts_language(${_x} _lang)
			set(_ts_langs ${_ts_langs} ${_lang})
			set(_ts_${_lang}_files ${_ts_${_lang}_files} ${_x})
		endforeach()
		list(REMOVE_DUPLICATES _ts_langs)

		set(_qm_files)
		set(_qm_fpathes)
		foreach(_lang ${_ts_langs})
			set(_files ${_ts_${_lang}_files})
			set(_qm_file "${CMAKE_CURRENT_BINARY_DIR}/qm/${_lang}.qm")
			list(GET _files 0 _main_dep)
			add_custom_command(
				OUTPUT "${_qm_file}"
				COMMAND ${X_QT_LRELEASE} ${_files} -qm "${_qm_file}"
				MAIN_DEPENDENCY ${_main_dep}
				DEPENDS ${_files} ${CMAKE_CURRENT_BINARY_DIR}/qm
				COMMENT "${_files} => ${_qm_file}"
				WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
				)
			list(APPEND _qm_files "qm/${_lang}.qm")
			list(APPEND _qm_fpathes ${_qm_file})
		endforeach()
		add_custom_command(
			OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/qm"
			COMMAND "${CMAKE_COMMAND}" -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/qm
			)

		set(_qrc_cont)
		set(_qm_qrc "${CMAKE_CURRENT_BINARY_DIR}/qm.qrc")
		foreach(_qm ${_qm_files})
			set(_qrc_cont "${_qrc_cont}\t\t<file>${_qm}</file>\n")
		endforeach()
		set(QRC_CONT "${_qrc_cont}")
		configure_file("${X_CONFIG_TEMPLATE_DIR}/qm.qrc.in" ${_qm_qrc})

		set(_qm_cpp "${CMAKE_CURRENT_BINARY_DIR}/qm/qrc_qm.cpp")
		add_custom_command(
			OUTPUT ${_qm_cpp}
			COMMAND ${X_QT_RCC} -no-compress ${_qm_qrc} -o ${_qm_cpp}
			MAIN_DEPENDENCY ${_qm_qrc}
			DEPENDS ${_qm_fpathes}
			COMMENT "Generate ${_qm_cpp}..."
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
			)
		source_group("Generated Files" FILES ${_qm_cpp})
		list(APPEND ${_gen_ref} ${_qm_cpp})
	endif()
endmacro()

macro(_scan_qrc _qrc_file _wsq_srcs _qresource_list_ref)
	# if qrc file change, it will configure again
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${_qrc_file}" "${CMAKE_CURRENT_BINARY_DIR}/${_qrc_file}" COPYONLY)
	set(_qrc_text)
	set(_wds_qres_list)
	get_filename_component(_fname "${_qrc_file}" NAME_WE)
	list(FIND ${_wsq_srcs} "${_qrc_file}" _qrc_file_index)
	get_filename_component(_qrc_path "${_qrc_file}" PATH)

	file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/${_qrc_file}" _qrc_text REGEX "<file")

	set(_wds_qres_list)
	foreach(_qrc_str ${_qrc_text})
		string(REGEX REPLACE "[^<]*<file.*>(.*)</file>.*" "\\1" _qresource_file ${_qrc_str})
		list(APPEND _wds_qres_list "${CMAKE_CURRENT_SOURCE_DIR}/${_qrc_path}/${_qresource_file}")
	endforeach()
	list(REMOVE_DUPLICATES _wds_qres_list)
	if(NOT _qrc_file_index EQUAL "-1")
		list(INSERT ${_wsq_srcs} ${_qrc_file_index} ${_wds_qres_list})
		source_group("qrc\\${_fname}" FILES ${_wds_qres_list})
	endif()
	set(${_qresource_list_ref} ${_wds_qres_list})
endmacro()

function(_get_ts_language _ts_fpath _out_lang)
	file(STRINGS ${_ts_fpath} _lines LIMIT_COUNT 10)
	foreach(_line ${_lines})
		if(_line MATCHES "TS.*language=\".*\"")
			string(REGEX REPLACE ".*TS.*language=\"(.*)\".*" "\\1" _lang ${_line})
			set(${_out_lang} ${_lang} PARENT_SCOPE)
			return()
		endif()
	endforeach()
	message(FATAL_ERROR "Cannot get language from ${_ts_fpath}")
endfunction()

function(_get_compile_args _lang _output)
	if(MSVC)
		set(_def_prefix "/D")
		set(_inc_prefix "/I")
	else()
		set(_def_prefix "-D")
		set(_inc_prefix "-I")
	endif()

	set(_defs)
	foreach(_d ${X_CURRENT_PACKAGE_DEFINITIONS})
		string(REPLACE "\"" "\\\"" _d "${_d}")
		list(APPEND _defs "${_def_prefix}${_d}")
	endforeach()
	get_property(_ds DIRECTORY PROPERTY COMPILE_DEFINITIONS)
	foreach(_d ${_ds})
		string(REPLACE "\"" "\\\"" _d "${_d}")
		list(APPEND _defs "${_def_prefix}${_d}")
	endforeach()
	get_property(_is DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
	set(_incs)
	foreach(_i ${_is})
		list(APPEND _incs "${_inc_prefix}\"${_i}\"")
	endforeach()
	
	string(REGEX MATCHALL "[^ ;]+" _flags "${CMAKE_${_lang}_FLAGS} ${CMAKE_${_lang}_FLAGS_${BUILD_TYPE_UPPER}}")
	set(${_output} ${_incs} ${_defs} ${_flags} PARENT_SCOPE)
endfunction()

macro(_create_include_ref _f _header)
	if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_f}")
		message(FATAL_ERROR "${_f} does not exists!")
	endif()
	if(NOT EXISTS "${_header}")
		get_filename_component(_pub_d "${_header}" PATH)
		file(RELATIVE_PATH _relative_path "${_pub_d}" "${CMAKE_CURRENT_SOURCE_DIR}/${_f}")
		set(_cont "// file created by build system, do not edit!\n\n#include \"${_relative_path}\"\n\n")
		file(WRITE "${_header}" "${_cont}")
	endif()
endmacro()

macro(_disable_analysis_for_generated_file _srcs_ref)
	set(_dafgf_srcs ${${_srcs_ref}})
	if(X_STATIC_CODE_ANALYZE)
		foreach(_src ${_dafgf_srcs})
			if((IS_ABSOLUTE ${_src}) AND 
				(NOT _src MATCHES ${CMAKE_SOURCE_DIR}) AND 
				_src MATCHES "/qrc_.*\\.cpp$"
				)
				set_property(SOURCE "${_src}" PROPERTY COMPILE_FLAGS "/analyze-")
			endif()
		endforeach()
	endif()
endmacro()

macro(_append_target_property_string _target _property _val)
	get_target_property(_orig_val ${_target} ${_property})
	if(_orig_val)
		set_target_properties(${_target} PROPERTIES ${_property} "${_orig_val} ${_val}")
	else()
		set_target_properties(${_target} PROPERTIES ${_property} "${_val}")
	endif()
endmacro()

macro(_convert_file_code _src_code _src_file _dst_code _dst_file)
	file(TO_NATIVE_PATH "${_src_file}" _src_file_native)
	file(TO_NATIVE_PATH "${_dst_file}" _dst_file_native)
	execute_process(
		COMMAND "iconv" "-f" "${_src_code}" "-t" "${_dst_code}" "${_src_file_native}"
		OUTPUT_FILE "${_dst_file_native}"
		RESULT_VARIABLE _execute_result
		)
	if(NOT _execute_result EQUAL 0)
		message(FATAL_ERROR "iconv.exe convert code failed, file:${_src_file_native}")
	endif()
endmacro()
