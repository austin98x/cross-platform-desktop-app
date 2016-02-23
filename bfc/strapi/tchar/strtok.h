/***
*strtok.h - tokenize a wide-character string with given delimiters
*
*       
*
*Purpose:
*       defines strtok() - breaks wide-character string into series of token
*       via repeated calls.
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
*xchar *strtok(string, control) - tokenize string with delimiter in control
*       (wide-characters)
*
*Purpose:
*       strtok considers the string to consist of a sequence of zero or more
*       text tokens separated by spans of one or more control chars. the first
*       call, with string specified, returns a pointer to the first xchar of
*       the first token, and will write a null xchar into string immediately
*       following the returned token. subsequent calls with zero for the first
*       argument (string) will work thru the string until no tokens remain. the
*       control string may be different from call to call. when no tokens remain
*       in string a NULL pointer is returned. remember the control chars with a
*       bit map, one bit per xchar. the null xchar is always a control char
*       (wide-characters).
*
*Entry:
*       xchar *string - xchar string to tokenize, or NULL to get next token
*       xchar *control - xchar string of characters to use as delimiters
*
*Exit:
*       returns pointer to first token in string, or if string
*       was NULL, to next token
*       returns NULL when no more tokens remain.
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

__template_xchar
xchar * __xdecl __xcharfunc(strtok)(
        xchar * string,
        const xchar* control
        )
{
        xchar *token;
        const xchar *ctl;

#ifdef _MT
        _ptiddata ptd = _getptd();
#else  /* _MT */
        static xchar *nextoken;
#endif  /* _MT */

        /* If string==NULL, continue with previous string */
        if (!string)

#ifdef _MT
                string = ptd->_wtoken;
#else  /* _MT */
                string = nextoken;
#endif  /* _MT */

        /* Find beginning of token (skip over leading delimiters). Note that
         * there is no token iff this loop sets string to point to the terminal
         * null (*string == '\0') */

        while (*string) {
                for (ctl=control; *ctl && *ctl != *string; ctl++)
                        ;
                if (!*ctl) break;
                string++;
        }

        token = string;

        /* Find the end of the token. If it is not the end of the string,
         * put a null there. */
        for ( ; *string ; string++ ) {
                for (ctl=control; *ctl && *ctl != *string; ctl++)
                        ;
                if (*ctl) {
                        *string++ = '\0';
                        break;
                }
        }

        /* Update nextoken (or the corresponding field in the per-thread data
         * structure */
#ifdef _MT
        ptd->_wtoken = string;
#else  /* _MT */
        nextoken = string;
#endif  /* _MT */

        /* Determine if a token has been found. */
        if ( token == string )
                return NULL;
        else
                return token;
}

