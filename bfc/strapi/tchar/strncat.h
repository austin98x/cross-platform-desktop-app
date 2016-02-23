/***
*strncat.h - append n chars of string to new string
*
*       
*
*Purpose:
*       defines strncat() - appends n characters of string onto
*       end of other string
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
*wchar_t *strncat(front, back, count) - append count chars of back onto front
*
*Purpose:
*       Appends at most count characters of the string back onto the
*       end of front, and ALWAYS terminates with a null character.
*       If count is greater than the length of back, the length of back
*       is used instead.  (Unlike wcsncpy, this routine does not pad out
*       to count characters).
*
*Entry:
*       wchar_t *front - string to append onto
*       wchar_t *back - string to append
*       size_t count - count of max characters to append
*
*Exit:
*       returns a pointer to string appended onto (front).
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/


__template_xchar
xchar * __xdecl __xcharfunc(strncat)(xchar * dst, const xchar* src, size_t count)
{
	xchar *start = dst;

	while (*dst++)
		;
	dst--;

	while (count--)
		if (!(*dst++ = *src++))
			return(start);

	*dst = L'\0';
	return(start);
}

