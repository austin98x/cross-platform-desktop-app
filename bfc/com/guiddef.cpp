/* -------------------------------------------------------------------------
//	File name		：	guiddef.cpp
//	Author 			：	Austin
//	Create Time		：	2017-3-30 10:21:11
//	Description 	：	GUID
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
EXTERN_C __export const GUID IID_NULL = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
EXTERN_C __export const GUID GUID_NULL = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
EXTERN_C __export const GUID CLSID_NULL = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

// -------------------------------------------------------------------------
// objidl.h
EXTERN_C __export const IID IID_IUnknown =					__uuid(IUnknown);
EXTERN_C __export const IID IID_IClassFactory =				__uuid(IClassFactory);
EXTERN_C __export const IID IID_IEnumUnknown =				__uuid(IEnumUnknown);
EXTERN_C __export const IID IID_IMalloc =					__uuid(IMalloc);
EXTERN_C __export const IID IID_IMallocSpy =				__uuid(IMallocSpy);
EXTERN_C __export const IID IID_ILockBytes =				__uuid(ILockBytes);
EXTERN_C __export const IID IID_ISequentialStream =			__uuid(ISequentialStream);
EXTERN_C __export const IID IID_IStream =					__uuid(IStream);
EXTERN_C __export const IID IID_IEnumSTATSTG =				__uuid(IEnumSTATSTG);
EXTERN_C __export const IID IID_IStorage =					__uuid(IStorage);
EXTERN_C __export const IID IID_IPersist =					__uuid(IPersist);
EXTERN_C __export const IID IID_IPersistStream =			__uuid(IPersistStream);
EXTERN_C __export const IID IID_IEnumString =				__uuid(IEnumString);
EXTERN_C __export const IID IID_IMoniker =					__uuid(IMoniker);
EXTERN_C __export const IID IID_IPersistFile =				__uuid(IPersistFile);
EXTERN_C __export const IID IID_IPersistStorage =			__uuid(IPersistStorage);
EXTERN_C __export const IID IID_IEnumMoniker =				__uuid(IEnumMoniker);
EXTERN_C __export const IID IID_IRunningObjectTable =		__uuid(IRunningObjectTable);
EXTERN_C __export const IID IID_IBindCtx =					__uuid(IBindCtx);
EXTERN_C __export const IID IID_IAdviseSink =				__uuid(IAdviseSink);
EXTERN_C __export const IID IID_IEnumSTATDATA =				__uuid(IEnumSTATDATA);
EXTERN_C __export const IID IID_IEnumFORMATETC =			__uuid(IEnumFORMATETC);
EXTERN_C __export const IID IID_IDataObject =				__uuid(IDataObject);
EXTERN_C __export const IID IID_IStdMarshalInfo =			__uuid(IStdMarshalInfo);
EXTERN_C __export const IID IID_IExternalConnection =		__uuid(IExternalConnection);

// -------------------------------------------------------------------------
// ocidl.h
EXTERN_C __export const IID IID_IConnectionPoint =			__uuid(IConnectionPoint);
EXTERN_C __export const IID IID_IEnumConnectionPoints =		__uuid(IEnumConnectionPoints);
EXTERN_C __export const IID IID_IConnectionPointContainer =	__uuid(IConnectionPointContainer);
EXTERN_C __export const IID IID_IEnumConnections =			__uuid(IEnumConnections);

// -------------------------------------------------------------------------
// oleidl.h
EXTERN_C __export const IID IID_IEnumOLEVERB =				__uuid(IEnumOLEVERB);
EXTERN_C __export const IID IID_IOleObject =				__uuid(IOleObject);
EXTERN_C __export const IID IID_IOleClientSite =			__uuid(IOleClientSite);
EXTERN_C __export const IID IID_IParseDisplayName =			__uuid(IParseDisplayName);
EXTERN_C __export const IID IID_IOleContainer =				__uuid(IOleContainer);
EXTERN_C __export const IID IID_IDropSource =				__uuid(IDropSource);
EXTERN_C __export const IID IID_IDropTarget =				__uuid(IDropTarget);

// -------------------------------------------------------------------------
// propidl.h
EXTERN_C __export const IID IID_IPropertyStorage =			__uuid(IPropertyStorage);
EXTERN_C __export const IID IID_IPropertySetStorage =		__uuid(IPropertySetStorage);
EXTERN_C __export const IID IID_IEnumSTATPROPSTG =			__uuid(IEnumSTATPROPSTG);
EXTERN_C __export const IID IID_IEnumSTATPROPSETSTG =		__uuid(IEnumSTATPROPSETSTG);

// -------------------------------------------------------------------------
// oaidl.h
EXTERN_C __export const IID IID_IEnumVARIANT =				__uuid(IEnumVARIANT);
EXTERN_C __export const IID IID_ITypeLib =					__uuid(ITypeLib);
EXTERN_C __export const IID IID_ITypeComp =					__uuid(ITypeComp);
EXTERN_C __export const IID IID_ITypeInfo =					__uuid(ITypeInfo);
EXTERN_C __export const IID IID_IDispatch =					__uuid(IDispatch);
EXTERN_C __export const IID IID_ICreateErrorInfo =			__uuid(ICreateErrorInfo);
EXTERN_C __export const IID IID_IErrorInfo =				__uuid(IErrorInfo);
EXTERN_C __export const IID IID_IErrorLog =					__uuid(IErrorLog);
EXTERN_C __export const IID IID_IPropertyBag =				__uuid(IPropertyBag);

// -------------------------------------------------------------------------
typedef GUID FMTID;
EXTERN_C __export const FMTID FMTID_SummaryInformation = {0xF29F85E0, 0x4FF9, 0x1068, {0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9}};
EXTERN_C __export const FMTID FMTID_DocSummaryInformation = {0xD5CDD502, 0x2E9C, 0x101B, {0x93, 0x97, 0x08, 0x00, 0x2B, 0x2C, 0xF9, 0xAE}};
EXTERN_C __export const FMTID FMTID_UserDefinedProperties = {0xD5CDD505, 0x2E9C, 0x101B, {0x93, 0x97, 0x08, 0x00, 0x2B, 0x2C, 0xF9, 0xAE}};
EXTERN_C __export const FMTID FMTID_DiscardableInformation = {0xD725EBB0, 0xC9B8, 0x11D1, {0x89, 0xBC, 0x00, 0x00, 0xF8, 0x04, 0xB0, 0x57}};
EXTERN_C __export const FMTID FMTID_ImageSummaryInformation = {0x6444048F, 0x4C8B, 0x11D1, {0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03}};
EXTERN_C __export const FMTID FMTID_AudioSummaryInformation = {0x64440490, 0x4C8B, 0x11D1, {0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03}};
EXTERN_C __export const FMTID FMTID_VideoSummaryInformation = {0x64440491, 0x4C8B, 0x11D1, {0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03}};
EXTERN_C __export const FMTID FMTID_MediaFileSummaryInformation = {0x64440492, 0x4C8B, 0x11D1, {0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03}};

// -------------------------------------------------------------------------
void _force_link_guiddef() {}

