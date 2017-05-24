x_find_qt()

set(_dbg_suffix "")
set(_rls_suffix "")

if(OS_WIN)
	set(_dbg_suffix "d4")
	set(_rls_suffix "4")
endif()

x_extern_package(
	QtCore SHARED
	LOCATION ${X_QT_PATH}/lib
	BINARY_NAMES_DEBUG QtCore${_dbg_suffix}
	BINARY_NAMES_RELEASE QtCore${_rls_suffix}
	PUBLIC_HEADER ${X_QT_PATH}/include
				  ${X_QT_PATH}/include/QtCore
	X_ADD_INSTALL
	)

x_extern_package(
	QtGui SHARED
	LOCATION ${X_QT_PATH}/lib
	BINARY_NAMES_DEBUG QtGui${_dbg_suffix}
	BINARY_NAMES_RELEASE QtGui${_rls_suffix}
	PUBLIC_HEADER ${X_QT_PATH}/include
				  ${X_QT_PATH}/include/QtGui
	DEPENDS QtCore
	X_ADD_INSTALL
	)

x_extern_package(
	QtXml SHARED
	LOCATION ${X_QT_PATH}/lib
	BINARY_NAMES_DEBUG QtXml${_dbg_suffix}
	BINARY_NAMES_RELEASE QtXml${_rls_suffix}
	PUBLIC_HEADER ${X_QT_PATH}/include
				  ${X_QT_PATH}/include/QtXml
	DEPENDS QtCore
	X_ADD_INSTALL
	)

set(QtLibrary QtCore QtGui QtXml)
