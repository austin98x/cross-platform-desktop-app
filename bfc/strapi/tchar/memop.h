/***
*memop.h - contains memchr()  memcmp() memcpy() memmove() memset() routines
*
*
*
*Purpose:
*       To provide support for memory operation
*
*******************************************************************************/

#pragma once

#ifndef __template_xchar_inline
#define __template_xchar_inline	 template <class xchar> inline
#endif

#ifndef __xdecl
#define __xdecl		// __cdecl
#endif

__template_xchar_inline
const xchar* __xdecl __xcharfunc(memchr)(const xchar *_S, xchar _C, size_t _N)
        {for (; 0 < _N; ++_S, --_N)
                if (*_S == _C)
                        return (_S);
        return (0); }

__template_xchar_inline 
int __xdecl __xcharfunc(memcmp)(const xchar *_S1, const xchar *_S2, size_t _N)
        {for (; 0 < _N; ++_S1, ++_S2, --_N)
                if (*_S1 != *_S2)
                        return (*_S1 < *_S2 ? -1 : +1);
        return (0); }

__template_xchar_inline 
xchar* __xdecl __xcharfunc(memcpy)(xchar *_S1, const xchar *_S2, size_t _N)
        {xchar *_Su1 = _S1;
        for (; 0 < _N; ++_Su1, ++_S2, --_N)
                *_Su1 = *_S2;
        return (_S1); }

__template_xchar_inline 
xchar* __xdecl __xcharfunc(memmove)(xchar *_S1, const xchar *_S2, size_t _N)
        {xchar *_Su1 = _S1;
        if (_S2 < _Su1 && _Su1 < _S2 + _N)
                for (_Su1 += _N, _S2 += _N; 0 < _N; --_N)
                        *--_Su1 = *--_S2;
        else
                for (; 0 < _N; --_N)
                        *_Su1++ = *_S2++;
        return (_S1); }

__template_xchar_inline 
xchar* __xdecl __xcharfunc(memset)(xchar *_S, xchar _C, size_t _N)
        {xchar *_Su = _S;
        for (; 0 < _N; ++_Su, --_N)
                *_Su = _C;
        return (_S); }
