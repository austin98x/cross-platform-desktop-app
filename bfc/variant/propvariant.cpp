/* -------------------------------------------------------------------------
//	File name		：	propvariant.cpp
//	Author 			：	Austin
//	Create Time		：	2017-3-30 15:15:11
//	Description 	：	Impl of VARIANT functions
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#ifndef X_OS_WINDOWS
#include "bfc/com/propidl.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static void OLE_FreeClipDataArray(ULONG count, CLIPDATA * pClipDataArray)
{
	ULONG i;
	for (i = 0; i < count; i++)
		if (pClipDataArray[i].pClipData)
			CoTaskMemFree(pClipDataArray[i].pClipData);
}

static inline HRESULT PROPVARIANT_ValidateType(VARTYPE vt)
{
	switch (vt)
	{
	case VT_EMPTY:
	case VT_NULL:
	case VT_I2:
	case VT_I4:
	case VT_R4:
	case VT_R8:
	case VT_CY:
	case VT_DATE:
	case VT_BSTR:
	case VT_ERROR:
	case VT_BOOL:
	case VT_DECIMAL:
	case VT_UI1:
	case VT_UI2:
	case VT_UI4:
	case VT_I8:
	case VT_UI8:
	case VT_LPSTR:
	case VT_LPWSTR:
	case VT_FILETIME:
	case VT_BLOB:
	case VT_STREAM:
	case VT_STORAGE:
	case VT_STREAMED_OBJECT:
	case VT_STORED_OBJECT:
	case VT_BLOB_OBJECT:
	case VT_CF:
	case VT_CLSID:
	case VT_I2|VT_VECTOR:
	case VT_I4|VT_VECTOR:
	case VT_R4|VT_VECTOR:
	case VT_R8|VT_VECTOR:
	case VT_CY|VT_VECTOR:
	case VT_DATE|VT_VECTOR:
	case VT_BSTR|VT_VECTOR:
	case VT_ERROR|VT_VECTOR:
	case VT_BOOL|VT_VECTOR:
	case VT_VARIANT|VT_VECTOR:
	case VT_UI1|VT_VECTOR:
	case VT_UI2|VT_VECTOR:
	case VT_UI4|VT_VECTOR:
	case VT_I8|VT_VECTOR:
	case VT_UI8|VT_VECTOR:
	case VT_LPSTR|VT_VECTOR:
	case VT_LPWSTR|VT_VECTOR:
	case VT_FILETIME|VT_VECTOR:
	case VT_CF|VT_VECTOR:
	case VT_CLSID|VT_VECTOR:
		return S_OK;
	}

	return STG_E_INVALIDPARAMETER;
}

// -------------------------------------------------------------------------
WINOLEAPI PropVariantCopy ( PROPVARIANT * pvarDest, const PROPVARIANT * pvarSrc )
{
	ULONG len;
	HRESULT hr;

	hr = PROPVARIANT_ValidateType(pvarSrc->vt);
	if (FAILED(hr))
		return hr;

	/* this will deal with most cases */
	*pvarDest = *pvarSrc;

	switch(pvarSrc->vt)
	{
	case VT_EMPTY:
	case VT_NULL:
	case VT_I1:
	case VT_UI1:
	case VT_I2:
	case VT_UI2:
	case VT_BOOL:
	case VT_DECIMAL:
	case VT_I4:
	case VT_UI4:
	case VT_R4:
	case VT_ERROR:
	case VT_I8:
	case VT_UI8:
	case VT_R8:
	case VT_CY:
	case VT_DATE:
	case VT_FILETIME:
		break;
	case VT_STREAM:
	case VT_STREAMED_OBJECT:
	case VT_STORAGE:
	case VT_STORED_OBJECT:
		((LPUNKNOWN)pvarDest->pStream)->AddRef();
		break;
	case VT_CLSID:
		pvarDest->puuid = (CLSID *)CoTaskMemAlloc(sizeof(CLSID));
		*pvarDest->puuid = *pvarSrc->puuid;
		break;
	case VT_LPSTR:
		if (pvarSrc->pszVal)
		{
			len = strlen(pvarSrc->pszVal);
			pvarDest->pszVal = (LPSTR)CoTaskMemAlloc((len + 1) * sizeof(CHAR));
			CopyMemory(pvarDest->pszVal, pvarSrc->pszVal, (len + 1) * sizeof(CHAR));
		}
		break;
	case VT_LPWSTR:
		if (pvarSrc->pwszVal)
		{
			len = xstrlen(pvarSrc->pwszVal);
			pvarDest->pwszVal = (LPWSTR)CoTaskMemAlloc((len + 1) * sizeof(WCHAR));
			CopyMemory(pvarDest->pwszVal, pvarSrc->pwszVal, (len + 1) * sizeof(WCHAR));
		}
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
		if (pvarSrc->blob.pBlobData)
		{
			len = pvarSrc->blob.cbSize;
			pvarDest->blob.pBlobData = (BYTE *)CoTaskMemAlloc(len);
			CopyMemory(pvarDest->blob.pBlobData, pvarSrc->blob.pBlobData, len);
		}
		break;
	case VT_BSTR:
		pvarDest->bstrVal = SysAllocString(pvarSrc->bstrVal);
		break;
	case VT_CF:
		if (pvarSrc->pclipdata)
		{
			len = pvarSrc->pclipdata->cbSize - sizeof(pvarSrc->pclipdata->ulClipFmt);
			pvarDest->pclipdata = (CLIPDATA*)CoTaskMemAlloc(sizeof (CLIPDATA));
			pvarDest->pclipdata->cbSize = pvarSrc->pclipdata->cbSize;
			pvarDest->pclipdata->ulClipFmt = pvarSrc->pclipdata->ulClipFmt;
			pvarDest->pclipdata->pClipData = (BYTE *)CoTaskMemAlloc(len);
			CopyMemory(pvarDest->pclipdata->pClipData, pvarSrc->pclipdata->pClipData, len);
		}
		break;
	default:
		if (pvarSrc->vt & VT_VECTOR)
		{
			int elemSize;
			ULONG i;

			switch(pvarSrc->vt & ~VT_VECTOR)
			{
			case VT_I1:		elemSize = sizeof(pvarSrc->cVal);	break;
			case VT_UI1:	elemSize = sizeof(pvarSrc->bVal);	break;
			case VT_I2:		elemSize = sizeof(pvarSrc->iVal);	break;
			case VT_UI2:	elemSize = sizeof(pvarSrc->uiVal);	break;
			case VT_BOOL:	elemSize = sizeof(pvarSrc->boolVal);break;
			case VT_I4:		elemSize = sizeof(pvarSrc->lVal);	break;
			case VT_UI4:	elemSize = sizeof(pvarSrc->ulVal);	break;
			case VT_R4:		elemSize = sizeof(pvarSrc->fltVal);	break;
			case VT_R8:		elemSize = sizeof(pvarSrc->dblVal);	break;
			case VT_ERROR:	elemSize = sizeof(pvarSrc->scode);	break;
			case VT_I8:		elemSize = sizeof(pvarSrc->hVal);	break;
			case VT_UI8:	elemSize = sizeof(pvarSrc->uhVal);	break;
			case VT_CY:		elemSize = sizeof(pvarSrc->cyVal);	break;
			case VT_DATE:	elemSize = sizeof(pvarSrc->date);	break;
			case VT_FILETIME:	elemSize = sizeof(pvarSrc->filetime);	break;
			case VT_CLSID:		elemSize = sizeof(*pvarSrc->puuid);		break;
			case VT_CF:			elemSize = sizeof(*pvarSrc->pclipdata);	break;
			case VT_BSTR:		elemSize = sizeof(pvarSrc->bstrVal);	break;
			case VT_LPSTR:		elemSize = sizeof(pvarSrc->pszVal);		break;
			case VT_LPWSTR:		elemSize = sizeof(pvarSrc->pwszVal);	break;
			case VT_VARIANT:	elemSize = sizeof(*pvarSrc->pvarVal);	break;

			default:
				return E_INVALIDARG;
			}
			len = pvarSrc->capropvar.cElems;
			pvarDest->capropvar.pElems = (PROPVARIANT *)CoTaskMemAlloc(len * elemSize);
			if (pvarSrc->vt == (VT_VECTOR | VT_VARIANT))
			{
				for (i = 0; i < len; i++)
					PropVariantCopy(&pvarDest->capropvar.pElems[i], &pvarSrc->capropvar.pElems[i]);
			}
			else if (pvarSrc->vt == (VT_VECTOR | VT_CF))
			{
				// FIXME: Copy clipformats;
			}
			else if (pvarSrc->vt == (VT_VECTOR | VT_BSTR))
			{
				for (i = 0; i < len; i++)
					pvarDest->cabstr.pElems[i] = SysAllocString(pvarSrc->cabstr.pElems[i]);
			}
			else if (pvarSrc->vt == (VT_VECTOR | VT_LPSTR))
			{
				size_t strLen;
				for (i = 0; i < len; i++)
				{
					strLen = strlen(pvarSrc->calpstr.pElems[i]) + 1;
					pvarDest->calpstr.pElems[i] = (LPSTR)CoTaskMemAlloc(strLen);
					memcpy(pvarDest->calpstr.pElems[i],
					 pvarSrc->calpstr.pElems[i], strLen);
				}
			}
			else if (pvarSrc->vt == (VT_VECTOR | VT_LPWSTR))
			{
				size_t strLen;
				for (i = 0; i < len; i++)
				{
					strLen = (xstrlen(pvarSrc->calpwstr.pElems[i]) + 1) * sizeof(WCHAR);
					pvarDest->calpstr.pElems[i] = (LPSTR)CoTaskMemAlloc(strLen);
					memcpy(pvarDest->calpstr.pElems[i], pvarSrc->calpstr.pElems[i], strLen);
				}
			}
			else
				CopyMemory(pvarDest->capropvar.pElems, pvarSrc->capropvar.pElems, len * elemSize);
		}
	}

	return S_OK;

}

WINOLEAPI PropVariantClear ( PROPVARIANT * pvar )
{
	HRESULT hr;

	if (!pvar)
		return S_OK;

	hr = PROPVARIANT_ValidateType(pvar->vt);
	if (FAILED(hr))
		return hr;

	switch(pvar->vt)
	{
	case VT_EMPTY:
	case VT_NULL:
	case VT_I2:
	case VT_I4:
	case VT_R4:
	case VT_R8:
	case VT_CY:
	case VT_DATE:
	case VT_ERROR:
	case VT_BOOL:
	case VT_DECIMAL:
	case VT_UI1:
	case VT_UI2:
	case VT_UI4:
	case VT_I8:
	case VT_UI8:
	case VT_FILETIME:
		break;
	case VT_STREAM:
	case VT_STREAMED_OBJECT:
	case VT_STORAGE:
	case VT_STORED_OBJECT:
		if (pvar->pStream)
			pvar->pStream->Release();
		break;
	case VT_CLSID:
	case VT_LPSTR:
	case VT_LPWSTR:
		/* pick an arbitrary typed pointer - we don't care about the type
		 * as we are just freeing it */
		CoTaskMemFree(pvar->puuid);
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
		CoTaskMemFree(pvar->blob.pBlobData);
		break;
	case VT_BSTR:
		if (pvar->bstrVal)
			SysFreeString(pvar->bstrVal);
		break;
	case VT_CF:
		if (pvar->pclipdata)
		{
			OLE_FreeClipDataArray(1, pvar->pclipdata);
			CoTaskMemFree(pvar->pclipdata);
		}
		break;
	default:
		if (pvar->vt & VT_VECTOR)
		{
			ULONG i;

			switch (pvar->vt & ~VT_VECTOR)
			{
			case VT_VARIANT:
				FreePropVariantArray(pvar->capropvar.cElems, pvar->capropvar.pElems);
				break;
			case VT_CF:
				OLE_FreeClipDataArray(pvar->caclipdata.cElems, pvar->caclipdata.pElems);
				break;
			case VT_BSTR:
				for (i = 0; i < pvar->cabstr.cElems; i++)
					SysFreeString(pvar->cabstr.pElems[i]);
				break;
			case VT_LPSTR:
				for (i = 0; i < pvar->calpstr.cElems; i++)
					CoTaskMemFree(pvar->calpstr.pElems[i]);
				break;
			case VT_LPWSTR:
				for (i = 0; i < pvar->calpwstr.cElems; i++)
					CoTaskMemFree(pvar->calpwstr.pElems[i]);
				break;
			}
			if (pvar->vt & ~VT_VECTOR)
			{
				/* pick an arbitrary VT_VECTOR structure - they all have the same
				 * memory layout */
				CoTaskMemFree(pvar->capropvar.pElems);
			}
		}
	}

	ZeroMemory(pvar, sizeof(*pvar));

	return S_OK;
}

WINOLEAPI FreePropVariantArray(ULONG cVariants, /* [in] */
									PROPVARIANT *rgvars)    /* [in/out] */
{
	ULONG i;
	
	if (!rgvars)
		return E_INVALIDARG;

	for(i = 0; i < cVariants; i++)
		PropVariantClear(&rgvars[i]);

	return S_OK;
}

// -------------------------------------------------------------------------
void _force_link_propvariant() {}

