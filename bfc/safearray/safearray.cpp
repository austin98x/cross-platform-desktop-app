/* -------------------------------------------------------------------------
//	File name		：	safearray.cpp
//	Author 			：	Austin
//	Create Time		：	2016-5-23 15:15:11
//	Description 	：	Impl of SAFEARRAY functions
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
const USHORT FADF_DATADELETED		= 0x1000;
const USHORT FADF_CREATEVECTOR		= 0x2000;
const USHORT SAFEARRAY_HIDDEN_SIZE	= sizeof(GUID);

// -------------------------------------------------------------------------

/* Get the size of a supported VT type (0 means unsupported) */
static DWORD SAFEARRAY_GetVTSize(VARTYPE vt)
{
	switch (vt)
	{
	case VT_I1:
	case VT_UI1:		return sizeof(BYTE);
	case VT_BOOL:
	case VT_I2:
	case VT_UI2:		return sizeof(SHORT);
	case VT_I4:
	case VT_UI4:
	case VT_R4:
	case VT_ERROR:		return sizeof(INT32);
	case VT_R8:
	case VT_I8:
	case VT_UI8:		return sizeof(INT64);
	case VT_INT:
	case VT_UINT:		return sizeof(INT32);
	case VT_CY:			return sizeof(CY);
	case VT_DATE:		return sizeof(DATE);
	case VT_BSTR:		return sizeof(BSTR);
	case VT_DISPATCH:	return sizeof(LPDISPATCH);
	case VT_VARIANT:	return sizeof(VARIANT);
	case VT_UNKNOWN:	return sizeof(LPUNKNOWN);
	case VT_DECIMAL:	return sizeof(DECIMAL);
	/* Note: Return a non-zero size to indicate vt is valid. The actual size
	 * of a UDT is taken from the result of IRecordInfo_GetSize().
	 */
	case VT_RECORD:	 return 32;
	}
	return 0;
}

/* Set the hidden data for an array */
static inline void SAFEARRAY_SetHiddenDWORD(SAFEARRAY* psa, DWORD dw)
{
	/* Implementation data is stored in the 4 bytes before the header */
	LPDWORD lpDw = (LPDWORD)psa;
	lpDw[-1] = dw;
}

static inline DWORD SAFEARRAY_GetHiddenDWORD(SAFEARRAY* psa)
{
	LPDWORD lpDw = (LPDWORD)psa;
	return lpDw[-1];
}

static HRESULT WINAPI SafeArrayGetIID(SAFEARRAY *psa, GUID *pGuid)
{
	GUID* src = (GUID*)psa;

	if (!psa || !pGuid || !(psa->fFeatures & FADF_HAVEIID))
		return E_INVALIDARG;

	*pGuid = src[-1];
	return S_OK;
}

static HRESULT WINAPI SafeArraySetIID(SAFEARRAY *psa, REFGUID guid)
{
	GUID* dest = (GUID*)psa;

	if (!psa || !(psa->fFeatures & FADF_HAVEIID))
		return E_INVALIDARG;

	dest[-1] = guid;
	return S_OK;
}

/* Get the number of cells in a SafeArray */
static UINT32 SAFEARRAY_GetCellCount(const SAFEARRAY *psa)
{
	const SAFEARRAYBOUND* psab = psa->rgsabound;
	USHORT cCount = psa->cDims;
	UINT32 ulNumCells = 1;

	while (cCount--)
	{
		/* This is a valid bordercase. See testcases. -Marcus */
		if (!psab->cElements)
			return 0;
		ulNumCells *= psab->cElements;
		psab++;
	}

	return ulNumCells;
}

/* Copy data items from one array to another */
static HRESULT SAFEARRAY_CopyData(SAFEARRAY *psa, SAFEARRAY *dest)
{
	if (!psa->pvData)
		return S_OK;
	else if (!dest->pvData || psa->fFeatures & FADF_DATADELETED)
		return E_INVALIDARG;
	else
	{
		UINT32 ulCellCount = SAFEARRAY_GetCellCount(psa);
	
		dest->fFeatures = (dest->fFeatures & FADF_CREATEVECTOR) |
							(psa->fFeatures & ~(FADF_CREATEVECTOR|FADF_DATADELETED));
	
		if (psa->fFeatures & FADF_VARIANT)
		{
			VARIANT* lpVariant = (VARIANT*)psa->pvData;
			VARIANT* lpDest = (VARIANT*)dest->pvData;
	
			while(ulCellCount--)
			{
				VariantCopy(lpDest, lpVariant);
				lpVariant++;
				lpDest++;
			}
		}
		else if (psa->fFeatures & FADF_BSTR)
		{
			BSTR* lpBstr = (BSTR*)psa->pvData;
			BSTR* lpDest = (BSTR*)dest->pvData;
	
			while(ulCellCount--)
			{
				if (*lpBstr)
				{
					*lpDest = SysAllocStringByteLen((char*)*lpBstr, SysStringByteLen(*lpBstr));
					if (!*lpDest)
					return E_OUTOFMEMORY;
				}
				else
					*lpDest = NULL;
				lpBstr++;
				lpDest++;
			}
		}
		else
		{
			/* Copy the data over */
			memcpy(dest->pvData, psa->pvData, ulCellCount * psa->cbElements);
	
			if (psa->fFeatures & (FADF_UNKNOWN|FADF_DISPATCH))
			{
				LPUNKNOWN *lpUnknown = (LPUNKNOWN *)dest->pvData;
		
				while(ulCellCount--)
				{
					if (*lpUnknown)
						(*lpUnknown)->AddRef();
					lpUnknown++;
				}
			}
		}

		if (psa->fFeatures & FADF_RECORD)
		{
//			IRecordInfo* pRecInfo = NULL;
	
//			SafeArrayGetRecordInfo(psa, &pRecInfo);
//			SafeArraySetRecordInfo(dest, pRecInfo);
	
//			if (pRecInfo)
//			{
//				/* Release because Get() adds a reference */
//				IRecordInfo_Release(pRecInfo);
//			}
		}
		else if (psa->fFeatures & FADF_HAVEIID)
		{
			GUID guid;
			SafeArrayGetIID(psa, &guid);
			SafeArraySetIID(dest, guid);
		}
		else if (psa->fFeatures & FADF_HAVEVARTYPE)
		{
			SAFEARRAY_SetHiddenDWORD(dest, SAFEARRAY_GetHiddenDWORD(psa));
		}
	}
	return S_OK;
}

/* Free data items in an array */
static HRESULT SAFEARRAY_DestroyData(SAFEARRAY *psa, UINT32 ulStartCell)
{
	if (psa->pvData && !(psa->fFeatures & FADF_DATADELETED))
	{
		UINT32 ulCellCount = SAFEARRAY_GetCellCount(psa);

		if (ulStartCell > ulCellCount)
			return E_UNEXPECTED;
	
		ulCellCount -= ulStartCell;
	
		if (psa->fFeatures & (FADF_UNKNOWN|FADF_DISPATCH))
		{
			LPUNKNOWN *lpUnknown = (LPUNKNOWN *)psa->pvData + ulStartCell;
	
			while(ulCellCount--)
			{
				if (*lpUnknown)
					(*lpUnknown)->Release();
				lpUnknown++;
			}
		}
		else if (psa->fFeatures & (FADF_RECORD))
		{
//			IRecordInfo *lpRecInfo;
	
//			if (SUCCEEDED(SafeArrayGetRecordInfo(psa, &lpRecInfo)))
//			{
//			PBYTE pRecordData = psa->pvData;
//			while(ulCellCount--)
//			{
//				IRecordInfo_RecordClear(lpRecInfo, pRecordData);
//				pRecordData += psa->cbElements;
//			}
//			IRecordInfo_Release(lpRecInfo);
//			}
		}
		else if (psa->fFeatures & FADF_BSTR)
		{
			BSTR* lpBstr = (BSTR*)psa->pvData + ulStartCell;
			while(ulCellCount--)
			{
				SysFreeString(*lpBstr);
				lpBstr++;
			}
		}
		else if (psa->fFeatures & FADF_VARIANT)
		{
			VARIANT* lpVariant = (VARIANT*)psa->pvData + ulStartCell;
	
			while(ulCellCount--)
			{
				VariantClear(lpVariant);
				lpVariant++;
			}
		}
	}
	return S_OK;
}

/* Set the features of an array */
static void SAFEARRAY_SetFeatures(VARTYPE vt, SAFEARRAY *psa)
{
	/* Set the IID if we have one, otherwise set the type */
	if (vt == VT_DISPATCH)
	{
		psa->fFeatures = FADF_HAVEIID;
		SafeArraySetIID(psa, IID_IDispatch);
	}
	else if (vt == VT_UNKNOWN)
	{
		psa->fFeatures = FADF_HAVEIID;
		SafeArraySetIID(psa, IID_IUnknown);
	}
	else if (vt == VT_RECORD)
	{
		psa->fFeatures = FADF_RECORD;
	}
	else
	{
		psa->fFeatures = FADF_HAVEVARTYPE;
		SAFEARRAY_SetHiddenDWORD(psa, vt);
	}
}

static HRESULT WINAPI SafeArrayAllocDescriptorEx(VARTYPE vt, UINT cDims, SAFEARRAY **ppsaOut)
{
	HRESULT hRet = E_UNEXPECTED;
	
	UINT32 cbElements = SAFEARRAY_GetVTSize(vt);
	
	hRet = _MSafeArrayAllocDescriptor(cDims, ppsaOut);
	
	if (SUCCEEDED(hRet))
	{
		SAFEARRAY_SetFeatures(vt, *ppsaOut);
		(*ppsaOut)->cbElements = cbElements;
	}

	return hRet;
}

static bool _MCheckVARTYPE(VARTYPE vt)
{
	return (vt != VT_EMPTY)
		&& (vt != VT_NULL)
		&& (!(vt & VT_ARRAY))
		&& (!(vt & VT_VECTOR))
		&& (!(vt & VT_BYREF));
}

static SAFEARRAY* SAFEARRAY_Create(VARTYPE vt, UINT32 cDims, const SAFEARRAYBOUND *rgsabound, UINT32 ulSize)
{
	SAFEARRAY *psa = NULL;
	
	if (!_MCheckVARTYPE(vt) || !rgsabound)
		return NULL;
	
	if (SUCCEEDED(SafeArrayAllocDescriptorEx(vt, cDims, &psa)))
	{
		switch (vt)
		{
		case VT_BSTR:		psa->fFeatures |= FADF_BSTR;		break;
		case VT_UNKNOWN:	psa->fFeatures |= FADF_UNKNOWN;		break;
		case VT_DISPATCH:	psa->fFeatures |= FADF_DISPATCH;	break;
		case VT_VARIANT:	psa->fFeatures |= FADF_VARIANT;		break;
		}
		
		for (UINT i = 0; i < cDims; i++)
			memcpy(psa->rgsabound + i, rgsabound + cDims - 1 - i, sizeof(SAFEARRAYBOUND));
		
		if (ulSize)
			psa->cbElements = ulSize;
		
		if (!psa->cbElements || FAILED(_MSafeArrayAllocData(psa)))
		{
			_MSafeArrayDestroyDescriptor(psa);
			psa = NULL;
		}
	}

	return psa;
}

/* Allocate a descriptor for an array */
static HRESULT SAFEARRAY_AllocDescriptor(UINT32 ulSize, SAFEARRAY **ppsaOut)
{
	char *ptr = (char *)AllocMemory(ulSize + SAFEARRAY_HIDDEN_SIZE);
	
	if (!ptr)
	{
		*ppsaOut = NULL;
		return E_UNEXPECTED;
	}
	
	*ppsaOut = (SAFEARRAY*)(ptr + SAFEARRAY_HIDDEN_SIZE);

	return S_OK;
}

// ----------------------------------------------------------------------

WINOLEAUTAPI _MSafeArrayAccessData(SAFEARRAY *psa, void ** ppvData)
{
	if(!psa || !ppvData)
		return E_INVALIDARG;
	
	if (SUCCEEDED(_MSafeArrayLock(psa)))
	{
		*ppvData = psa->pvData;
		return S_OK;
	}
	
	*ppvData = NULL;
	
	return E_UNEXPECTED;
}

WINOLEAUTAPI _MSafeArrayAllocData(SAFEARRAY * psa)
{
	HRESULT hRet = E_INVALIDARG;

	if (psa)
	{
		UINT32 ulCount = SAFEARRAY_GetCellCount(psa);
		UINT32 ulSize = ulCount * psa->cbElements;
		
		psa->pvData = AllocMemory(ulSize);
		memset(psa->pvData, 0, ulSize);

		hRet = (psa->pvData ? S_OK : E_OUTOFMEMORY);
	}

	return hRet;
}

WINOLEAUTAPI _MSafeArrayAllocDescriptor(UINT cDims, SAFEARRAY ** ppsaOut)
{
	if (!cDims || cDims >= 0x10000) /* Maximum 65535 dimensions */
		return E_INVALIDARG;
	
	if (!ppsaOut)
		return E_POINTER;
	
	/* We need enough space for the header and its bounds */
	INT32 allocSize = sizeof(SAFEARRAY) + sizeof(SAFEARRAYBOUND) * (cDims - 1);
	
	if (FAILED(SAFEARRAY_AllocDescriptor(allocSize, ppsaOut)))
		return E_UNEXPECTED;
	
	(*ppsaOut)->cDims = cDims;
	(*ppsaOut)->fFeatures = FADF_FIXEDSIZE;
	(*ppsaOut)->cbElements = 0;
	(*ppsaOut)->cLocks = 0;
	(*ppsaOut)->pvData = NULL;
	memset((*ppsaOut)->rgsabound, 0, sizeof(SAFEARRAYBOUND) * cDims);
	
	return S_OK;
}

WINOLEAUTAPI _MSafeArrayCopy(SAFEARRAY * psa, SAFEARRAY ** ppsaOut)
{
	HRESULT hr;

	if (!ppsaOut)
		return E_INVALIDARG;
	
	*ppsaOut = NULL;
	
	if (!psa)
		return S_OK; /* Handles copying of NULL arrays */
	
	if (!psa->cbElements)
		return E_INVALIDARG;
	
	if (psa->fFeatures & (FADF_RECORD|FADF_HAVEIID|FADF_HAVEVARTYPE))
	{
		VARTYPE vt;
		if (FAILED(SafeArrayGetVartype(psa, &vt)))
		{
			hr = E_UNEXPECTED;
		}
		else
		{
			hr = E_UNEXPECTED;

			UINT32 cbElements = SAFEARRAY_GetVTSize(vt);
			
			hr = SafeArrayAllocDescriptor(psa->cDims, ppsaOut);
			
			if (SUCCEEDED(hr))
			{		
				if (vt == VT_DISPATCH)
				{
					(*ppsaOut)->fFeatures = FADF_HAVEIID;
					SafeArraySetIID(*ppsaOut, IID_IDispatch);
				}
				else if (vt == VT_UNKNOWN)
				{
					(*ppsaOut)->fFeatures = FADF_HAVEIID;
					SafeArraySetIID(*ppsaOut, IID_IUnknown);
				}
				else if (vt == VT_RECORD)
					(*ppsaOut)->fFeatures = FADF_RECORD;
				else
				{
					(*ppsaOut)->fFeatures = FADF_HAVEVARTYPE;
					LPDWORD lpDw = (LPDWORD)*ppsaOut;
					lpDw[-1] = vt;
				}
				(*ppsaOut)->cbElements = cbElements;
			}
		}
	}
	else
	{
		hr = SafeArrayAllocDescriptor(psa->cDims, ppsaOut);
		if (SUCCEEDED(hr))
		{
			(*ppsaOut)->fFeatures = psa->fFeatures & ~FADF_CREATEVECTOR;
			(*ppsaOut)->cbElements = psa->cbElements;
		}
	}
	
	if (SUCCEEDED(hr))
	{
		/* Copy dimension bounds */
		memcpy((*ppsaOut)->rgsabound, psa->rgsabound, psa->cDims * sizeof(SAFEARRAYBOUND));

		hr = _MSafeArrayAllocData(*ppsaOut);
		if (SUCCEEDED(hr) && (*ppsaOut)->pvData)
		{
			hr = SAFEARRAY_CopyData(psa, *ppsaOut);

			if (SUCCEEDED(hr))
				return hr;

			FreeMemory((*ppsaOut)->pvData);
		}
	
		SafeArrayDestroyDescriptor(*ppsaOut);
	}

	*ppsaOut = NULL;
	return hr;
}

WINOLEAUTAPI _MSafeArrayCopyData(SAFEARRAY *psaSource, SAFEARRAY *psaTarget)
{
	if (!psaSource || !psaTarget ||
		psaSource->cDims != psaTarget->cDims ||
		psaSource->cbElements != psaTarget->cbElements)
	{
		return E_INVALIDARG;
	}

	/* Each dimension must be the same size */
	for (int dim = psaSource->cDims - 1; dim >= 0 ; dim--)
	{
		if (psaSource->rgsabound[dim].cElements !=
			psaTarget->rgsabound[dim].cElements)
			return E_INVALIDARG;
	}

	if (SUCCEEDED(SAFEARRAY_DestroyData(psaTarget, 0)) &&
		SUCCEEDED(SAFEARRAY_CopyData(psaSource, psaTarget)))
		return S_OK;

	return E_UNEXPECTED;
}

WINOLEAUTAPI_(_SAFEARRAY_PTR) _MSafeArrayCreate(VARTYPE vt, UINT32 cDims, SAFEARRAYBOUND* rgsabound)
{
	if (vt == VT_RECORD)
		return NULL;
	
	return SAFEARRAY_Create(vt, cDims, rgsabound, 0);
}

WINOLEAUTAPI_(_SAFEARRAY_PTR) _MSafeArrayCreateVector(VARTYPE vt, INT32 lLbound, UINT32 cElements)
{
	SAFEARRAYBOUND bound = { cElements, lLbound };
	return _MSafeArrayCreate(vt, 1, &bound);
}

WINOLEAUTAPI _MSafeArrayDestroy(SAFEARRAY * psa)
{
	if (psa)
	{
		if (psa->cLocks > 0)
			return DISP_E_ARRAYISLOCKED;
	
		_MSafeArrayDestroyData(psa);
		_MSafeArrayDestroyDescriptor(psa);
	}

	return S_OK;
}

WINOLEAUTAPI _MSafeArrayDestroyDescriptor(SAFEARRAY * psa)
{
	if (psa)
	{
		LPVOID lpv = (char*)psa - SAFEARRAY_HIDDEN_SIZE;
		
		if (psa->cLocks)
			return DISP_E_ARRAYISLOCKED; /* Can't destroy a locked array */
		
//		if (psa->fFeatures & FADF_RECORD)
//			SafeArraySetRecordInfo(psa, NULL);
		
		if (psa->fFeatures & FADF_CREATEVECTOR &&
				!(psa->fFeatures & FADF_DATADELETED))
			SAFEARRAY_DestroyData(psa, 0); /* Data not previously deleted */
		
		FreeMemory(lpv);
	}
	
	return S_OK;
}

WINOLEAUTAPI _MSafeArrayDestroyData(SAFEARRAY * psa)
{
	if (!psa)
		return E_INVALIDARG;
	
	if (psa->cLocks)
		return DISP_E_ARRAYISLOCKED; /* Can't delete a locked array */
	
	/* Delete the actual item data */
	if (FAILED(SAFEARRAY_DestroyData(psa, 0)))
		return E_UNEXPECTED;
	
	if (psa->pvData)
	{
		if (psa->fFeatures & FADF_STATIC)
		{
			ZeroMemory(psa->pvData, SAFEARRAY_GetCellCount(psa) * psa->cbElements);
			return S_OK;
		}
		
		/* If this is not a vector, free the data memory block */
		if (!(psa->fFeatures & FADF_CREATEVECTOR))
		{
			FreeMemory(psa->pvData);
			psa->pvData = NULL;
		}
		else
		{
			psa->fFeatures |= FADF_DATADELETED; /* Mark the data deleted */
		}
	}
	
	return S_OK;
}

WINOLEAUTAPI_(UINT32) _MSafeArrayGetDim(SAFEARRAY * psa)
{
	return psa ? psa->cDims : 0;
}

WINOLEAUTAPI_(UINT32) _MSafeArrayGetElemsize(SAFEARRAY * psa)
{
	return psa ? psa->cbElements : 0;
}

WINOLEAUTAPI _MSafeArrayGetElement(SAFEARRAY * psa, INT32 * rgIndices, void * pv)
{
	if (!psa || !rgIndices || !pv)
		return E_INVALIDARG;
	
	HRESULT hRet = _MSafeArrayLock(psa);
	
	if (SUCCEEDED(hRet))
	{
		PVOID lpvSrc;
		
		hRet = _MSafeArrayPtrOfIndex(psa, rgIndices, &lpvSrc);
		
		if (SUCCEEDED(hRet))
		{
			if (psa->fFeatures & FADF_VARIANT)
			{
				VARIANT* lpVariant = (VARIANT *)lpvSrc;
				VARIANT* lpDest = (VARIANT *)pv;
				
				/* The original content of pv is ignored. */
				V_VT(lpDest) = VT_EMPTY;
				hRet = VariantCopy(lpDest, lpVariant);
			}
			else if (psa->fFeatures & FADF_BSTR)
			{
				BSTR* lpBstr = (BSTR *)lpvSrc;
				BSTR* lpDest = (BSTR *)pv;
				
				if (*lpBstr)
				{
					*lpDest = SysAllocStringLen(*lpBstr, SysStringLen(*lpBstr));
					if (!*lpBstr)
						hRet = E_OUTOFMEMORY;
				}
				else
					*lpDest = NULL;
			}
			else
			{
				if (psa->fFeatures & (FADF_UNKNOWN|FADF_DISPATCH))
				{
					LPUNKNOWN *lpUnknown = (LPUNKNOWN *)lpvSrc;
					
					if (*lpUnknown)
						(*lpUnknown)->AddRef();
				}
				/* Copy the data over */
				memcpy(pv, lpvSrc, psa->cbElements);
			}
		}

		_MSafeArrayUnlock(psa);
	}

	return hRet;
}

WINOLEAUTAPI _MSafeArrayGetUBound(SAFEARRAY * psa, UINT32 nDim, INT32 * plUbound)
{
	if (!psa || !plUbound)
		return E_INVALIDARG;
	
	if(!nDim || nDim > psa->cDims)
		return DISP_E_BADINDEX;
	
	*plUbound = psa->rgsabound[psa->cDims - nDim].lLbound +
			psa->rgsabound[psa->cDims - nDim].cElements - 1;
	
	return S_OK;
}

WINOLEAUTAPI _MSafeArrayGetLBound(SAFEARRAY * psa, UINT32 nDim, INT32 * plLbound)
{
	if (!psa || !plLbound)
		return E_INVALIDARG;
	
	if(!nDim || nDim > psa->cDims)
		return DISP_E_BADINDEX;
	
	*plLbound = psa->rgsabound[psa->cDims - nDim].lLbound;
	return S_OK;
}

WINOLEAUTAPI _MSafeArrayLock(SAFEARRAY * psa)
{
	if (!psa)
		return E_INVALIDARG;
	
	UINT32 ulLocks = InterlockedIncrement((INT32*)&psa->cLocks);
	
	if (ulLocks > 0xFFFF) /* Maximum of 16384 locks at a time */
	{
		InterlockedDecrement((INT32*)&psa->cLocks);
		return E_UNEXPECTED;
	}

	return S_OK;
}

WINOLEAUTAPI _MSafeArrayUnlock(SAFEARRAY * psa)
{
	if (!psa)
		return E_INVALIDARG;

	if (InterlockedDecrement((INT32*)&psa->cLocks) < 0)
	{
		InterlockedIncrement((INT32*)&psa->cLocks);
		return E_UNEXPECTED;
	}

	return S_OK;
}

WINOLEAUTAPI _MSafeArrayPutElement(SAFEARRAY * psa, INT32 * rgIndices, void * pv)
{
	HRESULT hRet;
	
	if (!psa || !rgIndices)
		return E_INVALIDARG;
	
	hRet = _MSafeArrayLock(psa);
	
	if (SUCCEEDED(hRet))
	{
		PVOID lpvDest;
		
		hRet = _MSafeArrayPtrOfIndex(psa, rgIndices, &lpvDest);
		
		if (SUCCEEDED(hRet))
		{
			if (psa->fFeatures & FADF_VARIANT)
			{
				VARIANT* lpVariant = (VARIANT *)pv;
				VARIANT* lpDest = (VARIANT *)lpvDest;
				
				hRet = VariantClear(lpDest);
				hRet = VariantCopy(lpDest, lpVariant);
			}
			else if (psa->fFeatures & FADF_BSTR)
			{
				BSTR  lpBstr = (BSTR)pv;
				BSTR* lpDest = (BSTR*)lpvDest;
				
				SysFreeString(*lpDest);
				
				*lpDest = SysAllocStringLen(lpBstr, SysStringLen(lpBstr));
				if (!*lpDest)
					hRet = E_OUTOFMEMORY;
			}
			else
			{
				if (psa->fFeatures & (FADF_UNKNOWN|FADF_DISPATCH))
				{
					LPUNKNOWN  lpUnknown = (LPUNKNOWN)pv;
					LPUNKNOWN *lpDest = (LPUNKNOWN *)lpvDest;
					
					if (lpUnknown)
						lpUnknown->AddRef();
					if (*lpDest)
						(*lpDest)->Release();
					*lpDest = lpUnknown;
				}
				else
				{
					/* Copy the data over */
					memcpy(lpvDest, pv, psa->cbElements);
				}
			}
		}

		_MSafeArrayUnlock(psa);
	}
	
	return hRet;
}

WINOLEAUTAPI _MSafeArrayPtrOfIndex(SAFEARRAY * psa, INT32 * rgIndices, void ** ppvData)
{
	UINT32 cell = 0, dimensionSize = 1;
	SAFEARRAYBOUND* psab;
	INT32 c1;
	
	/* The general formula for locating the cell number of an entry in an n
	 * dimensional array (where cn = coordinate in dimension dn) is:
	 *
	 * c1 + c2 * sizeof(d1) + c3 * sizeof(d2) ... + cn * sizeof(c(n-1))
	 *
	 * We calculate the size of the last dimension at each step through the
	 * dimensions to avoid recursing to calculate the last dimensions size.
	 */
	if (!psa || !rgIndices || !ppvData)
		return E_INVALIDARG;
	
	psab = psa->rgsabound + psa->cDims - 1;
	c1 = *rgIndices++;
	
	if (c1 < psab->lLbound || c1 >= psab->lLbound + (INT32)psab->cElements)
		return DISP_E_BADINDEX; /* Initial index out of bounds */
	
	for (USHORT dim = 1; dim < psa->cDims; dim++)
	{
		dimensionSize *= psab->cElements;
		
		psab--;
		
		if (!psab->cElements || *rgIndices < psab->lLbound ||
			*rgIndices >= psab->lLbound + (INT32)psab->cElements)
			return DISP_E_BADINDEX; /* Index out of bounds */
		
		cell += (*rgIndices - psab->lLbound) * dimensionSize;
		rgIndices++;
	}
	
	cell += (c1 - psa->rgsabound[psa->cDims - 1].lLbound);
	
	*ppvData = (char*)psa->pvData + cell * psa->cbElements;

	return S_OK;
}

WINOLEAUTAPI _MSafeArrayRedim(SAFEARRAY * psa, SAFEARRAYBOUND * psaboundNew)
{
	SAFEARRAYBOUND *oldBounds;

	if (!psa || psa->fFeatures & FADF_FIXEDSIZE || !psaboundNew)
		return E_INVALIDARG;
	
	if (psa->cLocks > 0)
		return DISP_E_ARRAYISLOCKED;
	
	if (FAILED(_MSafeArrayLock(psa)))
		return E_UNEXPECTED;
	
	oldBounds = psa->rgsabound;
	oldBounds->lLbound = psaboundNew->lLbound;
	
	if (psaboundNew->cElements != oldBounds->cElements)
	{
		if (psaboundNew->cElements < oldBounds->cElements)
		{
			/* Shorten the final dimension. */
			UINT32 ulStartCell = psaboundNew->cElements *
					(SAFEARRAY_GetCellCount(psa) / oldBounds->cElements);
			SAFEARRAY_DestroyData(psa, ulStartCell);
		}
		else
		{
			/* Lengthen the final dimension */
			UINT32 ulOldSize, ulNewSize;
			PVOID pvNewData;
			
			ulOldSize = SAFEARRAY_GetCellCount(psa) * psa->cbElements;
			if (ulOldSize)
			{
				ulNewSize = (ulOldSize / oldBounds->cElements) * psaboundNew->cElements;
			}
			else
			{
				int oldelems = oldBounds->cElements;
				oldBounds->cElements = psaboundNew->cElements;
				ulNewSize = SAFEARRAY_GetCellCount(psa) * psa->cbElements;
				oldBounds->cElements = oldelems;
			}
			
			if (!(pvNewData = AllocMemory(ulNewSize)))
			{
				_MSafeArrayUnlock(psa);
				return E_UNEXPECTED;
			}
			
			memcpy(pvNewData, psa->pvData, ulOldSize);
			FreeMemory(psa->pvData);
			psa->pvData = pvNewData;
		}
		oldBounds->cElements = psaboundNew->cElements;
	}
	
	_MSafeArrayUnlock(psa);

	return S_OK;
}

WINOLEAUTAPI _MSafeArrayUnaccessData(SAFEARRAY * psa)
{
	return _MSafeArrayUnlock(psa);
}

WINOLEAUTAPI _MSafeArrayGetVartype(SAFEARRAY * psa, VARTYPE * pvt)
{
	if (!psa || !pvt)
		return E_INVALIDARG;

	if (psa->fFeatures & FADF_RECORD)
	{
		*pvt = VT_RECORD;
	}
	else if ((psa->fFeatures & (FADF_HAVEIID|FADF_DISPATCH)) == (FADF_HAVEIID|FADF_DISPATCH))
	{
		*pvt = VT_DISPATCH;
	}
	else if (psa->fFeatures & FADF_HAVEIID)
	{
		*pvt = VT_UNKNOWN;
	}
	else if (psa->fFeatures & FADF_HAVEVARTYPE)
	{
		VARTYPE vt = SAFEARRAY_GetHiddenDWORD(psa);
		*pvt = vt;
	}
	else
	{
		return E_INVALIDARG;
	}

	return S_OK;
}

// -------------------------------------------------------------------------
void _force_link_safearray() {}

