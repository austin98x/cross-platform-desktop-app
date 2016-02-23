/* -------------------------------------------------------------------------
//	File name		：	strapi.cpp
//	Author 			：	Austin
//	Create Time		：	2016-2-23 10:11:54
//	Description 	：	Impl of _Xu2_xxx functions
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
typedef WCHAR xchar;

#define __template_xchar		EXTERN_C
#define __template_xchar_inline	__template_xchar
#define __xdecl					__stdcall
#define __xcharfunc(name)		__ ## name

#ifndef X_CC_VC
#include "sys/types.h"
#endif

#include "strapi/tchar/memop.h"
#include "strapi/tchar/strlen.h"
#include "strapi/tchar/strcat.h"
#include "strapi/tchar/strncpy.h"
#include "strapi/tchar/strecpy.h"
#include "strapi/tchar/strchr.h"
#include "strapi/tchar/strrchr.h"
#include "strapi/tchar/strcmp.h"
#include "strapi/tchar/strcspn.h"
#include "strapi/tchar/strspn.h"
#include "strapi/tchar/strdup.h"
#include "strapi/tchar/strpbrk.h"
#include "strapi/tchar/stricmp.h"
#include "strapi/tchar/strncmp.h"
#include "strapi/tchar/strnicmp.h"
#include "strapi/tchar/strlwr.h"
#include "strapi/tchar/strupr.h"
#include "strapi/tchar/makepath.h"
#include "strapi/tchar/splitpath.h"
#include "strapi/tchar/itoa.h"
#include "strapi/tchar/strtod.h"
#include "strapi/tchar/strtol.h"
#include "strapi/tchar/strstr.h"
#include "strapi/tchar/strncat.h"
#include "strapi/tchar/strtok.h"

EXPORTAPI_(int) _Xu2_memcmp(const WCHAR* first, const WCHAR* second, size_t count)
{
	return __memcmp(first, second, count);
}

EXPORTAPI_(WCHAR*) _Xu2_memcpy(WCHAR* dest, const WCHAR* src, size_t count)
{
	return __memcpy(dest, src, count);
}

EXPORTAPI_(WCHAR*) _Xu2_memmove(WCHAR* dest, const WCHAR* src, size_t count)
{
	return __memmove(dest, src, count);
}

EXPORTAPI_(WCHAR*) _Xu2_memset(WCHAR* dest, WCHAR ch, size_t count)
{
	return __memset(dest, ch, count);
}

EXPORTAPI_(const WCHAR*) _Xu2_memchr(const WCHAR* string, WCHAR ch, size_t count)
{
	return __memchr(string, ch, count);
}

EXPORTAPI_(WCHAR*) _Xu2_strcat(WCHAR* dest, const WCHAR* src)
{
	return __strcat(dest, src);
}

EXPORTAPI_(WCHAR*) _Kso_strncat(WCHAR* dest, const WCHAR* src, size_t count)
{
	return __strncat(dest, src, count);
}

EXPORTAPI_(WCHAR*) _Xu2_strcpy(WCHAR* dest, const WCHAR* src)
{
	return __strcpy(dest, src);
}

EXPORTAPI_(WCHAR*) _Xu2_strncpy(WCHAR* dest, const WCHAR* src, size_t count)
{
	return __strncpy(dest, src, count);
}

EXPORTAPI_(WCHAR*) _Xu2_strecpy(WCHAR* dest, const WCHAR* src)
{
	return __strecpy(dest, src);
}

EXPORTAPI_(WCHAR*) _Xu2_strchr(const WCHAR* string, WCHAR ch)
{
	return __strchr(string, ch);
}

EXPORTAPI_(WCHAR*) _Xu2_strrchr(const WCHAR* string, WCHAR ch)
{
	return __strrchr(string, ch);
}

EXPORTAPI_(WCHAR*) _Xu2_strlwr(WCHAR* string)
{
	return __strlwr(string);
}

EXPORTAPI_(WCHAR*) _Xu2_strupr(WCHAR* string)
{
	return __strupr(string);
}

EXPORTAPI_(WCHAR*) _Xu2_strdup(const WCHAR* string)
{
	if (!string)
		return(NULL);

	if (xchar* memory = (xchar *) malloc((__strlen(string)+1) * sizeof(xchar)))
		return __strcpy(memory,string);

	return(NULL);
}

EXPORTAPI_(size_t) _Xu2_strlen(const WCHAR* string)
{
	if (NULL == string)
		return 0;
	return __strlen(string);
}

EXPORTAPI_(int) _Xu2_strcmp(const WCHAR* first, const WCHAR* second)
{
	return __strcmp(first, second);
}

EXPORTAPI_(int) _Xu2_stricmp(const WCHAR* first, const WCHAR* second)
{
	return __stricmp(first, second);
}

EXPORTAPI_(int) _Xu2_strncmp(const WCHAR* first, const WCHAR* second, size_t count)
{
	return __strncmp(first, second, count);
}

EXPORTAPI_(int) _Xu2_strnicmp(const WCHAR* first, const WCHAR* second, size_t count)
{
	return __strnicmp(first, second, count);
}

EXPORTAPI_(size_t) _Xu2_strcspn(const WCHAR* string, const WCHAR* control)
{
	return __strcspn(string, control);
}

EXPORTAPI_(size_t)_Xu2_strspn(const WCHAR* string, const WCHAR* control)
{
	return __strspn(string, control);
}

EXPORTAPI_(WCHAR*) _Xu2_strpbrk(const WCHAR *string, const WCHAR *control)
{
	return __strpbrk(string, control);
}

EXPORTAPI_(void) _Xu2_splitpath(const WCHAR* path, WCHAR* drive, WCHAR* dir, WCHAR* fname, WCHAR* ext)
{
	return __splitpath(path, drive, dir, fname, ext);
}

EXPORTAPI_(WCHAR*) _Xu2_strtok(WCHAR* token, const WCHAR* delimit)
{
	return __strtok(token, delimit);
}

EXPORTAPI_(WCHAR*) _Xu2_itoa(int val, WCHAR* string, int radix)
{
	return __itoa(val, string, radix);
}

EXPORTAPI_(WCHAR*) _Xu2_ltoa(long val, WCHAR* string, int radix)
{
	return __ltoa(val, string, radix);
}

EXPORTAPI_(WCHAR*) _Xu2_ultoa(unsigned long val, WCHAR* string, int radix)
{
	return __ultoa(val, string, radix);
}

EXPORTAPI_(WCHAR*) _Xu2_strstr(const WCHAR* str1, const WCHAR* str2)
{
	return __strstr(str1, str2);
}

EXPORTAPI_(double) _Xu2_strtod(const WCHAR* string, WCHAR** end)
{
	return __strtod(string, end);
}

EXPORTAPI_(long) _Xu2_strtol(const WCHAR* string, WCHAR** end, int base)
{
	return __strtol(string, end, base);
}

EXPORTAPI_(unsigned long) _Xu2_strtoul(const WCHAR* string, WCHAR** end, int base)
{
	return __strtoul(string, end, base);
}

EXPORTAPI_(WCHAR) _Xu2_tolower(WCHAR ch)
{
	if ((ch >= __Xc('A')) && (ch <= __Xc('Z')))
		ch += __Xc('a') - __Xc('A');

	return ch;
}

EXPORTAPI_(WCHAR) _Xu2_toupper(WCHAR ch)
{
	if ((ch >= __Xc('a')) && (ch <= __Xc('z')))
		ch += __Xc('A') - __Xc('a');

	return ch;
}

// -------------------------------------------------------------------------
