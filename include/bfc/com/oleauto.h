/* -------------------------------------------------------------------------
//	File name		：	oleauto.h
//	Author 			：	Austin
//	Create Time		：	2016-2-24 10:44:25
//	Description 	：	Define OLE API for Linux platform
//
// -----------------------------------------------------------------------*/
#ifndef __OLEAUTO_H__
#define __OLEAUTO_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

#ifndef WINOLEAUTAPI
#define WINOLEAUTAPI        EXTERN_C __export HRESULT STDAPICALLTYPE
#define WINOLEAUTAPI_(type) EXTERN_C __export type STDAPICALLTYPE
#endif

#ifndef _LCID_DEFINED
#define _LCID_DEFINED
typedef DWORD LCID;
#endif

typedef unsigned _BSTR;

/*---------------------------------------------------------------------*/
/*                           MISC API                                  */
/*---------------------------------------------------------------------*/

// Declare variant access functions.

#if __STDC__ || defined(NONAMELESSUNION)
#define V_UNION(X, Y)   ((X)->n1.n2.n3.Y)
#define V_VT(X)         ((X)->n1.n2.vt)
#define V_RECORDINFO(X) ((X)->n1.n2.n3.brecVal.pRecInfo)
#define V_RECORD(X)     ((X)->n1.n2.n3.brecVal.pvRecord)
#define V_DECIMAL(X)    ((X)->n1.decVal)
#else
#define V_UNION(X, Y)   ((X)->Y)
#define V_VT(X)         ((X)->vt)
#define V_RECORDINFO(X) ((X)->pRecInfo)
#define V_RECORD(X)     ((X)->pvRecord)
#define V_DECIMAL(X)    ((X)->decVal)
#endif

/* Variant access macros
 */
#define V_ISBYREF(X)     (V_VT(X)&VT_BYREF)
#define V_ISARRAY(X)     (V_VT(X)&VT_ARRAY)
#define V_ISVECTOR(X)    (V_VT(X)&VT_VECTOR)
#define V_NONE(X)        V_I2(X)

#define V_UI1(X)         V_UNION(X, bVal)
#define V_UI1REF(X)      V_UNION(X, pbVal)
#define V_I2(X)          V_UNION(X, iVal)
#define V_I2REF(X)       V_UNION(X, piVal)
#define V_I4(X)          V_UNION(X, lVal)
#define V_I4REF(X)       V_UNION(X, plVal)
#define V_I8(X)          V_UNION(X, llVal)
#define V_I8REF(X)       V_UNION(X, pllVal)
#define V_R4(X)          V_UNION(X, fltVal)
#define V_R4REF(X)       V_UNION(X, pfltVal)
#define V_R8(X)          V_UNION(X, dblVal)
#define V_R8REF(X)       V_UNION(X, pdblVal)
#define V_I1(X)          V_UNION(X, cVal)
#define V_I1REF(X)       V_UNION(X, pcVal)
#define V_UI2(X)         V_UNION(X, uiVal)
#define V_UI2REF(X)      V_UNION(X, puiVal)
#define V_UI4(X)         V_UNION(X, ulVal)
#define V_UI4REF(X)      V_UNION(X, pulVal)
#define V_UI8(X)         V_UNION(X, ullVal)
#define V_UI8REF(X)      V_UNION(X, pullVal)
#define V_INT(X)         V_UNION(X, intVal)
#define V_INTREF(X)      V_UNION(X, pintVal)
#define V_UINT(X)        V_UNION(X, uintVal)
#define V_UINTREF(X)     V_UNION(X, puintVal)

#if defined( __x86_64__) || defined(__ia64) || defined(__amd64__)
#define V_INT_PTR(X)        V_UNION(X, llVal)
#define V_UINT_PTR(X)       V_UNION(X, ullVal)
#define V_INT_PTRREF(X)     V_UNION(X, pllVal)
#define V_UINT_PTRREF(X)    V_UNION(X, pullVal)
#else
#define V_INT_PTR(X)        V_UNION(X, lVal)
#define V_UINT_PTR(X)       V_UNION(X, ulVal)
#define V_INT_PTRREF(X)     V_UNION(X, plVal)
#define V_UINT_PTRREF(X)    V_UNION(X, pulVal)
#endif

#define V_CY(X)          V_UNION(X, cyVal)
#define V_CYREF(X)       V_UNION(X, pcyVal)
#define V_DATE(X)        V_UNION(X, date)
#define V_DATEREF(X)     V_UNION(X, pdate)
#define V_BSTR(X)        V_UNION(X, bstrVal)
#define V_BSTRREF(X)     V_UNION(X, pbstrVal)
#define V_DISPATCH(X)    V_UNION(X, pdispVal)
#define V_DISPATCHREF(X) V_UNION(X, ppdispVal)
#define V_ERROR(X)       V_UNION(X, scode)
#define V_ERRORREF(X)    V_UNION(X, pscode)
#define V_BOOL(X)        V_UNION(X, boolVal)
#define V_BOOLREF(X)     V_UNION(X, pboolVal)
#define V_UNKNOWN(X)     V_UNION(X, punkVal)
#define V_UNKNOWNREF(X)  V_UNION(X, ppunkVal)
#define V_VARIANTREF(X)  V_UNION(X, pvarVal)
#define V_ARRAY(X)       V_UNION(X, parray)
#define V_ARRAYREF(X)    V_UNION(X, pparray)
#define V_BYREF(X)       V_UNION(X, byref)

#define V_DECIMALREF(X)  V_UNION(X, pdecVal)

/*---------------------------------------------------------------------*/
/*                            BSTR API                                 */
/*---------------------------------------------------------------------*/
#define USES_KSKERN_01
#if defined(USES_KSKERN_01)

WINOLEAUTAPI_(BSTR) _XSysAllocString(const OLECHAR* psz);
WINOLEAUTAPI_(BSTR) _XSysAllocStringLen(const OLECHAR* psz, UINT cch);
WINOLEAUTAPI_(INT)  _XSysReAllocString(BSTR* pbstr, const OLECHAR* psz);
WINOLEAUTAPI_(INT)  _XSysReAllocStringLen(BSTR* pbstr, const OLECHAR* psz, UINT cch);
WINOLEAUTAPI_(void) _XSysFreeString(BSTR bstr);
WINOLEAUTAPI_(UINT) _XSysStringLen(BSTR bstr);
WINOLEAUTAPI_(UINT) _XSysStringByteLen(BSTR bstr);
WINOLEAUTAPI_(BSTR) _XSysAllocStringByteLen(LPCSTR psz, UINT cch);

#if !defined(__cplusplus)
#define SysAllocString(psz)													\
			( (BSTR) _XSysAllocString(psz) )
#define SysAllocStringLen(psz, cch)											\
			( (BSTR) _XSysAllocStringLen(psz, cch) )
#else
#define SysAllocString(psz)		_XSysAllocString(psz)
#define SysAllocStringLen(psz, cch)	_XSysAllocStringLen(psz, cch)
#endif

#define SysReAllocString(pbstr, psz)			_XSysReAllocString(pbstr, psz)
#define SysReAllocStringLen(pbstr, psz, cch)	_XSysReAllocStringLen(pbstr, psz, cch)
#define SysFreeString(bstr)						_XSysFreeString(bstr)
#define SysStringLen(bstr)						_XSysStringLen(bstr)
#define SysStringByteLen(bstr)					_XSysStringByteLen(bstr)
#define SysAllocStringByteLen(PSZ, cch)			_XSysAllocStringByteLen(PSZ, cch)

#else

WINOLEAUTAPI_(_BSTR) _MSysAllocString(const OLECHAR* psz);
WINOLEAUTAPI_(_BSTR) _MSysAllocStringLen(const OLECHAR* psz, UINT cch);
WINOLEAUTAPI_(INT)  _MSysReAllocString(BSTR* pbstr, const OLECHAR* psz);
WINOLEAUTAPI_(INT)  _MSysReAllocStringLen(BSTR* pbstr, const OLECHAR* psz, UINT cch);
WINOLEAUTAPI_(void) _MSysFreeString(BSTR bstr);
WINOLEAUTAPI_(UINT) _MSysStringLen(BSTR bstr);
WINOLEAUTAPI_(_BSTR) _MSysAllocStringByteLen(LPCSTR psz, UINT cch);

#if !defined(__cplusplus)
#define SysAllocString(psz)						( (BSTR) _MSysAllocString(psz) )
#define SysAllocStringLen(psz, cch)				( (BSTR) _MSysAllocStringLen(psz, cch) )
#else
inline STDMETHODIMP_(BSTR) SysAllocString(const OLECHAR* psz)
{
	return (BSTR)_MSysAllocString(psz);
}

inline STDMETHODIMP_(BSTR) SysAllocStringLen(const OLECHAR*psz, UINT cch)
{
	return (BSTR)_MSysAllocStringLen(psz, cch);
}
#endif

#define SysReAllocString(pbstr, psz)			_MSysReAllocString(pbstr, psz)
#define SysReAllocStringLen(pbstr, psz, cch)	_MSysReAllocStringLen(pbstr, psz, cch)
#define SysFreeString(bstr)						_MSysFreeString(bstr)
#define SysStringLen(bstr)						_MSysStringLen(bstr)
#define SysAllocStringByteLen(PSZ, cch)			_MSysAllocStringByteLen(PSZ, cch)

#endif

/*---------------------------------------------------------------------*/
/*                           VARIANT API                               */
/*---------------------------------------------------------------------*/

#define VARCMP_LT	0
#define VARCMP_EQ	1
#define VARCMP_GT	2
#define VARCMP_NULL	3

#if !defined(__cplusplus)
WINOLEAUTAPI_(void) _MVariantInit(VARIANTARG* pvarg);
#else
inline
STDMETHODIMP_(void) _MVariantInit(VARIANTARG* pvarg)
{
	V_VT(pvarg) = VT_EMPTY;
}
#endif

WINOLEAUTAPI _MVariantClear(VARIANTARG * pvarg);
WINOLEAUTAPI _MVariantCopy(VARIANTARG * pvargDest, const VARIANTARG * pvargSrc);
WINOLEAUTAPI _MVariantCopyInd(VARIANT * pvarDest, VARIANTARG * pvargSrc);
WINOLEAUTAPI _MVariantChangeType(VARIANTARG * pvargDest,
							     VARIANTARG * pvarSrc, USHORT wFlags, VARTYPE vt);
WINOLEAUTAPI _MVariantChangeTypeEx(VARIANTARG * pvargDest,
								   VARIANTARG * pvarSrc, LCID lcid, USHORT wFlags, VARTYPE vt);
WINOLEAUTAPI _MVariantCompare(LPVARIANT pvarLeft, LPVARIANT pvarRight, LCID lcid, ULONG dwFlags);

#define VariantInit			_MVariantInit
#define VariantClear		_MVariantClear
#define VariantCopy			_MVariantCopy
#define VariantCopyInd		_MVariantCopyInd
#define VariantChangeType	_MVariantChangeType
#define VariantChangeTypeEx	_MVariantChangeTypeEx
#define VarCmp				_MVariantCompare

#define VARIANT_NOVALUEPROP 0x01

/*---------------------------------------------------------------------*/
/*                          SafeArray API                              */
/*---------------------------------------------------------------------*/
typedef SAFEARRAY* _SAFEARRAY_PTR;

WINOLEAUTAPI _MSafeArrayAccessData(SAFEARRAY *psa, void ** ppvData);
WINOLEAUTAPI _MSafeArrayAllocData(SAFEARRAY * psa);
WINOLEAUTAPI _MSafeArrayAllocDescriptor(UINT32 cDims, SAFEARRAY ** ppsaOut);
WINOLEAUTAPI _MSafeArrayCopy(SAFEARRAY * psa, SAFEARRAY ** ppsaOut);
WINOLEAUTAPI _MSafeArrayCopyData(SAFEARRAY *psaSource, SAFEARRAY *psaTarget);
WINOLEAUTAPI_(_SAFEARRAY_PTR) _MSafeArrayCreate(VARTYPE vt, UINT32 cDims, SAFEARRAYBOUND* rgsabound);
WINOLEAUTAPI_(_SAFEARRAY_PTR) _MSafeArrayCreateVector(VARTYPE vt, INT32 lLbound, UINT32 cElements);
WINOLEAUTAPI _MSafeArrayDestroy(SAFEARRAY * psa);
WINOLEAUTAPI _MSafeArrayDestroyDescriptor(SAFEARRAY * psa);
WINOLEAUTAPI _MSafeArrayDestroyData(SAFEARRAY * psa);
WINOLEAUTAPI_(UINT32) _MSafeArrayGetDim(SAFEARRAY * psa);
WINOLEAUTAPI_(UINT32) _MSafeArrayGetElemsize(SAFEARRAY * psa);
WINOLEAUTAPI _MSafeArrayGetElement(SAFEARRAY * psa, INT32 * rgIndices, void * pv);
WINOLEAUTAPI _MSafeArrayGetUBound(SAFEARRAY * psa, UINT32 nDim, INT32 * plUbound);
WINOLEAUTAPI _MSafeArrayGetLBound(SAFEARRAY * psa, UINT32 nDim, INT32 * plLbound);
WINOLEAUTAPI _MSafeArrayLock(SAFEARRAY * psa);
WINOLEAUTAPI _MSafeArrayUnlock(SAFEARRAY * psa);
WINOLEAUTAPI _MSafeArrayPutElement(SAFEARRAY * psa, INT32 * rgIndices, void * pv);
WINOLEAUTAPI _MSafeArrayPtrOfIndex(SAFEARRAY * psa, INT32 * rgIndices, void ** ppvData);
WINOLEAUTAPI _MSafeArrayRedim(SAFEARRAY * psa, SAFEARRAYBOUND * psaboundNew);
WINOLEAUTAPI _MSafeArrayUnaccessData(SAFEARRAY * psa);

WINOLEAUTAPI _MSafeArrayGetVartype(SAFEARRAY * psa, VARTYPE * pvt);

#define SafeArrayAccessData			_MSafeArrayAccessData
#define SafeArrayAllocData			_MSafeArrayAllocData
#define SafeArrayAllocDescriptor	_MSafeArrayAllocDescriptor
#define SafeArrayCopy				_MSafeArrayCopy
#define SafeArrayCopyData			_MSafeArrayCopyData
#define SafeArrayDestroy			_MSafeArrayDestroy
#define SafeArrayDestroyDescriptor	_MSafeArrayDestroyDescriptor
#define SafeArrayDestroyData		_MSafeArrayDestroyData
#define SafeArrayGetDim				_MSafeArrayGetDim
#define SafeArrayGetElemsize		_MSafeArrayGetElemsize
#define SafeArrayGetElement			_MSafeArrayGetElement
#define SafeArrayGetUBound			_MSafeArrayGetUBound
#define SafeArrayGetLBound			_MSafeArrayGetLBound
#define SafeArrayLock				_MSafeArrayLock
#define SafeArrayUnlock				_MSafeArrayUnlock
#define SafeArrayPutElement			_MSafeArrayPutElement
#define SafeArrayPtrOfIndex			_MSafeArrayPtrOfIndex
#define SafeArrayRedim				_MSafeArrayRedim
#define SafeArrayUnaccessData		_MSafeArrayUnaccessData
#define SafeArrayCreate(vt, cDims, rgsabound)								\
	( (SAFEARRAY*)_MSafeArrayCreate(vt, cDims, rgsabound) )
#define SafeArrayCreateVector(vt, lLbound, cElements)						\
	( (SAFEARRAY*)_MSafeArrayCreateVector(vt, lLbound, cElements))
#define SafeArrayGetVartype			_MSafeArrayGetVartype

/*
WINOLEAUTAPI _MSafeArrayAllocDescriptorEx(VARTYPE vt, UINT cDims, SAFEARRAY ** ppsaOut);
WINOLEAUTAPI_(SAFEARRAY *) _MSafeArrayCreateEx(VARTYPE vt, UINT cDims, SAFEARRAYBOUND * rgsabound, PVOID pvExtra);
WINOLEAUTAPI _MSafeArraySetRecordInfo(SAFEARRAY * psa, IRecordInfo * prinfo);
WINOLEAUTAPI _MSafeArrayGetRecordInfo(SAFEARRAY * psa, IRecordInfo ** prinfo);
WINOLEAUTAPI _MSafeArraySetIID(SAFEARRAY * psa, REFGUID guid);
WINOLEAUTAPI _MSafeArrayGetIID(SAFEARRAY * psa, GUID * pguid);
WINOLEAUTAPI_(SAFEARRAY *) _MSafeArrayCreateVector(VARTYPE vt, LONG lLbound, ULONG cElements);
WINOLEAUTAPI_(SAFEARRAY *) _MSafeArrayCreateVectorEx(VARTYPE vt, LONG lLbound, ULONG cElements, PVOID pvExtra);
*/

/*---------------------------------------------------------------------*/
/*                           ErrorInfo API                             */
/*---------------------------------------------------------------------*/

WINOLEAUTAPI _XCreateErrorInfo(ICreateErrorInfo** pperrinfo);
WINOLEAUTAPI _XSetErrorInfo(UINT nReserved, IErrorInfo*  perrinfo);
WINOLEAUTAPI _XGetErrorInfo(UINT nReserved, IErrorInfo** pperrinfo);

#define CreateErrorInfo(pperrinfo)			_XCreateErrorInfo(pperrinfo)
#define SetErrorInfo(nReserved, perrinfo)	_XSetErrorInfo(nReserved, perrinfo)
#define GetErrorInfo(nReserved, pperrinfo)	_XGetErrorInfo(nReserved, pperrinfo)


#endif /* __OLEAUTO_H__ */

