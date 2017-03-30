/* -------------------------------------------------------------------------
//	File name		：	variant.cpp
//	Author 			：	Austin
//	Create Time		：	2017-3-30 16:15:11
//	Description 	：	Impl of VARIANT functions
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#ifndef X_OS_WINDOWS
#include "winnls.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define V_TYPE(v)		(V_VT((v)) & VT_TYPEMASK)
#define DEC_SCALE(d)	((d)->u.s.scale)

// -------------------------------------------------------------------------
WINOLEAUTAPI _MVariantClear(VARIANTARG * pvarg)
{
	HRESULT hr = S_OK;
	if (!V_ISBYREF(pvarg))
	{
		if (V_ISARRAY(pvarg) || V_VT(pvarg) == VT_SAFEARRAY)
		{
			hr = SafeArrayDestroy(V_ARRAY(pvarg));
		}
		else if (V_VT(pvarg) == VT_BSTR)
		{
			SysFreeString(V_BSTR(pvarg));
		}
//		else if (V_VT(pvarg) == VT_RECORD)
//		{
//			struct __tagBRECORD* pBr = &V_UNION(pvarg,brecVal);
//			if (pBr->pRecInfo)
//			{
//				IRecordInfo_RecordClear(pBr->pRecInfo, pBr->pvRecord);
//				IRecordInfo_Release(pBr->pRecInfo);
//			}
//		}
		else if (V_VT(pvarg) == VT_DISPATCH ||
				 V_VT(pvarg) == VT_UNKNOWN)
		{
			if (V_UNKNOWN(pvarg))
				V_UNKNOWN(pvarg)->Release();
		}
	}
	V_VT(pvarg) = VT_EMPTY;

	return hr;
}

WINOLEAUTAPI _MVariantCopy(VARIANTARG * pvargDest, const VARIANTARG * pvargSrc)
{
	HRESULT hr = S_OK;
	
	if (V_TYPE(pvargSrc) == VT_CLSID)/* VT_CLSID is a special case */
		return DISP_E_BADVARTYPE;
	
	if (pvargSrc != pvargDest && SUCCEEDED(hr = VariantClear(pvargDest)))
	{
		*pvargDest = *pvargSrc; /* Shallow copy the value */
	
		if (!V_ISBYREF(pvargSrc))
		{
			if (V_ISARRAY(pvargSrc))
			{
				if (V_ARRAY(pvargSrc))
					hr = SafeArrayCopy(V_ARRAY(pvargSrc), &V_ARRAY(pvargDest));
			}
			else if (V_VT(pvargSrc) == VT_BSTR)
			{
				V_BSTR(pvargDest) = SysAllocStringLen(V_BSTR(pvargSrc), SysStringLen(V_BSTR(pvargSrc)));
				if (!V_BSTR(pvargDest))
					hr = E_OUTOFMEMORY;
			}
//			else if (V_VT(pvargSrc) == VT_RECORD)
//			{
//				hr = VARIANT_CopyIRecordInfo(&V_UNION(pvargDest,brecVal));
//			}
			else if (V_VT(pvargSrc) == VT_DISPATCH ||
					 V_VT(pvargSrc) == VT_UNKNOWN)
			{
				if (V_UNKNOWN(pvargSrc))
					V_UNKNOWN(pvargSrc)->AddRef();
			}
		}
	}
	return hr;
}

static inline size_t VARIANT_DataSize(const VARIANT* pv)
{
	switch (V_TYPE(pv))
	{
	case VT_I1:
	case VT_UI1:	return sizeof(INT8);
	case VT_I2:
	case VT_UI2:	return sizeof(INT16);
	case VT_INT:
	case VT_UINT:
	case VT_I4:
	case VT_UI4:	return sizeof(INT32);
	case VT_I8:
	case VT_UI8:	return sizeof(INT64);
	case VT_R4:		return sizeof(float);
	case VT_R8:		return sizeof(double);
	case VT_DATE:	return sizeof(DATE);
	case VT_BOOL:	return sizeof(VARIANT_BOOL);
	case VT_DISPATCH:
	case VT_UNKNOWN:
	case VT_BSTR:	return sizeof(void*);
	case VT_CY:		return sizeof(CY);
	case VT_ERROR:	return sizeof(SCODE);
	}
	return 0;
}

WINOLEAUTAPI _MVariantCopyInd(VARIANT * pvarDest, VARIANTARG * pvargSrc)
{
	VARIANTARG vTmp, *pSrc = pvargSrc;
	VARTYPE vt;
	HRESULT hr = S_OK;
	
	if (!V_ISBYREF(pvargSrc))
		return VariantCopy(pvarDest, pvargSrc);
	
	/* Argument checking is more lax than VariantCopy()... */
	vt = V_TYPE(pvargSrc);
	if (V_ISARRAY(pvargSrc) || (V_VT(pvargSrc) == (VT_RECORD|VT_BYREF)) ||
		 (vt > VT_NULL && vt != (VARTYPE)15 && vt < VT_VOID &&
		 !(V_VT(pvargSrc) & (VT_VECTOR|VT_RESERVED))))
	{
		/* OK */
	}
	else
		return E_INVALIDARG; /* ...And the return value for invalid types differs too */
	
	if (pvargSrc == pvarDest)
	{
		/* In place copy. Use a shallow copy of pvargSrc & init pvargDest.
		 * This avoids an expensive VariantCopy() call - e.g. SafeArrayCopy().
		 */
		vTmp = *pvargSrc;
		pSrc = &vTmp;
		V_VT(pvarDest) = VT_EMPTY;
	}
	else
	{
		/* Copy into another variant. Free the variant in pvargDest */
		if (FAILED(hr = VariantClear(pvarDest)))
		{
			//TRACE("VariantClear() of destination failed\n");
			return hr;
		}
	}
	
	if (V_ISARRAY(pSrc))
	{
		/* Native doesn't check that *V_ARRAYREF(pSrc) is valid */
		hr = SafeArrayCopy(*V_ARRAYREF(pSrc), &V_ARRAY(pvarDest));
	}
	else if (V_VT(pSrc) == (VT_BSTR|VT_BYREF))
	{
		/* Native doesn't check that *V_BSTRREF(pSrc) is valid */
		V_BSTR(pvarDest) = SysAllocStringLen(*V_BSTRREF(pSrc), SysStringLen(*V_BSTRREF(pSrc)));
	}
//	else if (V_VT(pSrc) == (VT_RECORD|VT_BYREF))
//	{
//		V_UNION(pvarDest,brecVal) = V_UNION(pvargSrc,brecVal);
//		hr = VARIANT_CopyIRecordInfo(&V_UNION(pvarDest, brecVal));
//	}
	else if (V_VT(pSrc) == (VT_DISPATCH|VT_BYREF) ||
			 V_VT(pSrc) == (VT_UNKNOWN|VT_BYREF))
	{
		/* Native doesn't check that *V_UNKNOWNREF(pSrc) is valid */
		V_UNKNOWN(pvarDest) = *V_UNKNOWNREF(pSrc);
		if (*V_UNKNOWNREF(pSrc))
			(*V_UNKNOWNREF(pSrc))->AddRef();
	}
	else if (V_VT(pSrc) == (VT_VARIANT|VT_BYREF))
	{
		/* Native doesn't check that *V_VARIANTREF(pSrc) is valid */
		if (V_VT(V_VARIANTREF(pSrc)) == (VT_VARIANT|VT_BYREF))
			hr = E_INVALIDARG; /* Don't dereference more than one level */
		else
			hr = VariantCopyInd(pvarDest, V_VARIANTREF(pSrc));
	
		/* Use the dereferenced variants type value, not VT_VARIANT */
		goto VariantCopyInd_Return;
	}
//	else if (V_VT(pSrc) == (VT_DECIMAL|VT_BYREF))
//	{
//		memcpy(&DEC_SCALE(&V_DECIMAL(pvarDest)), &DEC_SCALE(V_DECIMALREF(pSrc)), sizeof(DECIMAL) - sizeof(USHORT));
//	}
	else
	{
		/* Copy the pointed to data into this variant */
		memcpy(&V_BYREF(pvarDest), V_BYREF(pSrc), VARIANT_DataSize(pSrc));
	}
	
	V_VT(pvarDest) = V_VT(pSrc) & ~VT_BYREF;
	
VariantCopyInd_Return:
	
	if (pSrc != pvargSrc)
		VariantClear(pSrc);

	return hr;
}

bool vtIsNumber(VARTYPE vt)
{
	return vt == VT_I2
		|| vt == VT_I4
		|| vt == VT_I1
		|| vt == VT_I8
		|| vt == VT_UI1
		|| vt == VT_UI2
		|| vt == VT_UI4
		|| vt == VT_UI8
		|| vt == VT_BOOL
		|| vt == VT_INT
		|| vt == VT_UINT;
}

template<typename T>
T _getNumber(const VARIANTARG * pvarg)
{
	switch (V_VT(pvarg))
	{
	case VT_I2:		return V_I2(pvarg);
	case VT_I4:		return V_I4(pvarg);
	case VT_I1:		return V_I1(pvarg);
	case VT_I8:		return V_I8(pvarg);
	case VT_UI1:	return V_UI1(pvarg);
	case VT_UI2:	return V_UI2(pvarg);
	case VT_UI4:	return V_UI4(pvarg);
	case VT_UI8:	return V_UI8(pvarg);
	case VT_BOOL:	return V_BOOL(pvarg);
	case VT_INT:	return V_INT(pvarg);
	case VT_UINT:	return V_UINT(pvarg);
	default:		assert(!"Invalid type");
	}

	return 0;
}

static void _copyNumber(VARIANTARG * pvargDest,
						const VARIANTARG * pvarSrc)
{
	switch (V_VT(pvargDest))
	{
	case VT_I2:
		V_I2(pvargDest) = _getNumber<SHORT>(pvarSrc);
		break;
	case VT_I4:
		V_I4(pvargDest) = _getNumber<LONG>(pvarSrc);
		break;
	case VT_I1:
		V_I1(pvargDest) = _getNumber<CHAR>(pvarSrc);
		break;
	case VT_I8:
		V_I8(pvargDest) = _getNumber<LONGLONG>(pvarSrc);
		break;
	case VT_UI1:
		V_UI1(pvargDest) = _getNumber<BYTE>(pvarSrc);
		break;
	case VT_UI2:
		V_UI2(pvargDest) = _getNumber<USHORT>(pvarSrc);
		break;
	case VT_UI4:
		V_UI4(pvargDest) = _getNumber<ULONG>(pvarSrc);
		break;
	case VT_UI8:
		V_UI8(pvargDest) = _getNumber<ULONGLONG>(pvarSrc);
		break;
	case VT_BOOL:
		V_BOOL(pvargDest) = _getNumber<BOOL>(pvarSrc);
		break;
	case VT_INT:
		V_INT(pvargDest) = _getNumber<INT>(pvarSrc);
		break;
	case VT_UINT:
		V_UINT(pvargDest) = _getNumber<UINT>(pvarSrc);
		break;
	default:
		assert(!"Invalid type");
	}
}

WINOLEAUTAPI _MVariantChangeType(VARIANTARG * pvargDest,
								 VARIANTARG * pvarSrc,
								 USHORT wFlags,
								 VARTYPE vt)
{
	if (pvarSrc && pvargDest)
	{
		if (V_VT(pvarSrc) == vt)
		{
			_MVariantCopy(pvargDest, pvarSrc);
			return S_OK;
		}
		else if (vtIsNumber(V_VT(pvarSrc)))
		{
			if (vtIsNumber(vt))
			{
				V_VT(pvargDest) = vt;
				_copyNumber(pvargDest, pvarSrc);
				return S_OK;
			}
			else if (vt == VT_R4)
			{
				V_R4(pvargDest) = V_I4(pvarSrc);
				V_VT(pvargDest) = VT_R4;
				return S_OK;
			}
			else if (vt == VT_R8)
			{
				V_R8(pvargDest) = V_I4(pvarSrc);
				V_VT(pvargDest) = VT_R8;
				return S_OK;
			}
			else if (vt == VT_BSTR)
			{
#ifdef HASQT
				QString qstr = QString::number(V_I4(pvarSrc));
				V_BSTR(pvargDest) = _XSysAllocString((const WCHAR*)qstr.utf16());
				V_VT(pvargDest) = VT_BSTR;
#endif
				return S_OK;
			}
		}
		else if (V_VT(pvarSrc) == VT_R4)
		{
			if (vtIsNumber(vt))
			{
				V_VT(pvargDest) = vt;
				V_I4(pvargDest) = V_R4(pvarSrc);
			}
			else if (vt == VT_R8)
			{
				V_R8(pvargDest) = V_R4(pvarSrc);
				V_VT(pvargDest) = VT_R8;
				return S_OK;
			}
			else if (vt == VT_BSTR)
			{
#ifdef HASQT
				QString qstr = QString::number(V_R4(pvarSrc));
				V_BSTR(pvargDest) = _XSysAllocString((const WCHAR*)qstr.utf16());
				V_VT(pvargDest) = VT_BSTR;
				return S_OK;
#endif
			}
		}
		else if (V_VT(pvarSrc) == VT_R8)
		{
			if (vtIsNumber(vt))
			{
				V_VT(pvargDest) = vt;
				V_I4(pvargDest) = V_R8(pvarSrc);
			}
			else if (vt == VT_R4)
			{
				V_R4(pvargDest) = V_R8(pvarSrc);
				V_VT(pvargDest) = VT_R4;
				return S_OK;
			}
			else if (vt == VT_BSTR)
			{
#ifdef HASQT
				QString qstr = QString::number(V_R8(pvarSrc));
				V_BSTR(pvargDest) = _XSysAllocString((const WCHAR*)qstr.utf16());
				V_VT(pvargDest) = VT_BSTR;
				return S_OK;
#endif
			}
		}
		else if (V_VT(pvarSrc) == VT_DISPATCH)
		{
			if (vt == VT_UNKNOWN)
			{
				V_UNKNOWN(pvargDest) = V_DISPATCH(pvarSrc);
				if (V_UNKNOWN(pvargDest))
					V_UNKNOWN(pvargDest)->AddRef();
				V_VT(pvargDest) = VT_UNKNOWN;
				return S_OK;
			}
		}
	}

	return E_FAIL;
}

WINOLEAUTAPI _MVariantChangeTypeEx(VARIANTARG * pvargDest,
									 VARIANTARG * pvarSrc,
									 LCID lcid,
									 USHORT wFlags,
									 VARTYPE vt)
{
	return E_NOTIMPL;
}

#define _VARCMP(a,b) \
	(((a) == (b)) ? VARCMP_EQ : (((a) < (b)) ? VARCMP_LT : VARCMP_GT))

WINOLEAUTAPI _MVariantCompare(LPVARIANT pvarLeft,
							  LPVARIANT pvarRight,
							  LCID lcid,
							  ULONG dwFlags)
{
	HRESULT hr = E_FAIL;

	if (pvarLeft == pvarRight)
		return VARCMP_EQ;

	assert(V_VT(pvarLeft) == V_VT(pvarRight));

	switch (V_VT(pvarLeft))
	{
	case VT_EMPTY:
		return VARCMP_EQ;
	case VT_NULL:
		return VARCMP_NULL;
	case VT_I2:
		return _VARCMP(V_I2(pvarLeft), V_I2(pvarRight));
	case VT_I4:
		return _VARCMP(V_I4(pvarLeft), V_I4(pvarRight));
	case VT_R4:
		return _VARCMP(V_R4(pvarLeft), V_R4(pvarRight));
	case VT_R8:
		return _VARCMP(V_R8(pvarLeft), V_R8(pvarRight));
	case VT_CY:
	{
		double l, r;
		l = (double)V_CY(pvarLeft).int64;
		r = (double)V_CY(pvarRight).int64;
		
		if (l - r < 0)
			return VARCMP_LT;
		else if (l - r > 0)
			return VARCMP_GT;
		else
			return VARCMP_EQ;
	}
	case VT_DATE:
		return _VARCMP(V_DATE(pvarLeft), V_DATE(pvarRight));
	case VT_BSTR:
	{
#ifdef HASQT
		/* TODO: compare according to LCID, just use local now */
		int result;
		QString sL, sR;
		result = 0;
		sL = QString::fromUtf16(V_BSTR(pvarLeft));
		sR = QString::fromUtf16(V_BSTR(pvarRight));
		
		if (dwFlags & NORM_IGNORECASE)
		{
			sL = sL.toLower();
			sR = sR.toLower();
		}
		
		result = QString::localeAwareCompare(sL, sR);	// just local
		if (result < 0)
			return VARCMP_LT;
		else if (result > 0)
			return VARCMP_GT;
		else
			return VARCMP_EQ;
#endif
	}
	case VT_DISPATCH:
		return VARCMP_NULL; // how to handle ?
	case VT_ERROR:
		/* If both input variants are ERROR then VARCMP_EQ will be returned,
		 * else an ERROR variant will trigger an error. */
		return VARCMP_EQ;
	case VT_BOOL:
		return _VARCMP(V_BOOL(pvarLeft), V_BOOL(pvarRight));
	case VT_UNKNOWN:
		return VARCMP_NULL; // how to handle ?
	case VT_I1:
		return _VARCMP(V_I1(pvarLeft), V_I1(pvarRight));
	case VT_UI1:
		return _VARCMP(V_UI1(pvarLeft), V_UI1(pvarRight));
	case VT_UI2:
		return _VARCMP(V_UI2(pvarLeft), V_UI2(pvarRight));
	case VT_UI4:
		return _VARCMP(V_UI4(pvarLeft), V_UI4(pvarRight));
	case VT_I8:
		return _VARCMP(V_I8(pvarLeft), V_I8(pvarRight));
	case VT_UI8:
		return _VARCMP(V_UI8(pvarLeft), V_UI8(pvarRight));
	case VT_INT:
		return _VARCMP(V_INT(pvarLeft), V_INT(pvarRight));
	case VT_UINT:
		return _VARCMP(V_UINT(pvarLeft), V_UINT(pvarRight));
	default:
		assert(false);	// We should never get here
		break;
	}

	return hr;
}

// -------------------------------------------------------------------------
void _force_link_variant() {}

