// -------------------------------------------------------------------------- //
//	File name		：	pre_def.h
//	Author 			：	Austin
//	Create Time		：	2016-2-16 14:54:21
//	Description 	：	Predefined macros 
//
// -------------------------------------------------------------------------- //

#ifndef __PRE_DEF_H__
#define __PRE_DEF_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif


// -------------------------------------------------------------------------- //
// --> Include Cofiguration
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif
#include "pre_platform.h"
#if defined(X_OS_WINDOWS)
#include <windows.h>
#else
#include "pre_unixdef.h"
#endif

// -------------------------------------------------------------------------- //
// --> Compiler Cofiguration
#if defined(X_CC_VC)
#	define X_VER_VC5							1100
#	define X_VER_VC6							1200
#	define X_VER_VC_NET_2003					1300
#	define X_VER_VC_NET_2005					1400
#   define X_VER_VC_NET_2008                    1500
#	define X_VER_VC_NET_2010					1600
#	define X_VER_VC_NET_2012					1700
#	define X_VER_VC_NET_2013					1800
#	if (_MSC_VER < X_VER_VC_NET_2010)
#		error "the compiler version is too lower, please use msvc2010 or above."
#	endif
    typedef unsigned __int64    __uint64;
#elif defined(X_CC_GCC)
#	define __stdcall			__attribute__((stdcall))
#	define __fastcall			__attribute__((fastcall))
#	define __cdecl
#	define __export				__attribute__((visibility("default")))
	typedef int64_t				__int64;
	typedef uint64_t			__uint64;
	typedef uint32_t			PROPID;
#else
#	define __stdcall
#	define __fastcall
#	define __cdecl
#   define __export
#endif

// -------------------------------------------------------------------------- //
// --> Keyword

#if !defined(__BEGIN_DECLS)
#	if defined(__cplusplus)
#		define __BEGIN_DECLS	extern "C" {
#		define __END_DECLS		}
#	else
#		define __BEGIN_DECLS
#		define __END_DECLS
#	endif
#endif

// -------------------------------------------------------------------------- //
// --> Type Definitions

typedef int8_t				int8;
typedef int16_t				int16;
typedef int32_t				int32;
typedef int64_t				int64;
typedef uint8_t				uint8;
typedef uint16_t			uint16;
typedef uint32_t			uint32;
typedef uint64_t			uint64;
typedef intptr_t			intp;
typedef uintptr_t			uintp;

typedef int8				INT8;
typedef uint8				UINT8;
typedef int16				INT16;
typedef uint16				UINT16;
typedef int32				INT32;
typedef uint32				UINT32;
typedef int64				INT64;
typedef uint64				UINT64;

typedef uintp				UINTP;
typedef intp				INTP;

typedef int32				size32;
typedef uint32				usize32;
typedef size32				SIZE32;
typedef usize32				USIZE32;

static_assert(sizeof(DWORD) == 4, "DWORD has no 4 bytes.");
static_assert(sizeof(int8) == 1, "int8 has no 1 byte");
static_assert(sizeof(uint8) == 1, "uint8 has no 1 byte");
static_assert(sizeof(int16) == 2, "int16 has no 2 byte");
static_assert(sizeof(uint16) == 2, "uint16 has no 2 byte");
static_assert(sizeof(int32) == 4, "int32 has no 4 byte");
static_assert(sizeof(uint32) == 4, "uint32 has no 4 byte");
static_assert(sizeof(int64) == 8, "int64 has no 8 byte");
static_assert(sizeof(uint64) == 8, "uint64 has no 8 byte");
static_assert(sizeof(intp) == sizeof(void*), "intp's size not equal to void *");
static_assert(sizeof(uintp) == sizeof(void*), "uintp's size not equal to void *");

// -------------------------------------------------------------------------- //
// --> Macros

#ifdef X_CC_VC
#define __X(x) L ## x
#define __Xc(x) L ## x
#else
#define __X(x) ((unsigned short *)(u ## x))
#define OLESTR(x) __X(x)
#define __Xc(x) ((unsigned short)(u ## x))
#endif

#ifndef MAX_PATH
#define MAX_PATH		260
#endif

#ifndef _MAX_PATH
#define _MAX_PATH		MAX_PATH
#define _MAX_FNAME		256
#define _MAX_DRIVE		3
#define _MAX_DIR		256
#define _MAX_EXT		256
#endif

// -------------------------------------------------------------------------- //
// --> BFC Namespace

#if defined(__cplusplus)
#define _BFC					bfc::
#define _BFC_BEGIN				namespace bfc {
#define _BFC_END				};
#define _USING_BFC				using namespace bfc;
#else
#define _BFC
#define _BFC_BEGIN
#define _BFC_END
#define _USING_BFC
#endif

// -------------------------------------------------------------------------- //

#endif// __PRE_DEF_H__
