# CMAKE_C_FLAGS. for c 
# CMAKE_CXX_FLAGS. for c++
# CMAKE_<LANG>_FLAGS for common
# CMAKE_<LANG>_FLAGS_DEBUG for debug configuration
# CMAKE_<LANG>_FLAGS_RELEASE for release configuration
# CMAKE_<LANG>_FLAGS_CRITICAL_RELEASE for some projects which is time critial

add_definitions(
	-DNOMINMAX 
	-DWIN32 
	-D_WINDOWS 
	-D_CRT_SECURE_NO_WARNINGS 
	-D_SCL_SECURE_NO_WARNINGS 
	-D_CRT_NONSTDC_NO_WARNINGS
	-D_SECURE_SCL=0 
	-D_BIND_TO_CURRENT_VCLIBS_VERSION=1
	)
	
if(X_STATIC_CODE_ANALYZE)
	add_definitions(-DCODE_ANALYSIS)
endif()

if(X_DETECT_MEMORY_LEAK)
	add_definitions(-DDETECT_MEMORY_LEAK)
endif()

set(DISABLED_WARNING
	4297
	4251
	4355
	4127
	4512
	4201
	4100
	4290
	4961
	4945
	4005
	4013
	4244
	4229
	4190
	4624

	6255
	6387
	6011
	6326
	6263
	6001
	6031
	6246
	6386
	6400
	6385
	6328
	6211
	6384
	6315
	6278
	6204
	6269
	6309
	6230
	6294
	6244
	6242
	6053
	6262
	6273
	6308
	6239
	6057
	6054
	6401
	6258
	6221
	6219
	6320
	6283
	6237
	6250
	6215
	6284
	6225
	6323
	6313
	6297
	6214
	6303
	6336
	6298
	6282
	6277
	6335
	6302
	6305
	6295
	6287
	6280
	6216
	6289
	6236
	)

set(CMAKE_C_FLAGS "/MP /W3 /WX /Zm500 /Zi /nologo /Oy- /Gm- /GS /Zc:wchar_t- /Gd /GR")
foreach(_x ${DISABLED_WARNING})
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd${_x} ")
endforeach()
if(X_STATIC_CODE_ANALYZE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /analyze ")
endif()
set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /DQT_DEBUG /RTC1")
set(CMAKE_C_FLAGS_RELEASE "/DNDEBUG /DQT_NO_DEBUG")

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} /EHsc")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

set(CXX_OPTIMIZATION_NONE_FLAGS "/Od /Ob0")
set(CXX_OPTIMIZATION_MINSIZE_FLAGS "/O1 /Ob1 /Os")
set(CXX_OPTIMIZATION_MAXSPEED_FLAGS "/O2 /Ob2 /Ot")

set(CMAKE_IDL_FLAGS "/W3 /nologo /env win32 /Oicf")

if(CMAKE_CL_64)
	set(CMAKE_EXE_LINKER_FLAGS "/machine:X64 /debug /MANIFESTDEPENDENCY:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df'\"")
else()
	set(CMAKE_EXE_LINKER_FLAGS "/machine:X86 /debug /MANIFESTDEPENDENCY:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df'\"")
endif()

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /OPT:REF /OPT:ICF")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/INCREMENTAL")

set(CMAKE_MODULE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})

set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DYNAMICBASE:NO /FIXED")

if(NOT CMAKE_RC_CREATE_SHARED_LIBRARY)
	# avoid cmake's bug treat resource dll as normal dll
	# use package(xxx_lngid LNG_LEGACY) instand of package(xxx SHARED)
	set(CMAKE_RC_CREATE_SHARED_LIBRARY "${CMAKE_C_CREATE_SHARED_LIBRARY}")
endif()
