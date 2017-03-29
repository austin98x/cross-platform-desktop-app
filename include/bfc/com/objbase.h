/* -------------------------------------------------------------------------
//	File name		：	objbase.h
//	Author 			：	Austin
//	Create Time		：	2016-2-24 09:57:11
//	Description 	：	Declare some API functions for Linux platform
//
// -----------------------------------------------------------------------*/

#ifndef __OBJBASE_H__
#define __OBJBASE_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------
// --> CoTaskMem

STDAPI _XCoGetMalloc(UINT uMemContext, LPMALLOC FAR* ppv);
STDAPI _XCoRegisterMallocSpy(LPMALLOCSPY pMallocSpy);
STDAPI _XCoRevokeMallocSpy(void);
STDAPI_(LPVOID) _XCoTaskMemAlloc(UINT cb);
STDAPI_(LPVOID) _XCoTaskMemRealloc(LPVOID pv, UINT cb);
STDAPI_(void) _XCoTaskMemFree(LPVOID pv);
STDAPI_(UINT) _XCoTaskMemSize(LPVOID pv);
#define CoGetMalloc(uMemContext, ppv)	_XCoGetMalloc(uMemContext, ppv)
#define CoRegisterMallocSpy(pMallocSpy)	_XCoRegisterMallocSpy(pMallocSpy)
#define CoRevokeMallocSpy()				_XCoRevokeMallocSpy()
#define CoTaskMemAlloc(cb)				_XCoTaskMemAlloc(cb)
#define CoTaskMemRealloc(pv, cb)		_XCoTaskMemRealloc(pv, cb)
#define CoTaskMemFree(pv)				_XCoTaskMemFree(pv)
#define CoTaskMemSize(pv)				_XCoTaskMemSize(pv)

// -------------------------------------------------------------------------
// --> guid/progid helpers

STDAPI _XCoCreateGuid(GUID FAR *pguid);
STDAPI _XStringFromCLSID(REFCLSID clsid, LPOLESTR FAR* ppsz);
STDAPI _XCLSIDFromString(LPCOLESTR psz, LPCLSID pclsid);
STDAPI _XStringFromIID(REFIID clsid, LPOLESTR FAR* ppsz);
STDAPI _XIIDFromString(LPCOLESTR lpsz, LPIID lpiid);
STDAPI _XProgIDFromCLSID(REFCLSID clsid, LPOLESTR FAR* ppszProgID);
STDAPI _XCLSIDFromProgID(LPCOLESTR szProgID, LPCLSID pclsid);
STDAPI_(int) _XStringFromGUID2(REFGUID guid, LPOLESTR psz, int cchMax);
#define CoCreateGuid(pguid)				_XCoCreateGuid(pguid)
#define StringFromCLSID(clsid, ppsz)	_XStringFromCLSID(clsid, ppsz)
#define CLSIDFromString(psz, pclsid)	_XCLSIDFromString(psz, pclsid)
#define StringFromIID(iid, ppsz)		StringFromCLSID(iid, ppsz)
#define IIDFromString(psz, piid)		CLSIDFromString(psz, piid)
#define ProgIDFromCLSID(clsid, ppsz)	_XProgIDFromCLSID(clsid, ppsz)
#define CLSIDFromProgID(psz, pclsid)	_XCLSIDFromProgID(psz, pclsid)
#define StringFromGUID2(guid, psz, cch)	_XStringFromGUID2(guid, psz, cch)

// -------------------------------------------------------------------------

#endif /* __OBJBASE_H__ */
