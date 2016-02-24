/* -------------------------------------------------------------------------
//	File name		：	guid.h
//	Author 			：	Austin
//	Create Time		：	2016-2-24 10:13:14
//	Description 	：	Define GUID for Linux platform
//
// -----------------------------------------------------------------------*/
#ifndef __GUID_H__
#define __GUID_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

#ifndef GUID_DEFINED
#define GUID_DEFINED
#define __IID_DEFINED__
#define CLSID_DEFINED

#pragma pack(1)
typedef struct _GUID
{
	uint32	Data1;
	uint16	Data2;
	uint16	Data3;
	uint8	Data4[8];
} GUID;
#pragma pack()

#endif

// -------------------------------------------------------------------------

#ifndef DECLARE_GUID
#define DECLARE_GUID(var)		EXTERN_C const GUID var;
#endif

#ifndef DECLARE_CLSID
#define DECLARE_CLSID(Com)		DECLARE_GUID(CLSID_##Com)
#endif

#ifndef DECLARE_IID
#define DECLARE_IID(Intf)		DECLARE_GUID(IID_##Intf)
#endif

// -------------------------------------------------------------------------

#define IMPLEMENT_GUID(var, sz, x, s1, s2, c1, c2, c3, c4, c5, c6, c7, c8)	\
	EXTERN_C const GUID var													\
			= {x, s1, s2, { c1, c2, c3, c4, c5, c6, c7, c8 }};

#define IMPLEMENT_CLSID(Com, sz, x, s1, s2, c1, c2, c3, c4, c5, c6, c7, c8)	\
	IMPLEMENT_GUID(CLSID_##Com, sz,											\
			x, s1, s2, c1, c2, c3, c4, c5, c6, c7, c8)

#define IMPLEMENT_IID(Intf, sz, x, s1, s2, c1, c2, c3, c4, c5, c6, c7, c8)	\
	IMPLEMENT_GUID(IID_##Intf, sz,											\
			x, s1, s2, c1, c2, c3, c4, c5, c6, c7, c8);

// -------------------------------------------------------------------------

typedef GUID IID;
typedef GUID CLSID;

#ifdef X_CC_GCC
typedef const IID& REFFMTID;
#endif
#if defined(__cplusplus)
#ifndef REFGUID
#define REFGUID		const GUID&
#endif // !REFGUID
#ifndef REFIID
#define REFIID		const IID&
#endif // !REFIID
#ifndef REFCLSID
#define REFCLSID	const CLSID&
#endif // !REFCLSID

#else 

#ifndef REFGUID
#define REFGUID		const GUID* const
#endif // !REFGUID
#ifndef REFIID
#define REFIID		const IID* const
#endif // !REFIID
#ifndef REFCLSID
#define REFCLSID	const CLSID* const
#endif // !REFCLSID

#endif

// -------------------------------------------------------------------------

#ifndef	__iid
#define __iid(Interface)	IID_ ## Interface
#endif

#ifndef	__clsid
#define __clsid(ComClass)	CLSID_ ## ComClass
#endif

#ifndef X_OS_WINDOWS
EXTERN_C const GUID CLSID_NULL;
EXTERN_C const GUID GUID_NULL;
EXTERN_C const GUID IID_NULL;
#endif

// -------------------------------------------------------------------------

#endif /* __GUID_H__ */

