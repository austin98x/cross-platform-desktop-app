x_package(test-shared SHARED)
	x_add_definitions(
		_USRDLL
		TEST_SHARED_DEF
		)
	x_include_directories(
		../../../include
		./include
		.
		)
	x_add_sources(
		PCH stdafx.h stdafx.cpp
		include/SharedDef.h
		src/SharedImpl.cpp
		)
	x_declare_fileinfo(
		FILE_DESCRIPTION "TEST SHARED"
		)
x_end_package()