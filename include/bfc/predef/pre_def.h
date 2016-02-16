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
#include <stdexcpt.h>
#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif
#include "pre_platform.h"
#if defined(X_OS_WINDOWS)
#include <windows.h>
#else
#endif

// -------------------------------------------------------------------------- //
// --> Keyword
#undef far
#undef near
#define far
#define near
#undef FAR
#undef NEAR
#define FAR                 far
#define NEAR                near

#ifndef CDECL
#define CDECL	__cdecl
#endif

#ifndef PASCAL
#define PASCAL	__stdcall
#endif

#ifndef CONST
#define CONST               const
#endif

#ifndef interface
#define interface struct
#endif

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C    extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef INT32 HRESULT;
#endif // !_HRESULT_DEFINED

#ifndef STDAPI
#define STDAPI				EXTERN_C __export HRESULT __stdcall
#define STDAPI_(type)       EXTERN_C __export type __stdcall

#define STDAPICALLTYPE                  __stdcall
#define STDAPIVCALLTYPE                 __cdecl
#endif

#ifndef EXPORTAPI
#define EXPORTAPI			EXTERN_C __export HRESULT __stdcall
#define EXPORTAPI_(type)	EXTERN_C __export type __stdcall
#endif

#ifndef STDMETHOD
#define STDMETHODCALLTYPE		__stdcall
#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method) virtual type STDMETHODCALLTYPE method
#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE
#endif

#ifndef PURE
#define PURE					= 0
#endif

#ifndef STDPROC
#define STDPROC					virtual HRESULT __stdcall
#define STDPROC_(Type)			virtual Type __stdcall
#endif

#ifndef APIENTRY
#define APIENTRY				__stdcall
#endif

#ifndef WINAPI
#define WINAPI					__stdcall
#endif

#ifndef CALLBACK
#define CALLBACK				__stdcall
#endif

#ifndef DECLARE_HANDLE
	typedef void* HANDLE;
	#define DECLARE_HANDLE(name) struct __handle_##name##__ { int unused; }; typedef struct name##__ *name
	typedef HANDLE* PHANDLE;
#endif

#if !defined(__HMODULE)
#define __HMODULE
	DECLARE_HANDLE(HINSTANCE);
	typedef HINSTANCE HMODULE;	/* HMODULEs can be used in place of HINSTANCEs */
#endif

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
// --> Type Define
#undef TRUE
#undef FALSE
#define TRUE				1
#define FALSE				0

#ifndef BASETYPES
#define BASETYPES
typedef long LONG;
typedef LONG *PLONG;
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef short SHORT;
typedef SHORT *PSHORT;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef char CHAR;
typedef CHAR *PCHAR;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  // !BASETYPES

#ifndef VOID
#define VOID void
#endif

typedef void* PVOID;
typedef unsigned short VARTYPE;
typedef short VARIANT_BOOL;
typedef long SCODE;

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
typedef UINT32				DWORD;
typedef int32				BOOL;
typedef unsigned char		BYTE;
typedef uint16				WORD;
typedef float				FLOAT;
typedef double				DOUBLE;
typedef FLOAT				*PFLOAT;
typedef BOOL near			*PBOOL;
typedef BOOL far			*LPBOOL;
typedef BYTE near			*PBYTE;
typedef BYTE far			*LPBYTE;
typedef int near			*PINT;
typedef int far				*LPINT;
typedef WORD near			*PWORD;
typedef WORD far			*LPWORD;
typedef long far			*LPLONG;
typedef DWORD near			*PDWORD;
typedef DWORD far			*LPDWORD;
typedef void far			*LPVOID;
typedef CONST void far		*LPCVOID;

typedef int					INT;
typedef unsigned int		UINT;
typedef unsigned int		*PUINT;
typedef long long			LONGLONG;
typedef unsigned long long	ULONGLONG;
typedef DWORD				LCID;
typedef DWORD				LCTYPE;

typedef uintp				UINTP;
typedef intp				INTP;

typedef int32				size32;
typedef uint32				usize32;
typedef size32				SIZE32;
typedef usize32				USIZE32;

typedef DWORD   COLORREF;
typedef DWORD*	LPCOLORREF;

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

typedef unsigned short WCHAR;

typedef WCHAR*	PWCHAR;
typedef WCHAR*	LPWCH, *PWCH;
typedef WCHAR*	LPWSTR, *PWSTR;
typedef CONST WCHAR* LPCWCHAR, *PCWCHAR;
typedef CONST WCHAR* LPCWCH, *PCWCH;
typedef CONST WCHAR* LPCWSTR, *PCWSTR;

typedef LPCWSTR LPCOLESTR;
typedef LPWSTR LPOLESTR;

typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;

typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

#ifndef VARIANT_TRUE
#define VARIANT_TRUE	((VARIANT_BOOL)0xffff)
#define VARIANT_FALSE	((VARIANT_BOOL)0)
#endif


// --> Neutral ANSI/UNICODE types and macros
#ifdef  UNICODE

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE, *PTBYTE;
#endif

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote

#else   /* UNICODE */

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE, *PTBYTE ;
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR;
typedef LPCSTR LPCTSTR;
#define __TEXT(quote) quote

#endif /* UNICODE */


// -------------------------------------------------------------------------- //
// --> Macros

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKEINT32(a, b)     ((INT32)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#ifndef RGB
#define RGB(r,g,b)		((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

#ifndef LISet32
#define LISet32(li, v)		((li).HighPart = (v) < 0 ? -1 : 0, (li).LowPart = (v))
#define ULISet32(li, v)		((li).HighPart = 0, (li).LowPart = (v))
#endif

#ifdef X_CC_VC
#define __X(x) L ## x
#define __Xc(x) L ## x
#else
#define __X(x) ((unsigned short *)(u ## x))
#define OLESTR(x) __X(x)
#define __Xc(x) ((unsigned short)(u ## x))
#endif

#ifndef	countof
#  define countof(array)						(sizeof(array)/sizeof(array[0]))
#endif

#ifndef _countof
#  define _countof(array)						(sizeof(array)/sizeof(array[0]))
#endif

#ifndef _offsetof
#	if defined(X_CC_GCC)
#		define _offsetof(coclass, member)	( (size_t)&((coclass*)64)->member - 64 )
#	else
#		define _offsetof(coclass, member)	( (size_t)&((coclass*)0)->member )
#	endif
#endif

#ifndef parent_class_ptr
#define parent_class_ptr(ParentClass, member)	\
	( (ParentClass*)((const char*)(this) - _offsetof(ParentClass, member)) )
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
