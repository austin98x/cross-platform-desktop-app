/* -------------------------------------------------------------------------
//	File name		：	com.h
//	Author 			：	Austin
//	Create Time		：	2016-2-25 12:55:10
//	Description 	：	Include files for COM
//
// -----------------------------------------------------------------------*/

#ifndef __COM_H__
#define __COM_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

#if defined( X_OS_WINDOWS )
#	include <objbase.h>
#	include <objidl.h>
#	include <oaidl.h>
#	include <ocidl.h>
#	include <oleidl.h>
#	include <propidl.h>
#	include <Ole2.h>
#else
#	include "bfc/predef/pre_unixdef.h"
#	include "guid.h"
#	include "guiddef.h"
#	include "objidl.h"
#	include "oaidl.h"
#	include "ocidl.h"
#	include "oleidl.h"
#	include "propidl.h"
#	include "oleauto.h"
#	include "objbase.h"
#	include "ole2.h"
#endif

#include "comdef.h"
#include "countobj.h"

#endif // __COM_H__
