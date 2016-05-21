if(NOT EXISTS "${INPUT_FILE}")
	message("Input file does not exists.")
endif()

get_filename_component(_filename ${INPUT_FILE} NAME_WE)
file(STRINGS "${INPUT_FILE}" _input_cont)

set(_need_moc NO)

foreach(_l ${_input_cont})
	if(_l MATCHES "^[ \\t]*#[ \\t]*include[ \\t]*\"[ \\t]*${_filename}\\.moc[ \\t]*\"[ \\t]*$")
		set(_need_moc YES)
		break()
	endif()
endforeach()

if(_need_moc)
	set(_args)

	foreach(_d ${DEFINITIONS})
		list(APPEND _args "-D${_d}")
	endforeach()

	foreach(_i ${INCLUDES})
		list(APPEND _args "-I${_i}")
	endforeach()

	execute_process(
		COMMAND ${MOC_BIN} ${INPUT_FILE} ${_args}
		OUTPUT_VARIABLE _o
		RESULT_VARIABLE _r
		)
	if(NOT _r EQUAL 0)
		message(FATAL_ERROR "Failed to create moc file!")
	endif()
	#Filter generation time to improve the ccache hit rate
	string(REGEX REPLACE "\n\\*\\* Created:[^\n]*\n" "\n" _o2 "${_o}")
	file(WRITE ${OUTPUT_FILE} "${_o2}")
else()
	file(WRITE ${OUTPUT_FILE} "")
endif()
