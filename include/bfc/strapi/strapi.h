/* -------------------------------------------------------------------------
//	File name		：	strapi.h
//	Author 			：	Austin
//	Create Time		：	2016-2-22 15:04:54
//	Description 	：	wchar api 
//
// -----------------------------------------------------------------------*/
#ifndef __STRAPI_H__
#define __STRAPI_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

#ifdef X_OS_WINDOWS
#include <wchar.h>
#else
#include "bfc/strapi/wchar.h"
#endif

// -------------------------------------------------------------------------
// -> wchar api function

#ifdef X_OS_WINDOWS
// Windows supported wchar api
#define xstrcat				wcscat
#define xstrncat			wcsncat
#define xstrcpy				wcscpy
#define xstrncpy			wcsncpy
#define xstrecpy			wcsecpy
#define xstrchr				wcschr
#define xstrrchr			wcsrchr
#define xstrlwr				wcslwr
#define xstrupr				wcsupr
#define xstrdup				wcsdup
#define xstrlen				wcslen

#define xstrcmp				wcscmp
#define xstricmp			wcsicmp
#define xstrncmp			wcsncmp
#define xstrnicmp			wcsnicmp
#define xstrcspn			wcscspn
#define xstrspn				wcsspn
#define xstrpbrk			wcspbrk

#define xvsprintf			_vsnwprintf
#define xsprintf			swprintf
#define xnsprintf			_snwprintf

#define toxlower			towlower
#define toxupper			towupper
#define itox				_itow
#define ltox				_ltow
#define ultox				_ultow

#define xsplitpath			_wsplitpath

#define xstrtok				wcstok
#define xstrstr				wcsstr

#define xstrtod				wcstod
#define xstrtol				wcstol
#define xstrtoul			wcstoul

#else
// Self realization api
#define xstrcat				_Xu2_strcat
#define xstrncat			_Xu2_strncat
#define xstrcpy				_Xu2_strcpy
#define xstrncpy			_Xu2_strncpy
#define xstrecpy			_Xu2_strecpy
#define xstrchr				_Xu2_strchr
#define xstrrchr			_Xu2_strrchr
#define xstrlwr				_Xu2_strlwr
#define xstrupr				_Xu2_strupr
#define xstrdup				_Xu2_strdup
#define xstrlen				_Xu2_strlen

#define xstrcmp				_Xu2_strcmp
#define xstricmp			_Xu2_stricmp
#define xstrncmp			_Xu2_strncmp
#define xstrnicmp			_Xu2_strnicmp

#define xstrcspn			_Xu2_strcspn
#define xstrspn				_Xu2_strspn
#define xstrpbrk			_Xu2_strpbrk

#define xvsprintf			_Xu2_vsprintf
#define xsprintf			_Xu2_sprintf
#define xnsprintf			_Xu2_nsprintf

#define toxlower			_Xu2_tolower
#define toxupper			_Xu2_toupper

#define itox				_Xu2_itoa
#define ltox				_Xu2_ltoa
#define ultox				_Xu2_ultoa

#define xsplitpath			_Xu2_splitpath

#define xstrtok				_Xu2_strtok
#define xstrstr				_Xu2_strstr

#define xstrtod				_Xu2_strtod
#define xstrtol				_Xu2_strtol
#define xstrtoul			_Xu2_strtoul

#endif

#ifndef X_OS_WINDOWS
#define stricmp strcasecmp
#define _stricmp strcasecmp
#define strnicmp strncasecmp
#define _strnicmp strncasecmp
#endif

// -------------------------------------------------------------------------

#endif // __STRAPI_H__
