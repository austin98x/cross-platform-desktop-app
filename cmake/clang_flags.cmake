# CMAKE_C_FLAGS... for c 
# CMAKE_CXX_FLAGS... for c++
# CMAKE_<LANG>_FLAGS for common
# CMAKE_<LANG>_FLAGS_DEBUG for debug configuration
# CMAKE_<LANG>_FLAGS_RELEASE for release configuration
# CMAKE_<LANG>_FLAGS_CRITICAL_RELEASE for some projects which is time critial

if(X_PRINT_TIME_SPENT)
	add_definitions(-D__PRINT_TIME_SPENT)
endif()

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386"
	OR ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i586"
	OR ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
	SET(CPU_X86 TRUE)
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
	SET(CPU_X86_64 TRUE)
else()
	message(FATAL_ERROR "Unsupport CPU architecture: ${CMAKE_SYSTEM_PROCESSOR}!")
endif()

if(CMAKE_SIZEOF_VOID_P MATCHES "4")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Winvalid-pch -march=i686 -mtune=i686 -fPIC")
elseif(CMAKE_SIZEOF_VOID_P MATCHES "8")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Winvalid-pch -march=x86-64 -mtune=generic -fPIC")
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Winvalid-pch -fPIC")
endif()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-trigraphs")
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG -D_DEBUG -DQT_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-g -DNDEBUG -DQT_NO_DEBUG")
if(X_USING_ASAN)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

# remove -fvisibility-inlines-hidden -Wcomment -Wignored-attributes
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fvisibility-ms-compat -Werror=return-type -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

#disable cxx warning to make the project clean and easier to solve specified warning
set(DISABLE_CXX_WARNINGS
	inconsistent-missing-override
	ignored-attributes
	comment
	c++11-narrowing
	null-conversion
	switch
	unused-value
	enum-compare
	deprecated-register
	parentheses
	logical-op-parentheses
	)
foreach(_x ${DISABLE_CXX_WARNINGS})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-${_x}")
endforeach()

set(CXX_OPTIMIZATION_NONE_FLAGS "-O0")
set(CXX_OPTIMIZATION_MINSIZE_FLAGS "-Os")
set(CXX_OPTIMIZATION_MAXSPEED_FLAGS "-O3")

set(COMMON_LINKER_FLAGS "")
set(COMMON_LINKER_FLAGS "${COMMON_LINKER_FLAGS} -lc++abi")
if(X_USING_ASAN)
	set(COMMON_LINKER_FLAGS "${COMMON_LINKER_FLAGS} -fsanitize=address")
endif()

set(CMAKE_EXE_LINKER_FLAGS ${COMMON_LINKER_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='\$ORIGIN${EXTRA_RPATH}' -Wl,-rpath-link=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

#  When linking shared libraries, the AddressSanitizer run-time is not linked, so -Wl,-z,defs may cause link errors (don’t use it with AddressSanitizer)
if (NOT X_USING_ASAN)
	set(COMMON_LINKER_FLAGS "${COMMON_LINKER_FLAGS} -Wl,--no-undefined")
endif()

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_MODULE_LINKER_FLAGS ${COMMON_LINKER_FLAGS})
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})

set(CMAKE_SHARED_LINKER_FLAGS ${COMMON_LINKER_FLAGS})
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})

set(CMAKE_CXX_CREATE_SHARED_LIBRARY "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <CMAKE_SHARED_LIBRARY_SONAME_CXX_FLAG><TARGET_SONAME> -o <TARGET> -Wl,--start-group <OBJECTS> <LINK_FLAGS> <LINK_LIBRARIES> -Wl,--end-group")
set(CMAKE_CXX_CREATE_SHARED_MODULE "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <CMAKE_SHARED_LIBRARY_SONAME_CXX_FLAG><TARGET_SONAME> -o <TARGET> -Wl,--start-group <OBJECTS> <LINK_FLAGS> <LINK_LIBRARIES> -Wl,--end-group")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER>  <FLAGS> <CMAKE_CXX_LINK_FLAGS> -o <TARGET> -Wl,--start-group <OBJECTS> <LINK_FLAGS> <LINK_LIBRARIES> -Wl,--end-group")
