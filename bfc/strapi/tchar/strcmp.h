/***
*strcmp.h - routine to compare two xchar strings (for equal, less, or greater)
*
*       
*
*Purpose:
*       Compares two wide-character strings, determining their lexical order.
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
*strcmp - compare two xchar strings,
*        returning less than, equal to, or greater than
*
*Purpose:
*       strcmp compares two wide-character strings and returns an integer
*       to indicate whether the first is less than the second, the two are
*       equal, or whether the first is greater than the second.
*
*       Comparison is done xchar by xchar on an UNSIGNED basis, which is to
*       say that Null xchar(0) is less than any other character.
*
*Entry:
*       const xchar * src - string for left-hand side of comparison
*       const xchar * dst - string for right-hand side of comparison
*
*Exit:
*       returns -1 if src <  dst
*       returns  0 if src == dst
*       returns +1 if src >  dst
*
*Exceptions:
*
*******************************************************************************/

__template_xchar
int __xdecl __xcharfunc(strcmp)(
        const xchar * src,
        const xchar * dst
        )
{
        int ret = 0 ;

        while( ! (ret = (int)(*src - *dst)) && *dst)
                ++src, ++dst;

        if ( ret < 0 )
                ret = -1 ;
        else if ( ret > 0 )
                ret = 1 ;

        return( ret );
}

