/* -------------------------------------------------------------------------
//	File name		：	ole2.h
//	Author 			：	Austin
//	Create Time		：	2016-3-2 10:48:10
//	Description 	：	APIs declare
//
// -----------------------------------------------------------------------*/
#ifndef _OLE2_H__
#define _OLE2_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

#ifndef WINOLEAPI
#define WINOLEAPI        EXTERN_C __export HRESULT STDAPICALLTYPE
#define WINOLEAPI_(type) EXTERN_C __export type STDAPICALLTYPE
#endif

// -------------------------------------------------------------------------
// Common stuff gleamed from OLE.2,

/* verbs */
#define OLEIVERB_PRIMARY            (0L)
#define OLEIVERB_SHOW               (-1L)
#define OLEIVERB_OPEN               (-2L)
#define OLEIVERB_HIDE               (-3L)
#define OLEIVERB_UIACTIVATE         (-4L)
#define OLEIVERB_INPLACEACTIVATE    (-5L)
#define OLEIVERB_DISCARDUNDOSTATE   (-6L)

// -------------------------------------------------------------------------
// --> Storage Utility APIs

WINOLEAPI _XGetHGlobalFromILockBytes(LPLOCKBYTES plkbyt, HGLOBAL FAR* phglobal);
WINOLEAPI _XCreateILockBytesOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease,
									 LPLOCKBYTES FAR* pplkbyt);

WINOLEAPI _XGetHGlobalFromStream(LPSTREAM pstm, HGLOBAL FAR* phglobal);
WINOLEAPI _XCreateStreamOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease,
								 LPSTREAM FAR* ppstm);

#define GetHGlobalFromILockBytes(plkbyt, phglobal)							\
	_XGetHGlobalFromILockBytes(plkbyt, phglobal)

#define CreateILockBytesOnHGlobal(hGlobal, fDeleteOnRelease, pplkbyt)		\
	_XCreateILockBytesOnHGlobal(hGlobal, fDeleteOnRelease, pplkbyt)

#define GetHGlobalFromStream(pstm, phglobal)								\
	_XGetHGlobalFromStream(pstm, phglobal)

#define CreateStreamOnHGlobal(hGlobal, fDeleteOnRelease, ppstm)				\
	_XCreateStreamOnHGlobal(hGlobal, fDeleteOnRelease, ppstm)

// -------------------------------------------------------------------------
// --> Clipboard APIs

interface IDataObject;

WINOLEAPI  _XOleSetClipboard(IDataObject* pDataObj);
WINOLEAPI  _XOleGetClipboard(IDataObject** ppDataObj);
WINOLEAPI  _XOleFlushClipboard();
WINOLEAPI  _XOleIsCurrentClipboard(IDataObject* pDataObj);

#define OleSetClipboard(pDataObj)											\
	_XOleSetClipboard(pDataObj)

#define OleGetClipboard(ppDataObj)											\
	_XOleGetClipboard(ppDataObj)

#define OleFlushClipboard()													\
	_XOleFlushClipboard()

#define OleIsCurrentClipboard(pDataObj)										\
	_XOleIsCurrentClipboard(pDataObj)

// -------------------------------------------------------------------------
// --> Drag/Drop APIs

interface IDataObject;
interface IDropSource;

WINOLEAPI  _XDoDragDrop(
						IDataObject* pDataObj,
						IDropSource* pDropSource,
						DWORD dwOKEffects,
						LPDWORD pdwEffect
						);

#define DoDragDrop(pDataObj, pDropSource, dwOKEffects, pdwEffect)			\
	_XDoDragDrop(pDataObj, pDropSource, dwOKEffects, pdwEffect)

// -------------------------------------------------------------------------
// --> Stream Utility APIs

typedef struct _OLESTREAM FAR*  LPOLESTREAM;

/* Stream definitions */
typedef struct _OLESTREAMVTBL
{
	DWORD (CALLBACK* Get)(LPOLESTREAM, void FAR*, DWORD);
	DWORD (CALLBACK* Put)(LPOLESTREAM, const void FAR*, DWORD);
} OLESTREAMVTBL;
typedef  OLESTREAMVTBL FAR*  LPOLESTREAMVTBL;

typedef struct _OLESTREAM
{
	LPOLESTREAMVTBL      lpstbl;
} OLESTREAM;


WINOLEAPI _XOleConvertIStorageToOLESTREAM(IStorage *pstg,
									   LPOLESTREAM polestm);

WINOLEAPI _XOleConvertOLESTREAMToIStorage(
		LPOLESTREAM pOleStream,
		LPSTORAGE pstg,
		const DVTARGETDEVICE* ptd);

#define OleConvertIStorageToOLESTREAM(pstg, polestm)	\
		_XOleConvertIStorageToOLESTREAM(pstg, polestm)

#define OleConvertOLESTREAMToIStorage(pOleStream, pstg, ptd)	\
		_XOleConvertOLESTREAMToIStorage(pOleStream, pstg, ptd)

// -------------------------------------------------------------------------

#endif /* _OLE2_H__ */
