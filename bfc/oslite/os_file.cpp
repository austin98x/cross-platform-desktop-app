/* -------------------------------------------------------------------------
//	File name		：	os_fileio.h
//	Author 			：	Austin
//	Create Time		：	2016-2-22 10:39:45
//	Description 	：	File Part 
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"

#ifdef X_OS_WINDOWS
#include <share.h>
#include <string>

// -------------------------------------------------------------------------
#define GFA_INVAID	((DWORD)-1)

STDAPI_(BOOL) _XIsDirExist(LPCWSTR szPathW)
{
	DWORD dwState = GetFileAttributesW(szPathW);
	return dwState != GFA_INVAID && (dwState & FILE_ATTRIBUTE_DIRECTORY);
}

STDAPI_(BOOL) _XIsFileExistA(LPCSTR szFile)
{
	DWORD dwState = GetFileAttributes(szFile);
	return dwState != GFA_INVAID && !(dwState & FILE_ATTRIBUTE_DIRECTORY);
}

STDAPI_(BOOL) _XIsFileExist(LPCWSTR szFileW)
{
	DWORD dwState = GetFileAttributesW(szFileW);
	return dwState != GFA_INVAID && !(dwState & FILE_ATTRIBUTE_DIRECTORY);
}

STDAPI_(BOOL) _XIsPathExist(LPCWSTR szFileOrDirW)
{
	return GetFileAttributesW(szFileOrDirW) != GFA_INVAID;
}

STDAPI_(BOOL) _XIsReadOnly(LPCWSTR szFileW)
{
	DWORD dwState = GetFileAttributesW(szFileW);
	return dwState != GFA_INVAID && (dwState & FILE_ATTRIBUTE_READONLY);
}

STDAPI_(BOOL) _XIsWritableDir(LPCWSTR szDir)
{
	BOOL bWritable = FALSE;
	DWORD length = 0;
	const SECURITY_INFORMATION seFileInfo = 
		OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;

	if (!GetFileSecurityW(szDir, seFileInfo, NULL, NULL, &length) &&
		ERROR_INSUFFICIENT_BUFFER == GetLastError())
	{
		std::string tempBuffer;
		tempBuffer.reserve(length);
		PSECURITY_DESCRIPTOR security = (PSECURITY_DESCRIPTOR)tempBuffer.data();
		if (security && GetFileSecurityW(szDir, seFileInfo, security, length, &length))
		{
			HANDLE hToken = NULL;
			const DWORD tokenDesiredAccess = 
				TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE | STANDARD_RIGHTS_READ;

			if (!OpenThreadToken(GetCurrentThread(), tokenDesiredAccess, TRUE, &hToken))
				OpenProcessToken(GetCurrentProcess(), tokenDesiredAccess, &hToken);

			HANDLE hImpersonatedToken = NULL;
			if (DuplicateToken(hToken, SecurityImpersonation, &hImpersonatedToken))
			{
				GENERIC_MAPPING mapping = {0xFFFFFFFF};
				mapping.GenericRead = FILE_GENERIC_READ;
				mapping.GenericWrite = FILE_GENERIC_WRITE;
				mapping.GenericExecute = FILE_GENERIC_EXECUTE;
				mapping.GenericAll = FILE_ALL_ACCESS;

				DWORD genericAccessRights = FILE_GENERIC_WRITE;
				MapGenericMask(&genericAccessRights, &mapping);

				BOOL bResult = FALSE;
				PRIVILEGE_SET privileges = {0};
				DWORD privilegesLength = sizeof(privileges);
				DWORD grantedAccess = 0;
				if (AccessCheck(security, hImpersonatedToken, genericAccessRights,
					&mapping, &privileges, &privilegesLength, &grantedAccess, &bResult))
				{
					bWritable = bResult;
				}
				CloseHandle(hImpersonatedToken);
			}

			CloseHandle(hToken);
		}
	}

	return bWritable;
}

STDAPI _Xaccess(LPCWSTR szFileW, int nMode)
{
	DWORD attr = GetFileAttributesW(szFileW);

	if (attr == 0xffffffff) 
		return -1;

	if ( (attr & FILE_ATTRIBUTE_READONLY) && (nMode & 2) ) 
		return -1;

	return S_OK;
}

STDAPI _Xchmod(LPCWSTR szFileW, int mode)
{
	DWORD attr;

	attr = GetFileAttributesW(szFileW);
	if (attr  == 0xffffffff) 
		return -1;

	if (mode & 0000200) 
		attr &= ~FILE_ATTRIBUTE_READONLY;
	else
		attr |= FILE_ATTRIBUTE_READONLY;

	if (!SetFileAttributesW(szFileW, attr)) 
		return -1;

	return S_OK;
}

STDAPI _Xremove(LPCWSTR szFileW)
{
	return DeleteFileW(szFileW) ? 0 : -1;
}

STDAPI _Xrename(LPCWSTR szOldFileW, LPCWSTR szNewFileW)
{
	return MoveFileW(szOldFileW, szNewFileW) ? 0 : -1;
}

STDAPI_(FILE*) _Xfopen(LPCWSTR szFileW, LPCWSTR mode)
{
	return _wfopen(szFileW, mode);
}

STDAPI_(FILE*) _Xfsopen(LPCWSTR szFileW, LPCWSTR mode, int shflag)
{
	return _wfsopen(szFileW, mode, shflag);
}

STDAPI_(HANDLE) _XFileLockWrite(LPCWSTR szFileW)
{
	HANDLE h = INVALID_HANDLE_VALUE;
	
	if (!_XIsFileExist(szFileW))
		return h;

	h = CreateFileW(szFileW,
					GENERIC_WRITE,
					FILE_SHARE_READ,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
	
	assert(INVALID_HANDLE_VALUE != h);
	
	return h;
}

STDAPI_(VOID) _XFlushFileBuffers(LPCWSTR szFileW)
{
	HANDLE h = INVALID_HANDLE_VALUE;
	
	if (!_XIsFileExist(szFileW))
		return;

	h = CreateFileW(szFileW,
					GENERIC_WRITE,
					FILE_SHARE_READ,
					NULL,
					OPEN_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL);

	assert(INVALID_HANDLE_VALUE != h);
	if (INVALID_HANDLE_VALUE != h)
	{
		FlushFileBuffers(h);
		CloseHandle(h);
	}

	return ;
}

STDAPI _XFileUnlockWrite(HANDLE h)
{
	if (INVALID_HANDLE_VALUE != h)
		return CloseHandle(h) ? S_OK : E_FAIL;

	assert(0);
	return E_INVALIDARG;
}

STDAPI_(BOOL) _XFileCanLockForRW(LPCWSTR szFileW, BOOL bWrite)
{
	if (!_XIsFileExist(szFileW))
		return FALSE;

	DWORD dwAttr = GetFileAttributesW(szFileW);

	if (bWrite && (FILE_ATTRIBUTE_READONLY & dwAttr))
		return FALSE;

	DWORD dwAccess = bWrite ? GENERIC_WRITE : GENERIC_READ;
	DWORD dwShare  = bWrite ? FILE_SHARE_READ : FILE_SHARE_READ | FILE_SHARE_WRITE;

	HANDLE hFile = CreateFileW(szFileW,
							   dwAccess,
							   dwShare,
							   NULL,
							   OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,
							   NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return FALSE;

	CloseHandle(hFile);
	return TRUE;
}

#else

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// -------------------------------------------------------------------------
STDAPI_(BOOL) _XIsDirExist(LPCWSTR szPathW)
{
	QFileInfo fileInfo(QString::fromUtf16(szFileOrDirW));
	return fileInfo.exists() ? TRUE : FALSE;
}

STDAPI_(BOOL) _XIsFileExistA(LPCSTR szFile)
{
	QFileInfo fileInfo(QString::fromLocal8Bit(szFile));
	return fileInfo.exists() ? TRUE : FALSE;
}

STDAPI_(BOOL) _XIsPathExist(LPCWSTR szFileOrDirW)
{
	QFileInfo fileInfo(QString::fromUtf16(szFileOrDirW));
	return fileInfo.exists() ? TRUE : FALSE;
}

STDAPI_(BOOL) _XIsFileExist(LPCWSTR szFile)
{
	QFileInfo fileInfo(QString::fromUtf16(szFileOrDirW));
	return fileInfo.exists() ? TRUE : FALSE;
}

STDAPI_(BOOL) _XIsReadOnly(LPCWSTR szFileW)
{
	QFileInfo fileInfo(QString::fromUtf16(szFileW));
	if (!fileInfo.exists())
		return TRUE;
	
	if (fileInfo.permission(QFile::WriteOwner))
		return FALSE;
	
	if (fileInfo.permission(QFile::WriteUser))
		return FALSE;
	
	if (fileInfo.permission(QFile::WriteGroup))
		return FALSE;
	
	if (fileInfo.permission(QFile::WriteOther))
		return FALSE;
	
	return TRUE;
}

STDAPI_(BOOL) _XIsWritableDir(LPCWSTR szDir)
{
	QFileInfo fileInfo(QString::fromUtf16(szDir));
	return fileInfo.isWritable();
}

STDAPI _Xaccess(LPCWSTR szFileW, int nMode)
{
	QString strFileName = QString::fromUtf16((const ushort*)szFileW);
	return access(strFileName.toLocal8Bit().data(), nMode);
}

STDAPI _Xchmod(LPCWSTR szFileW, int mode)
{
	QString strFileName = QString::fromUtf16((const ushort*)szFileW);
	return chmod(strFileName.toLocal8Bit().data(), mode);
}

STDAPI _Xremove(LPCWSTR szFileW)
{
	QString strFileName = QString::fromUtf16((const ushort*)szFileW);
	return remove(strFileName.toLocal8Bit().data());
}

STDAPI _Xrename(LPCWSTR szOldFileW, LPCWSTR szNewFileW)
{
	QString strOldFileName = QString::fromUtf16((const ushort*)szFileW);
	QString strNewFileName = QString::fromUtf16((const ushort*)szFileW);
	return rename(strOldFileName.toLocal8Bit().data(), strNewFileName.toLocal8Bit().data());
}

STDAPI_(FILE*) _Xfopen(LPCWSTR szFileW, LPCWSTR mode)
{
	QString strFileName = QString::fromUtf16((const ushort*)szFileW);
	QString strMode = QString::fromUtf16((const ushort*)mode);
	return fopen(strFileName.toLocal8Bit().data(), strMode.toLocal8Bit().data());
}

STDAPI_(FILE*) _Xfsopen(LPCWSTR szFileW, LPCWSTR mode, int shflag)
{
	QString strFileName = QString::fromUtf16((const ushort*)szFileW);
	QString strMode = QString::fromUtf16((const ushort*)mode);
	return fopen(strFileName.toLocal8Bit().data(), strMode.toLocal8Bit().data());
}

STDAPI_(HANDLE) _XFileLockWrite(LPCWSTR szFileW)
{
	QString strFileName = QString::fromUtf16((const ushort*)szFileW);
	int fd = open(strFileName.toLocal8Bit().data(), O_WRONLY);
	if (fd != -1)
	{
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		fcntl(fd, F_SETLK, &lock);
	}
	return (HANDLE)(intp)fd;
}

STDAPI_(VOID) _XFlushFileBuffers(LPCWSTR szFileW)
{
}

STDAPI _XFileUnlockWrite(HANDLE h)
{
	int fd = (int)(intp)h;
	if (fd != -1)
	{
		struct flock lock;
		lock.l_type = F_UNLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		fcntl(fd, F_SETLK, &lock);
		close(fd);
	}

	return S_OK;
}

STDAPI_(BOOL) _XFileCanLockForRW(LPCWSTR szFileW, BOOL bWrite)
{
	BOOL bRet = FALSE;
	QString strFileName = QString::fromUtf16((const ushort*)szFileW);
	int fd = open(strFileName.toLocal8Bit().data(), bWrite ? O_WRONLY : O_RDONLY);
	if (fd != -1)
	{
		unsigned int lk_mode = bWrite ? F_WRLCK : F_RDLCK;
		struct flock lock;
		lock.l_type = lk_mode;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		fcntl(fd, F_GETLK, &lock);
		if (lock.l_type == lk_mode)
			bRet = FALSE;
		else
			bRet = TRUE;

		close(fd);
	}
	return bRet;
}

#endif

// -------------------------------------------------------------------------
