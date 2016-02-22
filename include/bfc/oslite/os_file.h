// -------------------------------------------------------------------------- //
//	File name		：	os_file.h
//	Author 			：	Austin
//	Create Time		：	2016-2-22 10:27:14
//	Description 	：	File Part 
//
// -------------------------------------------------------------------------- //

#ifndef __OS_FILE_H__
#define __OS_FILE_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------- //
// -> File Part
STDAPI _Xaccess(LPCWSTR szFileW, int nMode);
STDAPI _Xchmod(LPCWSTR szFileW, int mode);

STDAPI _Xremove(LPCWSTR szFileW);
STDAPI _Xrename(LPCWSTR szOldFileW, LPCWSTR szNewFileW);

STDAPI_(FILE*) _Xfopen(LPCWSTR szFileW, LPCWSTR mode);
STDAPI_(FILE*) _Xfsopen(LPCWSTR szFileW, LPCWSTR mode, int shflag);

STDAPI_(HANDLE) _XFileLockWrite(LPCWSTR szFileW);
STDAPI _XFileUnlockWrite(HANDLE h);
STDAPI_(VOID) _XFlushFileBuffers(LPCWSTR szFileW);
STDAPI_(BOOL) _XFileCanLockForRW(LPCWSTR szFileW, BOOL bWrite);

// -------------------------------------------------------------------------- //

#endif // __OS_FILE_H__
