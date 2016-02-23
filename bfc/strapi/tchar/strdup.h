/***
*strdup.h - duplicate a wide-character string in malloc'd memory
*
*      
*
*Purpose:
*       defines strdup() - grab new memory, and duplicate the string into it
*       (wide-character).
*
*******************************************************************************/

#pragma once

#ifndef __template_xchar
#define __template_xchar	// template <class xchar>
#endif

#ifndef __xdecl
#define __xdecl				// __cdecl
#endif

/***
*xchar *strdup(string) - duplicate string into malloc'd memory
*
*Purpose:
*       Allocates enough storage via malloc() for a copy of the
*       string, copies the string into the new memory, and returns
*       a pointer to it (wide-character).
*
*Entry:
*       xchar *string - string to copy into new memory
*
*Exit:
*       returns a pointer to the newly allocated storage with the
*       string in it.
*
*       returns NULL if enough memory could not be allocated, or
*       string was NULL.
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

__template_xchar
xchar * __xdecl __xcharfunc(strdup)(
        const xchar * string
        )
{
        if (!string)
                return(NULL);

		if (xchar* memory = (xchar *) malloc((__xcharfunc(strlen)(string)+1) * sizeof(xchar)))
                return __xcharfunc(strcpy)(memory,string);

        return(NULL);
}

