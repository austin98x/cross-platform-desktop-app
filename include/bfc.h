// -------------------------------------------------------------------------- //
//	File name		：	bfc.h
//	Author 			：	Austin
//	Create Time		：	2016-2-16 13:44:32
//	Description 	：	Basic Foundation Classes
//
// -------------------------------------------------------------------------- //

#ifndef __BFC__
#define __BFC__

// -------------------------------------------------------------------------- //
#define __BFC_INCLUDE__

// [PREDEF]
#include "bfc/predef/pre_platform.h"
#include "bfc/predef/pre_def.h"

// [ERR_HANDLE]
#include "bfc/error/eh_errno.h"
#include "bfc/error/eh_check.h"
#include "bfc/error/eh_exception.h"

// [STRING]
#include "bfc/strapi/strapi.h"
#include "bfc/strapi/transcode.h"

// [ALLOCTATOR]

// [THREAD]
#include "bfc/thread/thread.h"

// [COM]
#include "bfc/com/com.h"

// [POINTER]
#include "bfc/pointer/ptr.h"

// [BSTR]
#include "bfc/bstr/bstr.h"

// [SAFEARRAY]


// [VARIANT]
#include "bfc/variant/variant.h"

// [OS Lite]
#include "bfc/oslite/os_file.h"

#undef __BFC_INCLUDE__

// -------------------------------------------------------------------------- //

#endif	// __BFC__
