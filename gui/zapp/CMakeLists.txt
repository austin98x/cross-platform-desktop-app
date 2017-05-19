x_package(app EXECUTABLE)
	x_add_definitions(
		)
	x_include_directories(
		../../include
		../include
		.
		)
	x_include_packages(
		QtCore
		QtGui
		)
	x_add_sources(
		PCH stdafx.h stdafx.cpp
		QT_AUTOMOC
		src/zxappapplication.cpp
		src/zxappapplication.h
		src/zxappmainwindow.cpp
		src/zxappmainwindow.h
		src/main.cpp
		)
	x_link_packages(
		QtCore
		QtGui
		bfc
		zshare
		)
	x_declare_fileinfo(
		FILE_DESCRIPTION "App"
		)
x_end_package()
