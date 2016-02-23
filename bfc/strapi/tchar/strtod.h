/***
*strtod.h - string to double
*
*       
*
*Purpose:
*       defines strtod() - string to double
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
*double strtod(nptr, endptr) - convert wide string to double
*
*Purpose:
*       strtod recognizes an optional string of tabs and spaces,
*       then an optional sign, then a string of digits optionally
*       containing a decimal point, then an optional e or E followed
*       by an optionally signed integer, and converts all this to
*       to a floating point number.  The first unrecognized
*       character ends the string, and is pointed to by endptr.
*
*Entry:
*       nptr - pointer to wide string to convert
*
*Exit:
*       returns value of wide character string
*       wchar_t **endptr - if not NULL, points to character which stopped
*               the scan
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

__template_xchar
double __xdecl __xcharfunc(strtod)(
		const xchar * nptr,
		xchar ** endptr
		)
{
	long double result = 0.0;	/* result */
	int exp = 0;				/* exponent */
	long double scale;			/* scale */
	int sign = 1;				/* sign +- 1.0 */
	int exp_sign = 1;			/* exponent sign +- 1.0 */
	int flags = 0;				/* used for validation */

	/* validate parameters */
	if (endptr != NULL)
		*endptr = (xchar *)nptr;

	if (nptr == NULL)
		return 0.0;

	/* scan past leading space/tab characters */
	while ((*nptr == u' ') || (*nptr == u'\t'))
		nptr++;

	/* scan sign character */
	if (*nptr == u'+')
		nptr++;
	else if (*nptr == u'-')
	{
		sign = -1;
		nptr++;
	}

	/* scan whole part */
	while ((*nptr >= u'0') && (*nptr <= u'9'))
	{
		flags |= 1;
		result *= 10.0;
		result += *nptr - u'0';
		nptr++;
	}

	/* scan radix point and decimal */
	if (*nptr == u'.')
	{
		scale = 0.1L;
		nptr++;
		while ((*nptr >= u'0') && (*nptr <= u'9'))
		{
			flags |= 2;
			result +=scale * (*nptr - u'0');
			nptr++;
			scale *= 0.1L;
		}
	}

	/* has no valid character */
	if (flags == 0)
	{
		return 0;
	}

	/* scan exponent */
	if ((*nptr == u'e') || (*nptr == u'E'))
	{
		nptr++;
		if (*nptr == u'+')
			nptr++;
		else if (*nptr == u'-')
		{
			nptr++;
			exp_sign = -1;
		}
		if ((*nptr < u'0') || (*nptr > u'9'))
		{
			if (endptr)
				*endptr = (xchar *)nptr;
			return result;
		}

		while ((*nptr >= u'0') && (*nptr <= u'9'))
		{
			exp *= 10;
			exp += *nptr - u'0';
			nptr++;
		}
	}

	if (exp_sign < 0)
		for (int i=1; i<=exp; i++)
			result *= 0.1L;
	else
		for (int i=1; i<=exp; i++)
			result *= 10.0;

	if (endptr)
		*endptr = (xchar *)nptr;
	return result * sign;
}
