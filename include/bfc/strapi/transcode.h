/* -------------------------------------------------------------------------
//	File name		：	transcode.h
//	Author 			：	Austin
//	Create Time		：	2016-2-26 12:41:10
//	Description 	：	StringTranscoder 
//
// -----------------------------------------------------------------------*/
#ifndef __TRANSCODE_H__
#define __TRANSCODE_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

#if defined(X_OS_WINDOWS)
#  include "win32/transcode.h"
#  define LCPTranscoder Win32LCPTranscoder
#elif defined(X_OS_LINUX)
#  include "iconv/transcode.h"
#  define LCPTranscoder IconvLCPTranscoder
#else
#  error "Unknonw Platform!!!"
#endif

// -------------------------------------------------------------------------
// --> StringTranscoder

_BFC_BEGIN

class StringTranscoder : public LCPTranscoder
{
public:
	static unsigned int stringLen(const WCHAR* const src)
	{
		const WCHAR* end = src;
		while (*end)
			++end;
		return end - src;
	}

	static bool copyNString(WCHAR* const target,
							const WCHAR* const src,
							const unsigned int maxChars)
	{
		WCHAR* outPtr = target;
		const WCHAR* srcPtr = src;
		const WCHAR* endPtr = target + maxChars - 1;

		while (*srcPtr && (outPtr <= endPtr))
			*outPtr++ = *srcPtr++;

		// Cap it off here
		*outPtr = 0;

		// Return whether we copied it all or hit the max
		return (*srcPtr == 0);
	}

	static void copyString(WCHAR* pszOut, const WCHAR* pszIn)
	{
		while (*pszIn)
			*pszOut++ = *pszIn++;
		*pszOut = 0;
	}
};

_BFC_END

// -------------------------------------------------------------------------

#endif /* __TRANSCODE_H__ */
