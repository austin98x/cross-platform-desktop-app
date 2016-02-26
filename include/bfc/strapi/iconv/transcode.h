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
	static unsigned int wstrlen(const WCHAR* const src)
	{
		const WCHAR* end = src;
		while (*end)
			++end;
		return end - src;
	}

	static wchar_t* transcodeUTF16(const WCHAR* const toTranscode)
	{
		unsigned int wLent = wstrlen(toTranscode);

		wchar_t* wideCharBuf = 0;
		wideCharBuf = new wchar_t[wLent + 1];

		for (unsigned int i = 0; i < wLent; i++)
		{
			wideCharBuf[i] = toTranscode[i];
		}
		wideCharBuf[wLent] = 0x00;

		return wideCharBuf;
	}

	static wchar_t* transcodeUTF8(const char* const toTranscode)
	{
		unsigned int Lent = strlen(toTranscode);

		wchar_t* wideCharBuf = 0;
		wideCharBuf = new wchar_t[Lent + 1];

		int nret = ::mbstowcs(wideCharBuf, toTranscode, Lent);
		if (-1 == nret)
		{
			delete [] wideCharBuf;
			wideCharBuf = new wchar_t[1];
			wideCharBuf[0] = 0x00;
			return wideCharBuf;
		}
		wideCharBuf[Lent] = 0x00;

		return wideCharBuf;
	}

	static char* transcodeUCS4toUTF8(const wchar_t* const toTranscode)
	{
		unsigned int wLent = ::wcslen(toTranscode);

		char* charBuf = 0;
		charBuf = new char[wLent + 1];

		int nret = ::wcstombs(charBuf, toTranscode, wLent);
		if (-1 == nret)
		{
			delete [] charBuf;
			charBuf = new char[1];
			charBuf[0] = 0;
			return charBuf;
		}
		charBuf[wLent] = 0;

		return charBuf;
	}

	static WCHAR* transcodeUCS4toUTF16(const wchar_t* const toTranscode)
	{
		unsigned int wLent = ::wcslen(toTranscode);

		WCHAR* wideCharBuf = 0;
		wideCharBuf = new WCHAR[wLent + 1];

		for (unsigned int i = 0; i < wLent; i++)
		{
			wideCharBuf[i] = (WCHAR)toTranscode[i];
		}
		wideCharBuf[wLent] = 0x0;

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
			unsigned int  wLent = wstrlen(toTranscode);

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
			const size_t neededLen = ::wcstombs(0, wideCharBuf, 0);
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
			const unsigned int len = strlen(toTranscode);

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

public:
	enum
	{
		gTempBuffArraySize = 1024
	};
};

// -------------------------------------------------------------------------

#endif /* __ICONV_TRANSCODE_H__ */
