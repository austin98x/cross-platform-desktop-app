/* -------------------------------------------------------------------------
//	File name		：	bstr.cpp
//	Author 			：	Austin
//	Create Time		：	2016-5-23 15:15:11
//	Description 	：	Impl of BSTR functions
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
EXPORTAPI_(BSTR) _XSysAllocString(const OLECHAR* pwcs)
{
	if (pwcs)
	{
		int cch = xstrlen(pwcs);
		if (cch >= 0)
		{
			int cb = (cch + 1) * sizeof(OLECHAR);
			BSTR bstr = (BSTR)CoTaskMemAlloc(cb);
			CopyMemory(bstr, pwcs, cb);
			return (BSTR)bstr;
		}
	}

	return 0;
}

EXPORTAPI_(INT) _XSysReAllocString(BSTR* pbstr, const OLECHAR* pwcs)
{
	if (pwcs)
	{
		int cch = xstrlen(pwcs);
		if (cch >= 0)
		{
			int cb = (cch + 1) * sizeof(OLECHAR);
			BSTR bstr = (BSTR)CoTaskMemRealloc(*pbstr, cb);
			CopyMemory(bstr, pwcs, cb);
			*pbstr = bstr;
			return TRUE;
		}
	}

	CoTaskMemFree(*pbstr);
	*pbstr = NULL;
	return TRUE;
}

EXPORTAPI_(BSTR) _XSysAllocStringLen(const OLECHAR* pch, UINT cch)
{
	int cb = (cch + 1) * sizeof(OLECHAR);
	BSTR bstr = (BSTR)CoTaskMemAlloc(cb);
	if (pch)
		CopyMemory(bstr, pch, cb - sizeof(OLECHAR));
	bstr[cch] = 0;
	return (BSTR)bstr;
}

EXPORTAPI_(BSTR) _XSysAllocStringByteLen(LPCSTR psz, UINT cch)
{
	int cb = cch + (cch & 0x1) + sizeof(OLECHAR);
	BSTR bstr = (BSTR)CoTaskMemAlloc(cb);
	if (psz)
		CopyMemory(bstr, psz, cb - sizeof(OLECHAR));
	bstr[(cb >> 1) - 1] = 0;
	return (BSTR)bstr;
}

EXPORTAPI_(INT) _XSysReAllocStringLen(BSTR* pbstr, const OLECHAR* pch, UINT cch)
{
	int cb = (cch + 1) * sizeof(OLECHAR);
	BSTR bstr = (BSTR)CoTaskMemRealloc(*pbstr, cb);
	*pbstr = bstr;
	if (pch)
		CopyMemory(bstr, pch, cb - sizeof(OLECHAR));
	bstr[cch] = 0;
	return TRUE;
}

EXPORTAPI_(void) _XSysFreeString(BSTR bstr)
{
	CoTaskMemFree(bstr);
}

EXPORTAPI_(UINT) _XSysStringLen(BSTR bstr)
{
	if (bstr)
		return CoTaskMemSize(bstr) / sizeof(OLECHAR) - 1;
	return 0;
}

EXPORTAPI_(UINT) _XSysStringByteLen(BSTR bstr)
{
	if (bstr)
		return CoTaskMemSize(bstr) - 1;
	return 0;
}

// -------------------------------------------------------------------------
void _force_link_bstr() {}

