/* -------------------------------------------------------------------------
//	File name		：	transcode.h
//	Author 			：	Austin
//	Create Time		：	2016-2-26 12:53:20
//	Description 	：	IconvLCPTranscoder on Linux platform 
//
// -----------------------------------------------------------------------*/
#ifndef __ICONV_TRANSCODE_H__
#define __ICONV_TRANSCODE_H__

#ifndef __BFC_INCLUDE__

#	error This file is not intended to be included separately

#endif

#include <wchar.h>
#include <string.h>

// -------------------------------------------------------------------------
// --> IconvLCPTranscoder

class IconvLCPTranscoder
{
public:
	typedef unsigned long UCS4Ch;

	enum
	{
		gTempBuffArraySize = 1024
	};

public:
	static unsigned int getWideCharLength(const WCHAR* const src)
	{
		const WCHAR* end = src;
		while (*end)
			++end;
		return end - src;
	}

	static UCS4Ch* toUCS4(const WCHAR* const toTranscode)
	{
		unsigned int wLent = getWideCharLength(toTranscode);

		UCS4Ch  tmpWideCharArr[gTempBuffArraySize];
		UCS4Ch* allocatedArray = 0;
		UCS4Ch* wideCharBuf = 0;

		if (wLent >= gTempBuffArraySize)
			wideCharBuf = allocatedArray = new UCS4Ch[wLent + 1];
		else
			wideCharBuf = tmpWideCharArr;

		for (unsigned int i = 0; i < wLent; i++)
		{
			wideCharBuf[i] = toTranscode[i];
		}
		wideCharBuf[wLent] = 0x00;

		return wideCharBuf;
	}

public:
	static char* transcode(const WCHAR* const toTranscode)
	{
		if (!toTranscode)
			return 0;

		char* retVal = 0;
		if (*toTranscode)
		{
			unsigned int  wLent = getWideCharLength(toTranscode);

			wchar_t tmpWideCharArr[gTempBuffArraySize];
			wchar_t* allocatedArray = 0;
			wchar_t* wideCharBuf = 0;

			if (wLent >= gTempBuffArraySize)
				wideCharBuf = allocatedArray = new wchar_t[wLent + 1];
			else
				wideCharBuf = tmpWideCharArr;

			for (unsigned int i = 0; i < wLent; i++)
			{
				wideCharBuf[i] = toTranscode[i];
			}
			wideCharBuf[wLent] = 0x00;

			// Calc the needed size.
			const size_t neededLen = ::wcstombs(NULL, wideCharBuf, 0);
			if (neededLen == -1)
			{
				delete [] allocatedArray;
				retVal = new char[1];
				retVal[0] = 0;
				return retVal;
			}

			retVal = new char[neededLen + 1];
			::wcstombs(retVal, wideCharBuf, neededLen);
			retVal[neededLen] = 0;
			delete [] allocatedArray;
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
			const unsigned int len = mbstowcs((wchar_t*)NULL, toTranscode, 0);
			if ((int)len <= 0)
			{
				retVal = new WCHAR[1];
				retVal[0] = 0;
				return retVal;
			}

			wchar_t tmpWideCharArr[gTempBuffArraySize];
			wchar_t* allocatedArray = 0;
			wchar_t* wideCharBuf = 0;

			if (len >= gTempBuffArraySize)
				wideCharBuf = allocatedArray = new wchar_t[len + 1];
			else
				wideCharBuf = tmpWideCharArr;

			::mbstowcs(wideCharBuf, toTranscode, len);
			retVal = new WCHAR[len + 1];
			for (unsigned int i = 0; i < len; i++)
			{
				retVal[i] = (WCHAR) wideCharBuf[i];
			}
			retVal[len] = 0x00;
			delete [] allocatedArray;
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

#endif /* __ICONV_TRANSCODE_H__ */
