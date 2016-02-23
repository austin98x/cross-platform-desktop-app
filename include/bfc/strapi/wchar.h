/* -------------------------------------------------------------------------
//	File name		：	wchar.h
//	Author 			：	Austin
//	Create Time		：	2016-2-22 15:16:54
//	Description 	：	self realization api 
//
// -----------------------------------------------------------------------*/
#ifndef __WCHAR_H__
#define __WCHAR_H__

// =========================================================================
// WCHAR char type concept

#define WCHARAPI        EXTERN_C HRESULT STDAPICALLTYPE
#define WCHARAPI_(type) EXTERN_C type STDAPICALLTYPE

WCHARAPI_(int) _Xu2_memcmp(const WCHAR* first, const WCHAR* second, size_t count);
WCHARAPI_(WCHAR*) _Xu2_memcpy(WCHAR* dest, const WCHAR* src, size_t count);
WCHARAPI_(WCHAR*) _Xu2_memmove(WCHAR* dest, const WCHAR* src, size_t count);
WCHARAPI_(WCHAR*) _Xu2_memset(WCHAR* dest, WCHAR ch, size_t count);
const WCHAR* __stdcall _Xu2_memchr(const WCHAR* string, WCHAR ch, size_t count);

WCHARAPI_(WCHAR*) _Xu2_strcat(WCHAR* dest, const WCHAR* src);
WCHARAPI_(WCHAR*) _Xu2_strncat(WCHAR* dest, const WCHAR* src, size_t count);
WCHARAPI_(WCHAR*) _Xu2_strcpy(WCHAR* dest, const WCHAR* src);
WCHARAPI_(WCHAR*) _Xu2_strncpy(WCHAR* dest, const WCHAR* src, size_t count);
WCHARAPI_(WCHAR*) _Xu2_strecpy(WCHAR* dest, const WCHAR* src);
WCHARAPI_(WCHAR*) _Xu2_strchr(const WCHAR* string, WCHAR ch);
WCHARAPI_(WCHAR*) _Xu2_strrchr(const WCHAR* string, WCHAR ch);
WCHARAPI_(WCHAR*) _Xu2_strlwr(WCHAR* string);
WCHARAPI_(WCHAR*) _Xu2_strupr(WCHAR* string);
WCHARAPI_(WCHAR*) _Xu2_strdup(const WCHAR* string);
WCHARAPI_(size_t) _Xu2_strlen(const WCHAR* string);

WCHARAPI_(int) _Xu2_strcmp(const WCHAR* first, const WCHAR* second);
WCHARAPI_(int) _Xu2_stricmp(const WCHAR* first, const WCHAR* second);
WCHARAPI_(int) _Xu2_strncmp(const WCHAR* first, const WCHAR* second, size_t count);
WCHARAPI_(int) _Xu2_strnicmp(const WCHAR* first, const WCHAR* second, size_t count);

WCHARAPI_(size_t) _Xu2_strcspn(const WCHAR* string, const WCHAR* control);
WCHARAPI_(size_t) _Xu2_strspn(const WCHAR* string, const WCHAR* control);
WCHARAPI_(WCHAR*) _Xu2_strpbrk(const WCHAR* string, const WCHAR* control);

WCHARAPI_(WCHAR) _Xu2_tolower(WCHAR ch);
WCHARAPI_(WCHAR)_Xu2_toupper(WCHAR ch);

WCHARAPI_(WCHAR*) _Xu2_itoa(int val, WCHAR* string, int radix);
WCHARAPI_(WCHAR*) _Xu2_ltoa(long val, WCHAR* string, int radix);
WCHARAPI_(WCHAR*) _Xu2_ultoa(unsigned long val, WCHAR* string, int radix);

WCHARAPI_(void) _Xu2_splitpath(const WCHAR* path, WCHAR* drive, WCHAR* dir, WCHAR* fname, WCHAR* ext);

WCHARAPI_(WCHAR*) _Xu2_strtok(WCHAR* token, const WCHAR* delimit);
WCHARAPI_(WCHAR*) _Xu2_strstr(const WCHAR* str1, const WCHAR* str2);

WCHARAPI_(double) _Xu2_strtod(const WCHAR* string, WCHAR** end);
WCHARAPI_(long) _Xu2_strtol(const WCHAR* string, WCHAR** end, int base);
WCHARAPI_(unsigned long) _Xu2_strtoul(const WCHAR* string, WCHAR** end, int base);

#endif // __WCHAR_H__
