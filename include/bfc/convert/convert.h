// -------------------------------------------------------------------------- //
//	File name		：	convert.h
//	Author 			：	Austin
//	Create Time		：	2016-2-22 11:28:20
//	Description 	：	Convert String 
//
// -------------------------------------------------------------------------- //

#ifndef __CONVERT_H__
#define __CONVERT_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------- //
// -> Convert String

// UTF-16 to UTF-8 string
STDAPI_(int) WideToMulti(const LPCWSTR szSrc, int nSrcSize, char* strDest, int nDestSize);

// UTF-8 to UTF-16 string
STDAPI_(int) MultiToWide(const char* strSrc, int nSrcSize, LPCWSTR szDest, int nDestSize);

// -------------------------------------------------------------------------- //

#endif // __CONVERT_H__
