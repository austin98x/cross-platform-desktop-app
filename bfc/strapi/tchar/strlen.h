/***
*strlen.h - contains strlen() routine
*
*       
*
*Purpose:
*       strlen returns the length of a null-terminated wide-character string,
*       not including the null xchar itself.
*
*******************************************************************************/

#pragma once

#ifndef __template_xchar
#define __template_xchar	template <class xchar>
#endif

#ifndef __xdecl
#define __xdecl				// __cdecl
#endif

/***
*strlen - return the length of a null-terminated wide-character string
*
*Purpose:
*       Finds the length in xchar's of the given string, not including
*       the final null xchar (wide-characters).
*
*Entry:
*       const xchar * wcs - string whose length is to be computed
*
*Exit:
*       length of the string "wcs", exclusive of the final null xchar
*
*Exceptions:
*
*******************************************************************************/

__template_xchar
size_t __xdecl __xcharfunc(strlen)(
        const xchar * wcs
        )
{
		const xchar *eos = wcs;

		while( *eos++ ) ;

		return( (size_t)(eos - wcs - 1) );
}

