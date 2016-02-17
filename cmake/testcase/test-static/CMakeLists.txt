x_package(test-static STATIC)
	x_add_definitions(
		_LIB
		TEST_STATIC_DEF
		)
	x_include_directories(
		../../../include
		./include
		.
		)
	x_add_sources(
		PCH stdafx.h stdafx.cpp
		include/StaticDef.h
		src/StaticImpl.cpp
		)
	x_declare_fileinfo(
		FILE_DESCRIPTION "TEST STATIC"
		)
x_end_package()