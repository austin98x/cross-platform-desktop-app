// -------------------------------------------------------------------------- //
//	File name		£º	pre_unixdef.h
//	Author 			£º	Austin
//	Create Time		£º	2016-2-17 11:38:45
//	Description 	£º	Predefined macros for UNIX platform
//
// -------------------------------------------------------------------------- //

#ifndef __PRE_UNIXDEF_H__
#define __PRE_UNIXDEF_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------- //
// --> Type Definitions

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef int INT;
#endif

typedef void* PVOID;
typedef unsigned short VARTYPE;
typedef short VARIANT_BOOL;
typedef long SCODE;

#define MAX_PATH          260

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near
#undef pascal
#define far
#define near
#define pascal __stdcall

#undef FAR
#undef  NEAR
#define FAR                 far
#define NEAR                near
#ifndef CONST
#define CONST               const
#endif

#ifndef CDECL
#define CDECL _cdecl
#endif

#ifndef PASCAL
#define PASCAL __stdcall
#endif

#ifndef CALLBACK
#define CALLBACK    __stdcall
#endif

#ifndef WINAPI
#define WINAPI      __stdcall
#endif

#ifndef APIENTRY
#define APIENTRY    __stdcall
#endif


typedef unsigned int        DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef double              DOUBLE;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef long long           LONGLONG;
typedef unsigned long long  ULONGLONG;
typedef DWORD               LCID;
typedef DWORD               LCTYPE;

typedef unsigned short WCHAR;
typedef WCHAR* PWCHAR;
typedef WCHAR* LPWCH, *PWCH;
typedef WCHAR* LPWSTR, *PWSTR;
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

// --> Neutral ANSI/UNICODE types and macros
#ifdef  UNICODE

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE, *PTBYTE;
#endif /* !_TCHAR_DEFINED */

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;
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

#ifndef VARIANT_TRUE
#define VARIANT_TRUE    ((VARIANT_BOOL)0xffff)
#define VARIANT_FALSE   ((VARIANT_BOOL)0)
#endif

typedef DWORD   COLORREF;
typedef DWORD   *LPCOLORREF;

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKEINT32(a, b)     ((INT32)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#ifndef RGB
#define RGB(r,g,b)		((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

typedef void* HANDLE;
#define DECLARE_HANDLE(name) struct __handle_##name##__ { int unused; }; typedef struct name##__ *name
typedef HANDLE* PHANDLE;
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;

typedef struct tagRECT
{
	LONG    left;
	LONG    top;
	LONG    right;
	LONG    bottom;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;

typedef const RECT FAR* LPCRECT;

typedef struct _RECTL
{
	LONG    left;
	LONG    top;
	LONG    right;
	LONG    bottom;
} RECTL, *PRECTL, *LPRECTL;

typedef const RECTL FAR* LPCRECTL;

typedef struct tagPOINT
{
	LONG  x;
	LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

typedef struct _POINTL
{
	LONG  x;
	LONG  y;
} POINTL, *PPOINTL;

typedef struct tagSIZE
{
	LONG        cx;
	LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

typedef SIZE               SIZEL;
typedef SIZE               *PSIZEL, *LPSIZEL;

typedef struct tagPOINTS
{
	SHORT   y;
	SHORT   x;
} POINTS, *PPOINTS, *LPPOINTS;

typedef union _LARGE_INTEGER
{
	struct
	{
		int32_t LowPart;
		int32_t HighPart;
	};
	int64_t QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER; 

typedef union _ULARGE_INTEGER
{
	struct
	{
		uint32_t LowPart;
		uint32_t HighPart;
	};
	uint64_t QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef union tagCY
{
	struct
	{
		int32_t Lo;
		int32_t Hi;
	};
	int64_t int64;
} CY;
typedef CY* LPCY;

typedef struct tagDEC
{
	USHORT wReserved;
	union
	{
		struct
		{
			BYTE scale;
			BYTE sign;
		};
		USHORT signscale;
	};
	uint32_t Hi32;
	union
	{
		struct
		{
			uint32_t Lo32;
			uint32_t Mid32;
		};
		uint64_t Lo64;
	};
} DECIMAL;

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef int HRESULT;
#endif // !_HRESULT_DEFINED

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

#define STDMETHODCALLTYPE       __stdcall
#define STDMETHODVCALLTYPE      __cdecl

#define STDAPICALLTYPE          __stdcall
#define STDAPIVCALLTYPE         __cdecl

#define STDAPI                  EXTERN_C HRESULT __stdcall
#define STDAPI_(type)           EXTERN_C type __stdcall

#define STDPROC					virtual HRESULT __stdcall
#define STDPROC_(Type)			virtual Type __stdcall

#define EXPORTAPI				EXTERN_C __export HRESULT __stdcall
#define EXPORTAPI_(type)		EXTERN_C __export type __stdcall

#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE

#define STDOVERRIDEMETHODIMP        __override STDMETHODIMP
#define STDOVERRIDEMETHODIMP_(type) __override STDMETHODIMP_(type)

#define IFACEMETHODIMP          __override STDMETHODIMP
#define IFACEMETHODIMP_(type)   __override STDMETHODIMP_(type)

#ifndef interface
#define interface struct
#endif

#define STDMETHOD(method)        virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method)  virtual type STDMETHODCALLTYPE method
#define STDMETHODV(method)       virtual HRESULT STDMETHODVCALLTYPE method
#define STDMETHODV_(type,method) virtual type STDMETHODVCALLTYPE method

#define IFACEMETHOD(method)         __override STDMETHOD(method)
#define IFACEMETHOD_(type,method)   __override STDMETHOD_(type,method)
#define IFACEMETHODV(method)        __override STDMETHODV(method)
#define IFACEMETHODV_(type,method)  __override STDMETHODV_(type,method)

DECLARE_HANDLE(HGLOBAL);

#define PURE                    = 0
#define THIS_
#define THIS                    void
#define __RPC_FAR
#define __RPC_STUB              __stdcall

#define AllocMemory(cb)					malloc(cb)
#define ReallocMemory(pv, cb)			realloc(pv, cb)
#define FreeMemory(pv)					free(pv)
#define FillMemory(p, len, c)			memset(p, c, len)
#define ZeroMemory(p, len)				memset(p, 0, len)
#define CopyMemory(dst, src, len)		memcpy(dst, src, len)
#define MoveMemory(dst, src, len)		memmove(dst, src, len)
#define ZeroStruct(buf)					ZeroMemory(&(buf), sizeof(buf))

#define TokenVal(p, type)				(*((type*&)(p))++)
#define TokenSize(p, size)				(((const char*&)(p)) += (size))

// -------------------------------------------------------------------------- //

#endif// __PRE_UNIXDEF_H__
