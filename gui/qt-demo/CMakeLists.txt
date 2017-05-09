x_package(app EXECUTABLE)
	x_add_definitions(
		)
	x_include_directories(
		../../include
		.
		)
	x_include_packages(
		QtCore
		QtGui
		)
	x_add_sources(
		PCH stdafx.h stdafx.cpp
		QT_AUTOMOC
		mainwindow.cpp
		mainwindow.h
		main.cpp
		mydialog.cpp
		mydialog.h
		mydialog.ui
		application.qrc
		)
	x_link_packages(
		QtCore
		QtGui
		bfc
		)
	x_declare_fileinfo(
		FILE_DESCRIPTION "App"
		)
x_end_package()
