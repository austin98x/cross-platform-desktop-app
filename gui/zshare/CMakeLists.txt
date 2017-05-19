x_package(zshare SHARED)
	x_add_definitions(
		ZSHARE_LIB
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
		src/zglobal.h
		src/zapplication.cpp
		src/zapplication.h
		src/zmainwindow.cpp
		src/zmainwindow.h
		)
	x_link_packages(
		QtCore
		QtGui
		bfc
		)
x_end_package()
