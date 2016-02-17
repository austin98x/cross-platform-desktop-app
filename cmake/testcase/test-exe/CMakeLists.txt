x_package(test-exe EXECUTABLE)
	x_add_definitions(
		TEST_EXE_DEF
		)
	x_include_directories(
		../../../include
		./include
		.
		)
	x_add_sources(
		PCH stdafx.h stdafx.cpp
		WIN(
			include/TestWindows.h
			)
		LINUX(
			include/TestLinux.h
			)
		include/Test.h
		src/TestMain.cpp
		)
	x_link_packages(
		test-static
		test-shared
		)
	x_declare_fileinfo(
		FILE_DESCRIPTION "TEST EXE"
		)
x_end_package()