/* -------------------------------------------------------------------------
//	File name		：	cocreateguid.cpp
//	Author 			：	Austin
//	Create Time		：	2017-3-30 10:15:11
//	Description 	：	Impl of _XCoCreateGuid function
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------

#if defined(X_OS_WINDOWS)
#define _S_tick()			GetTickCount()
#else
#define _S_tick()			time(NULL)
#endif

#define _S_rand_value()		( ( rand() << 16 ) ^ rand() )

// -------------------------------------------------------------------------

inline STDMETHODIMP_(int) _S_srand()
{
	srand( _S_tick() );
	for (int n = (rand() & 7) + 2; n--;)
	{
		srand(rand());
	}
	return 0;
}

inline STDMETHODIMP_(DWORD) _S_computer_value()
{
	const char* sz = getenv("HOME");
	DWORD h = _S_rand_value();
	if (!sz)
	{
		sz = getenv("PATH");
		if (!sz)
			return h;
	}
	while (*sz)
		h = h*5 + *sz++;
	return h;
}

// -------------------------------------------------------------------------
EXPORTAPI _XCoCreateGuid(GUID FAR* pguid)
{
	static int _s_srand = _S_srand();
	
	DWORD* pdw = (DWORD*)pguid;
	pdw[0] = time(NULL) ^ _S_rand_value();
	pdw[1] = _S_computer_value();
	pdw[2] = time(NULL);
	pdw[3] = _S_rand_value();
	
	return S_OK;
}

// -------------------------------------------------------------------------
void _force_link_kskern_cocreateguid() {}

