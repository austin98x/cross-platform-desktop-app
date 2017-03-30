/* -------------------------------------------------------------------------
//	File name		：	errorinfo.cpp
//	Author 			：	Austin
//	Create Time		：	2017-3-30 10:19:11
//	Description 	：	Impl of ErrorInfo functions
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
EXPORTAPI _XCreateErrorInfo(ICreateErrorInfo** pperrinfo)
{
	return E_NOTIMPL;
}

EXPORTAPI _XSetErrorInfo(UINT dwReserved, IErrorInfo* perrinfo)
{
	return E_NOTIMPL;
}

EXPORTAPI _XGetErrorInfo(UINT dwReserved, IErrorInfo **pperrinfo)
{
	return E_NOTIMPL;
}

// -------------------------------------------------------------------------
void _force_link_errorinfo() {}

