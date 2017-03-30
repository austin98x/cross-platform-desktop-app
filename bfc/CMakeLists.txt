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
		oslite/os_file.cpp
		LINUX(
			strapi/strapi.cpp
			bstr/bstr.cpp
			com/cocreateguid.cpp
			com/guiddef.cpp
			errorinfo/errorinfo.cpp
			safearray/safearray.cpp
			variant/variant.cpp
			variant/propvariant.cpp
			)
		)
	x_declare_fileinfo(
		FILE_DESCRIPTION "BFC"
		)
x_end_package()
