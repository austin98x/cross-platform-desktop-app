/* -------------------------------------------------------------------------
//	File name		：	propidl.h
//	Author 			：	Austin
//	Create Time		：	2016-2-25 12:47:25
//	Description 	：	Define interface for Linux platform
//
// -----------------------------------------------------------------------*/

#pragma warning( disable: 4049 )  /* more than 64k source lines */

#ifndef __PROPIDL_H__
#define __PROPIDL_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

#ifndef WINOLEAPI
#define WINOLEAPI        EXTERN_C __export HRESULT STDAPICALLTYPE
#define WINOLEAPI_(type) EXTERN_C __export type STDAPICALLTYPE
#endif

/* Forward Declarations */ 

#ifndef __IPropertyStorage_FWD_DEFINED__
#define __IPropertyStorage_FWD_DEFINED__
typedef interface IPropertyStorage IPropertyStorage;
#endif 	/* __IPropertyStorage_FWD_DEFINED__ */


#ifndef __IPropertySetStorage_FWD_DEFINED__
#define __IPropertySetStorage_FWD_DEFINED__
typedef interface IPropertySetStorage IPropertySetStorage;
#endif 	/* __IPropertySetStorage_FWD_DEFINED__ */


#ifndef __IEnumSTATPROPSTG_FWD_DEFINED__
#define __IEnumSTATPROPSTG_FWD_DEFINED__
typedef interface IEnumSTATPROPSTG IEnumSTATPROPSTG;
#endif 	/* __IEnumSTATPROPSTG_FWD_DEFINED__ */


#ifndef __IEnumSTATPROPSETSTG_FWD_DEFINED__
#define __IEnumSTATPROPSETSTG_FWD_DEFINED__
typedef interface IEnumSTATPROPSETSTG IEnumSTATPROPSETSTG;
#endif 	/* __IEnumSTATPROPSETSTG_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_propidl_0000_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//--------------------------------------------------------------------------

typedef struct tagVersionedStream
{
	GUID guidVersion;
	IStream *pStream;
} 	VERSIONEDSTREAM;

typedef struct tagVersionedStream *LPVERSIONEDSTREAM;


// Flags for IPropertySetStorage::Create
#define	PROPSETFLAG_DEFAULT	( 0 )

#define	PROPSETFLAG_NONSIMPLE	( 1 )

#define	PROPSETFLAG_ANSI	( 2 )

//   (This flag is only supported on StgCreatePropStg & StgOpenPropStg
#define	PROPSETFLAG_UNBUFFERED	( 4 )

//   (This flag causes a version-1 property set to be created
#define	PROPSETFLAG_CASE_SENSITIVE	( 8 )


// Flags for the reservied PID_BEHAVIOR property
#define	PROPSET_BEHAVIOR_CASE_SENSITIVE	( 1 )

#ifdef MIDL_PASS
// This is the PROPVARIANT definition for marshaling.
typedef struct tag_inner_PROPVARIANT PROPVARIANT;

#else
// This is the standard C layout of the PROPVARIANT.
typedef struct tagPROPVARIANT PROPVARIANT;
#endif
typedef struct tagCAC
{
	UINT32 cElems;
	CHAR *pElems;
} 	CAC;

typedef struct tagCAUB
{
	UINT32 cElems;
	UCHAR *pElems;
} 	CAUB;

typedef struct tagCAI
{
	UINT32 cElems;
	SHORT *pElems;
} 	CAI;

typedef struct tagCAUI
{
	UINT32 cElems;
	USHORT *pElems;
} 	CAUI;

typedef struct tagCAL
{
	UINT32 cElems;
	INT32 *pElems;
} 	CAL;

typedef struct tagCAUL
{
	UINT32 cElems;
	UINT32 *pElems;
} 	CAUL;

typedef struct tagCAFLT
{
	UINT32 cElems;
	FLOAT *pElems;
} 	CAFLT;

typedef struct tagCADBL
{
	UINT32 cElems;
	DOUBLE *pElems;
} 	CADBL;

typedef struct tagCACY
{
	UINT32 cElems;
	CY *pElems;
} 	CACY;

typedef struct tagCADATE
{
	UINT32 cElems;
	DATE *pElems;
} 	CADATE;

typedef struct tagCABSTR
{
	UINT32 cElems;
	BSTR *pElems;
} 	CABSTR;

typedef struct tagBSTRBLOB
{
	UINT32 cbSize;
	BYTE *pData;
}	BSTRBLOB;

typedef struct tagCABSTRBLOB
{
	UINT32 cElems;
	BSTRBLOB *pElems;
} 	CABSTRBLOB;

typedef struct tagCABOOL
{
	UINT32 cElems;
	VARIANT_BOOL *pElems;
} 	CABOOL;

typedef struct tagCASCODE
{
	UINT32 cElems;
	SCODE *pElems;
} 	CASCODE;

typedef struct tagCAPROPVARIANT
{
	UINT32 cElems;
	PROPVARIANT *pElems;
} 	CAPROPVARIANT;

typedef struct tagCAH
{
	UINT32 cElems;
	LARGE_INTEGER *pElems;
} 	CAH;

typedef struct tagCAUH
{
	UINT32 cElems;
	ULARGE_INTEGER *pElems;
} 	CAUH;

typedef struct tagCALPSTR
{
	UINT32 cElems;
	LPSTR *pElems;
} 	CALPSTR;

typedef struct tagCALPWSTR
{
	UINT32 cElems;
	LPWSTR *pElems;
} 	CALPWSTR;

typedef struct tagCLIPDATA
{
	UINT32 cbSize;
	INT32 ulClipFmt;
	BYTE *pClipData;
}	CLIPDATA;

typedef struct tagCAFILETIME
{
	UINT32 cElems;
	FILETIME *pElems;
} 	CAFILETIME;

typedef struct tagCACLIPDATA
{
	UINT32 cElems;
	CLIPDATA *pElems;
} 	CACLIPDATA;

typedef struct tagCACLSID
{
	UINT32 cElems;
	CLSID *pElems;
} 	CACLSID;

typedef struct tagBLOB
{
	UINT32 cbSize;
	BYTE *pBlobData;
}	BLOB;

typedef WORD PROPVAR_PAD1;
typedef WORD PROPVAR_PAD2;
typedef WORD PROPVAR_PAD3;

struct tagPROPVARIANT
{
	VARTYPE vt;
	PROPVAR_PAD1 wReserved1;
	PROPVAR_PAD2 wReserved2;
	PROPVAR_PAD3 wReserved3;
	union
	{
		/* Empty union arm */
		CHAR cVal;
		UCHAR bVal;
		SHORT iVal;
		USHORT uiVal;
		INT32 lVal;
		UINT32 ulVal;
		INT intVal;
		UINT uintVal;
		LARGE_INTEGER hVal;
		ULARGE_INTEGER uhVal;
		FLOAT fltVal;
		DOUBLE dblVal;
		VARIANT_BOOL boolVal;
		bool boolVal2;
		SCODE scode;
		CY cyVal;
		DATE date;
		FILETIME filetime;
		CLSID *puuid;
		CLIPDATA *pclipdata;
		BSTR bstrVal;
		BSTRBLOB bstrblobVal;
		BLOB blob;
		LPSTR pszVal;
		LPWSTR pwszVal;
		IUnknown *punkVal;
		IDispatch *pdispVal;
		IStream *pStream;
		IStorage *pStorage;
		LPVERSIONEDSTREAM pVersionedStream;
		LPSAFEARRAY parray;
		CAC cac;
		CAUB caub;
		CAI cai;
		CAUI caui;
		CAL cal;
		CAUL caul;
		CAH cah;
		CAUH cauh;
		CAFLT caflt;
		CADBL cadbl;
		CABOOL cabool;
		CASCODE cascode;
		CACY cacy;
		CADATE cadate;
		CAFILETIME cafiletime;
		CACLSID cauuid;
		CACLIPDATA caclipdata;
		CABSTR cabstr;
		CABSTRBLOB cabstrblob;
		CALPSTR calpstr;
		CALPWSTR calpwstr;
		CAPROPVARIANT capropvar;
		CHAR *pcVal;
		UCHAR *pbVal;
		SHORT *piVal;
		USHORT *puiVal;
		LONG *plVal;
		ULONG *pulVal;
		INT *pintVal;
		UINT *puintVal;
		FLOAT *pfltVal;
		DOUBLE *pdblVal;
		VARIANT_BOOL *pboolVal;
		DECIMAL *pdecVal;
		SCODE *pscode;
		CY *pcyVal;
		DATE *pdate;
		BSTR *pbstrVal;
		IUnknown **ppunkVal;
		IDispatch **ppdispVal;
		LPSAFEARRAY *pparray;
		PROPVARIANT *pvarVal;
	};
};

// This is the standard C layout of the PROPVARIANT.
typedef struct tagPROPVARIANT * LPPROPVARIANT;

#ifndef _REFPROPVARIANT_DEFINED
#define _REFPROPVARIANT_DEFINED
#ifdef __cplusplus
#define REFPROPVARIANT const PROPVARIANT &
#else
#define REFPROPVARIANT const PROPVARIANT * __MIDL_CONST
#endif
#endif

// Reserved global Property IDs
#define	PID_DICTIONARY	( 0 )

#define	PID_CODEPAGE	( 0x1 )

#define	PID_FIRST_USABLE	( 0x2 )

#define	PID_FIRST_NAME_DEFAULT	( 0xfff )

#define	PID_LOCALE	( 0x80000000 )

#define	PID_MODIFY_TIME	( 0x80000001 )

#define	PID_SECURITY	( 0x80000002 )

#define	PID_BEHAVIOR	( 0x80000003 )

#define	PID_ILLEGAL	( 0xffffffff )

// Range which is read-only to downlevel implementations
#define	PID_MIN_READONLY	( 0x80000000 )

#define	PID_MAX_READONLY	( 0xbfffffff )

// Property IDs for the DiscardableInformation Property Set

#define PIDDI_THUMBNAIL          0x00000002L // VT_BLOB



// Property IDs for the SummaryInformation Property Set
#define PIDSI_TITLE               0x00000002L  // VT_LPSTR
#define PIDSI_SUBJECT             0x00000003L  // VT_LPSTR
#define PIDSI_AUTHOR              0x00000004L  // VT_LPSTR
#define PIDSI_KEYWORDS            0x00000005L  // VT_LPSTR
#define PIDSI_COMMENTS            0x00000006L  // VT_LPSTR
#define PIDSI_TEMPLATE            0x00000007L  // VT_LPSTR
#define PIDSI_LASTAUTHOR          0x00000008L  // VT_LPSTR
#define PIDSI_REVNUMBER           0x00000009L  // VT_LPSTR
#define PIDSI_EDITTIME            0x0000000aL  // VT_FILETIME (UTC)
#define PIDSI_LASTPRINTED         0x0000000bL  // VT_FILETIME (UTC)
#define PIDSI_CREATE_DTM          0x0000000cL  // VT_FILETIME (UTC)
#define PIDSI_LASTSAVE_DTM        0x0000000dL  // VT_FILETIME (UTC)
#define PIDSI_PAGECOUNT           0x0000000eL  // VT_I4
#define PIDSI_WORDCOUNT           0x0000000fL  // VT_I4
#define PIDSI_CHARCOUNT           0x00000010L  // VT_I4
#define PIDSI_THUMBNAIL           0x00000011L  // VT_CF
#define PIDSI_APPNAME             0x00000012L  // VT_LPSTR
#define PIDSI_DOC_SECURITY        0x00000013L  // VT_I4

// Property IDs for the DocSummaryInformation Property Set

#define PIDDSI_CATEGORY          0x00000002 // VT_LPSTR
#define PIDDSI_PRESFORMAT        0x00000003 // VT_LPSTR
#define PIDDSI_BYTECOUNT         0x00000004 // VT_I4
#define PIDDSI_LINECOUNT         0x00000005 // VT_I4
#define PIDDSI_PARCOUNT          0x00000006 // VT_I4
#define PIDDSI_SLIDECOUNT        0x00000007 // VT_I4
#define PIDDSI_NOTECOUNT         0x00000008 // VT_I4
#define PIDDSI_HIDDENCOUNT       0x00000009 // VT_I4
#define PIDDSI_MMCLIPCOUNT       0x0000000A // VT_I4
#define PIDDSI_SCALE             0x0000000B // VT_BOOL
#define PIDDSI_HEADINGPAIR       0x0000000C // VT_VARIANT | VT_VECTOR
#define PIDDSI_DOCPARTS          0x0000000D // VT_LPSTR | VT_VECTOR
#define PIDDSI_MANAGER           0x0000000E // VT_LPSTR
#define PIDDSI_COMPANY           0x0000000F // VT_LPSTR
#define PIDDSI_LINKSDIRTY        0x00000010 // VT_BOOL


//  FMTID_MediaFileSummaryInfo - Property IDs

#define PIDMSI_EDITOR                   0x00000002L  // VT_LPWSTR
#define PIDMSI_SUPPLIER                 0x00000003L  // VT_LPWSTR
#define PIDMSI_SOURCE                   0x00000004L  // VT_LPWSTR
#define PIDMSI_SEQUENCE_NO              0x00000005L  // VT_LPWSTR
#define PIDMSI_PROJECT                  0x00000006L  // VT_LPWSTR
#define PIDMSI_STATUS                   0x00000007L  // VT_UI4
#define PIDMSI_OWNER                    0x00000008L  // VT_LPWSTR
#define PIDMSI_RATING                   0x00000009L  // VT_LPWSTR
#define PIDMSI_PRODUCTION               0x0000000AL  // VT_FILETIME (UTC)
#define PIDMSI_COPYRIGHT                0x0000000BL  // VT_LPWSTR

//  PIDMSI_STATUS value definitions

enum PIDMSI_STATUS_VALUE
{
	PIDMSI_STATUS_NORMAL	= 0,
	PIDMSI_STATUS_NEW	= ( PIDMSI_STATUS_NORMAL + 1 ) ,
	PIDMSI_STATUS_PRELIM	= ( PIDMSI_STATUS_NEW + 1 ) ,
	PIDMSI_STATUS_DRAFT	= ( PIDMSI_STATUS_PRELIM + 1 ) ,
	PIDMSI_STATUS_INPROGRESS	= ( PIDMSI_STATUS_DRAFT + 1 ) ,
	PIDMSI_STATUS_EDIT	= ( PIDMSI_STATUS_INPROGRESS + 1 ) ,
	PIDMSI_STATUS_REVIEW	= ( PIDMSI_STATUS_EDIT + 1 ) ,
	PIDMSI_STATUS_PROOF	= ( PIDMSI_STATUS_REVIEW + 1 ) ,
	PIDMSI_STATUS_FINAL	= ( PIDMSI_STATUS_PROOF + 1 ) ,
	PIDMSI_STATUS_OTHER	= 0x7fff
};
#define	PRSPEC_INVALID	( 0xffffffff )

#define	PRSPEC_LPWSTR	( 0 )

#define	PRSPEC_PROPID	( 1 )

typedef struct tagPROPSPEC
{
	UINT32 ulKind;
	union
	{
		PROPID propid;
		LPOLESTR lpwstr;
		/* Empty union arm */
	};
} 	PROPSPEC;

typedef struct tagSTATPROPSTG
{
	LPOLESTR lpwstrName;
	PROPID propid;
	VARTYPE vt;
} 	STATPROPSTG;

typedef unsigned char BOOLEAN;
typedef GUID FMTID;

extern const FMTID FMTID_SummaryInformation;
extern const FMTID FMTID_DocSummaryInformation;
extern const FMTID FMTID_UserDefinedProperties;
extern const FMTID FMTID_DiscardableInformation;
extern const FMTID FMTID_ImageSummaryInformation;
extern const FMTID FMTID_AudioSummaryInformation;
extern const FMTID FMTID_VideoSummaryInformation;
extern const FMTID FMTID_MediaFileSummaryInformation;

// Macros for parsing the OS Version of the Property Set Header
#define PROPSETHDR_OSVER_KIND(dwOSVer)      HIWORD( (dwOSVer) )
#define PROPSETHDR_OSVER_MAJOR(dwOSVer)     LOBYTE(LOWORD( (dwOSVer) ))
#define PROPSETHDR_OSVER_MINOR(dwOSVer)     HIBYTE(LOWORD( (dwOSVer) ))
#define PROPSETHDR_OSVERSION_UNKNOWN        0xFFFFFFFF
typedef struct tagSTATPROPSETSTG
{
	FMTID fmtid;
	CLSID clsid;
	DWORD grfFlags;
	FILETIME mtime;
	FILETIME ctime;
	FILETIME atime;
	DWORD dwOSVersion;
} 	STATPROPSETSTG;



#ifndef __IPropertyStorage_INTERFACE_DEFINED__
#define __IPropertyStorage_INTERFACE_DEFINED__

/* interface IPropertyStorage */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPropertyStorage;

MIDL_INTERFACE_("00000138-0000-0000-C000-000000000046", IPropertyStorage)
	: public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE ReadMultiple(
		/* [in] */ ULONG cpspec,
		/* [size_is][in] */ const PROPSPEC rgpspec[  ],
		/* [size_is][out] */ PROPVARIANT rgpropvar[  ]) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteMultiple(
		/* [in] */ ULONG cpspec,
		/* [size_is][in] */ const PROPSPEC rgpspec[  ],
		/* [size_is][in] */ const PROPVARIANT rgpropvar[  ],
		/* [in] */ PROPID propidNameFirst) = 0;

	virtual HRESULT STDMETHODCALLTYPE DeleteMultiple(
		/* [in] */ ULONG cpspec,
		/* [size_is][in] */ const PROPSPEC rgpspec[  ]) = 0;

	virtual HRESULT STDMETHODCALLTYPE ReadPropertyNames(
		/* [in] */ ULONG cpropid,
		/* [size_is][in] */ const PROPID rgpropid[  ],
		/* [size_is][out] */ LPOLESTR rglpwstrName[  ]) = 0;

	virtual HRESULT STDMETHODCALLTYPE WritePropertyNames(
		/* [in] */ ULONG cpropid,
		/* [size_is][in] */ const PROPID rgpropid[  ],
		/* [size_is][in] */ const LPOLESTR rglpwstrName[  ]) = 0;

	virtual HRESULT STDMETHODCALLTYPE DeletePropertyNames(
		/* [in] */ ULONG cpropid,
		/* [size_is][in] */ const PROPID rgpropid[  ]) = 0;

	virtual HRESULT STDMETHODCALLTYPE Commit(
		/* [in] */ DWORD grfCommitFlags) = 0;

	virtual HRESULT STDMETHODCALLTYPE Revert( void) = 0;

	virtual HRESULT STDMETHODCALLTYPE Enum(
		/* [out] */ IEnumSTATPROPSTG **ppenum) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetTimes(
		/* [in] */ const FILETIME *pctime,
		/* [in] */ const FILETIME *patime,
		/* [in] */ const FILETIME *pmtime) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetClass(
		/* [in] */ REFCLSID clsid) = 0;

	virtual HRESULT STDMETHODCALLTYPE Stat(
		/* [out] */ STATPROPSETSTG *pstatpsstg) = 0;

};
    
#endif 	/* __IPropertyStorage_INTERFACE_DEFINED__ */


#ifndef __IPropertySetStorage_INTERFACE_DEFINED__
#define __IPropertySetStorage_INTERFACE_DEFINED__

/* interface IPropertySetStorage */
/* [unique][uuid][object] */ 

typedef /* [unique] */  IPropertySetStorage *LPPROPERTYSETSTORAGE;


EXTERN_C const IID IID_IPropertySetStorage;

MIDL_INTERFACE_("0000013A-0000-0000-C000-000000000046", IPropertySetStorage)
	: public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Create(
		/* [in] */ REFFMTID rfmtid,
		/* [unique][in] */ const CLSID *pclsid,
		/* [in] */ DWORD grfFlags,
		/* [in] */ DWORD grfMode,
		/* [out] */ IPropertyStorage **ppprstg) = 0;

	virtual HRESULT STDMETHODCALLTYPE Open(
		/* [in] */ REFFMTID rfmtid,
		/* [in] */ DWORD grfMode,
		/* [out] */ IPropertyStorage **ppprstg) = 0;

	virtual HRESULT STDMETHODCALLTYPE Delete(
		/* [in] */ REFFMTID rfmtid) = 0;

	virtual HRESULT STDMETHODCALLTYPE Enum(
		/* [out] */ IEnumSTATPROPSETSTG **ppenum) = 0;

};


#endif 	/* __IPropertySetStorage_INTERFACE_DEFINED__ */


#ifndef __IEnumSTATPROPSTG_INTERFACE_DEFINED__
#define __IEnumSTATPROPSTG_INTERFACE_DEFINED__

/* interface IEnumSTATPROPSTG */
/* [unique][uuid][object] */ 

typedef /* [unique] */  IEnumSTATPROPSTG *LPENUMSTATPROPSTG;


EXTERN_C const IID IID_IEnumSTATPROPSTG;

MIDL_INTERFACE_("00000139-0000-0000-C000-000000000046", IEnumSTATPROPSTG)
	: public IUnknown
{
public:
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG celt,
		/* [length_is][size_is][out] */ STATPROPSTG *rgelt,
		/* [out] */ ULONG *pceltFetched) = 0;

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG celt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ IEnumSTATPROPSTG **ppenum) = 0;

};


#endif 	/* __IEnumSTATPROPSTG_INTERFACE_DEFINED__ */


#ifndef __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__
#define __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__

/* interface IEnumSTATPROPSETSTG */
/* [unique][uuid][object] */ 

typedef /* [unique] */  IEnumSTATPROPSETSTG *LPENUMSTATPROPSETSTG;


EXTERN_C const IID IID_IEnumSTATPROPSETSTG;

MIDL_INTERFACE_("0000013B-0000-0000-C000-000000000046", IEnumSTATPROPSETSTG)
	: public IUnknown
{
public:
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG celt,
		/* [length_is][size_is][out] */ STATPROPSETSTG *rgelt,
		/* [out] */ ULONG *pceltFetched) = 0;

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG celt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ IEnumSTATPROPSETSTG **ppenum) = 0;

};

#endif 	/* __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_propidl_0000_0004 */
/* [local] */ 

typedef /* [unique] */  IPropertyStorage *LPPROPERTYSTORAGE;

WINOLEAPI PropVariantCopy ( PROPVARIANT * pvarDest, const PROPVARIANT * pvarSrc );
WINOLEAPI PropVariantClear ( PROPVARIANT * pvar );
WINOLEAPI FreePropVariantArray ( ULONG cVariants, PROPVARIANT * rgvars );

#define _PROPVARIANTINIT_DEFINED_
inline void PropVariantInit ( PROPVARIANT * pvar )
{
    memset ( pvar, 0, sizeof(PROPVARIANT) );
}


#ifndef _STGCREATEPROPSTG_DEFINED_
WINOLEAPI StgCreatePropStg( IUnknown* pUnk, REFFMTID fmtid, const CLSID *pclsid, DWORD grfFlags, DWORD dwReserved, IPropertyStorage **ppPropStg );
WINOLEAPI StgOpenPropStg( IUnknown* pUnk, REFFMTID fmtid, DWORD grfFlags, DWORD dwReserved, IPropertyStorage **ppPropStg );
WINOLEAPI StgCreatePropSetStg( IStorage *pStorage, DWORD dwReserved, IPropertySetStorage **ppPropSetStg);

#define CCH_MAX_PROPSTG_NAME    31
WINOLEAPI FmtIdToPropStgName( const FMTID *pfmtid, LPOLESTR oszName );
WINOLEAPI PropStgNameToFmtId( const LPOLESTR oszName, FMTID *pfmtid );
#endif
#ifndef _SERIALIZEDPROPERTYVALUE_DEFINED_
#define _SERIALIZEDPROPERTYVALUE_DEFINED_
typedef struct tagSERIALIZEDPROPERTYVALUE		// prop
{
    DWORD	dwType;
    BYTE	rgb[1];
} SERIALIZEDPROPERTYVALUE;
#endif

EXTERN_C SERIALIZEDPROPERTYVALUE* __stdcall
StgConvertVariantToProperty(
			const PROPVARIANT* pvar,
            USHORT CodePage,
			SERIALIZEDPROPERTYVALUE* pprop,
			ULONG* pcb,
            PROPID pid,
			BOOLEAN fReserved,
			ULONG* pcIndirect);

#ifdef __cplusplus
class PMemoryAllocator;

EXTERN_C BOOLEAN __stdcall
StgConvertPropertyToVariant(
			const SERIALIZEDPROPERTYVALUE* pprop,
            USHORT CodePage,
			PROPVARIANT* pvar,
			PMemoryAllocator* pma);
#endif


/* Additional Prototypes for ALL interfaces */

unsigned long    BSTR_UserSize(     unsigned long *, unsigned long  , BSTR * );
unsigned char *  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * );
unsigned char *  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * );
void             BSTR_UserFree(     unsigned long *, BSTR * );

unsigned long    LPSAFEARRAY_UserSize(     unsigned long *, unsigned long  , LPSAFEARRAY * );
unsigned char *  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * );
unsigned char *  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * );
void             LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * );

unsigned long    BSTR_UserSize64(     unsigned long *, unsigned long  , BSTR * );
unsigned char *  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * );
unsigned char *  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * );
void             BSTR_UserFree64(     unsigned long *, BSTR * );

unsigned long    LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long  , LPSAFEARRAY * );
unsigned char *  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * );
unsigned char *  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * );
void             LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * );


/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif // __PROPIDL_H__
