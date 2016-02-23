/***
*strecpy.h - contains strecpy() routine
*
*
*
*Purpose:
*       defines strecpy() - copy pszSrc string to pszDest string
*
*******************************************************************************/

#pragma once

#ifndef __template_xchar
#define __template_xchar	// template <class xchar>
#endif

#ifndef __xdecl
#define __xdecl				// __cdecl
#endif

// -------------------------------------------------------------------------

__template_xchar
xchar* __xdecl __xcharfunc(strecpy)(xchar* pszDest, const xchar* pszSrc)
{
	while ((*pszDest = *pszSrc) != 0)
	{
		++pszDest;
		++pszSrc;
	}
	return pszDest;
}

// -------------------------------------------------------------------------
