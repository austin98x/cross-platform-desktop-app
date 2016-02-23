/***
*strpbrk.h - contains strpbrk() routine
*
*
*
*Purpose:
*       defines strpbrk()
*
*******************************************************************************/

#pragma once

#ifndef __template_xchar
#define __template_xchar	// template <class xchar>
#endif

#ifndef __xdecl
#define __xdecl				// __cdecl
#endif

xchar * __xdecl __xcharfunc(strpbrk) (
		const xchar * string,
		const xchar * control
		)
{
	/* 1st char in control string stops search */
	while (*string)
	{
		for (xchar *wcset = (xchar *) control; *wcset; wcset++)
		{
			if (*wcset == *string)
				return (xchar *) string;
		}
		string++;
	}

	return NULL;
}
