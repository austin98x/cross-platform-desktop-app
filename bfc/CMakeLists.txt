x_package(bfc STATIC)
	x_add_definitions(
		_LIB
		)
	x_include_directories(
		../include
		.
		)
	x_add_sources(
		PCH stdafx.h stdafx.cpp
		LINUX(
			strapi/strapi.cpp
			)
		)
	x_declare_fileinfo(
		FILE_DESCRIPTION "BFC"
		)
x_end_package()
