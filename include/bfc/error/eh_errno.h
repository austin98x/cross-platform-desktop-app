// -------------------------------------------------------------------------- //
//	File name		：	eh_errno.h
//	Author 			：	Austin
//	Create Time		：	2016-2-17 16:32:14
//	Description 	：	Error number 
//
// -------------------------------------------------------------------------- //

#ifndef __EH_ERRNO_H__
#define __EH_ERRNO_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------- //
#ifndef X_OS_WINDOWS
#include "errno_unix.h"
#endif

// -------------------------------------------------------------------------- //

#ifndef KS_MAKE_ERRNO
#define KS_MAKE_ERRNO(Facility, errno)										\
( ((0xf000 | (Facility)) << 16) | (errno) )
#endif

#ifndef KS_MAKE_SCODE
#define KS_MAKE_SCODE(Facility, scode)										\
( ((0x3000 | (Facility)) << 16) | (scode) )
#endif

// -------------------------------------------------------------------------- //

#define KS_FACILITY_BFC			0xff1
#define KS_FACILITY_CORE		0xff2
#define KS_FACILITY_DATA		0xff3
#define KS_FACILITY_UI			0xff4

// -------------------------------------------------------------------------- //
// --> BFC

#ifndef MAKE_BFC_ERRNO
#define MAKE_BFC_ERRNO(errno)		KS_MAKE_ERRNO(KS_FACILITY_BFC, errno)
#endif

#ifndef MAKE_BFC_SCODE
#define MAKE_BFC_SCODE(scode)		KS_MAKE_SCODE(KS_FACILITY_BFC, scode)
#endif


#define BFC_E_OUTOFRANGE			MAKE_BFC_ERRNO(0x0001)
#define BFC_E_NULL					MAKE_BFC_ERRNO(0x0002)
#define BFC_E_CUSTOM				MAKE_BFC_ERRNO(0x0003)

// -------------------------------------------------------------------------- //
// --> Core Layer

#ifndef MAKE_CORE_ERRNO
#define MAKE_CORE_ERRNO(errno)		KS_MAKE_ERRNO(KS_FACILITY_CORE, errno)
#endif

#ifndef MAKE_CORE_SCODE
#define MAKE_CORE_SCODE(scode)		KS_MAKE_SCODE(KS_FACILITY_CORE, scode)
#endif

// -------------------------------------------------------------------------- //
// --> Data Layer

#ifndef MAKE_DATA_ERRNO
#define MAKE_DATA_ERRNO(errno)		KS_MAKE_ERRNO(KS_FACILITY_DATA, errno)
#endif

#ifndef MAKE_DATA_SCODE
#define MAKE_DATA_SCODE(scode)		KS_MAKE_SCODE(KS_FACILITY_DATA, scode)
#endif

// -------------------------------------------------------------------------- //
// --> UI Layer

#ifndef MAKE_UI_ERRNO
#define MAKE_UI_ERRNO(errno)		KS_MAKE_ERRNO(KS_FACILITY_UI, errno)
#endif

#ifndef MAKE_UI_SCODE
#define MAKE_UI_SCODE(scode)		KS_MAKE_SCODE(KS_FACILITY_UI, scode)
#endif

// -------------------------------------------------------------------------- //

#endif // __EH_ERRNO_H__
