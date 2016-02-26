/* -------------------------------------------------------------------------
//	File name		：	transcode.h
//	Author 			：	Austin
//	Create Time		：	2016-2-26 12:41:10
//	Description 	：	Win32LCPTranscoder on Windows platform 
//
// -----------------------------------------------------------------------*/
#ifndef __WIN32_TRANSCODE_H__
#define __WIN32_TRANSCODE_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------
// --> Win32LCPTranscoder

class Win32LCPTranscoder
{
public:
	static char* transcode(const WCHAR* const toTranscode)
	{
		if (!toTranscode)
			return 0;

		char* retVal = 0;
		if (*toTranscode)
		{
			// Calc the needed size
			const unsigned int neededLen = ::wcstombs(0, toTranscode, 0);
			if (neededLen == (unsigned int)-1)
				return 0;

			// Allocate a buffer of that size plus one for the null and transcode
			retVal = new char[neededLen + 1];
			::wcstombs(retVal, toTranscode, neededLen + 1);

			// And cap it off anyway just to make sure
			retVal[neededLen] = 0;
		}
		else
		{
			retVal = new char[1];
			retVal[0] = 0;
		}
		return retVal;
	}

	static WCHAR* transcode(const char* const toTranscode)
	{
		if (!toTranscode)
			return 0;

		WCHAR* retVal = 0;
		if (*toTranscode)
		{
			// Calculate the buffer size required
			const unsigned int neededLen = ::mbstowcs(0, toTranscode, 0);
			if (neededLen == (unsigned int)-1)
				return 0;

			// Allocate a buffer of that size plus one for the null and transcode
			retVal = new WCHAR[neededLen + 1];
			::mbstowcs(retVal, toTranscode, neededLen + 1);

			// Cap it off just to make sure. We are so paranoid!
			retVal[neededLen] = 0;
		}
		else
		{
			retVal = new WCHAR[1];
			retVal[0] = 0;
		}
		return retVal;
	}
};

// -------------------------------------------------------------------------

#endif /* __WIN32_TRANSCODE_H__ */
