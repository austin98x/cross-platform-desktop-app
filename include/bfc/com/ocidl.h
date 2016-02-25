/* -------------------------------------------------------------------------
//	File name		：	ocidl.h
//	Author 			：	Austin
//	Create Time		：	2016-2-25 11:46:34
//	Description 	：	Define interface for Linux platform
//
// -----------------------------------------------------------------------*/
#ifndef __OCIDL_H__
#define __OCIDL_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

interface IConnectionPointContainer;
interface IEnumConnections;
interface IConnectionPoint;

// -------------------------------------------------------------------------

MIDL_INTERFACE_("B196B286-BAB4-101A-B69C-00AA00341D07", IConnectionPoint)
	: public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetConnectionInterface(
		/* [out] */ IID *pIID) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetConnectionPointContainer(
		/* [out] */ IConnectionPointContainer **ppCPC) = 0;

	virtual HRESULT STDMETHODCALLTYPE Advise(
		/* [in] */ IUnknown *pUnkSink,
		/* [out] */ DWORD *pdwCookie) = 0;

	virtual HRESULT STDMETHODCALLTYPE Unadvise(
		/* [in] */ DWORD dwCookie) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumConnections(
		/* [out] */ IEnumConnections **ppEnum) = 0;

};

typedef IConnectionPoint *LPCONNECTIONPOINT;

// -------------------------------------------------------------------------

MIDL_INTERFACE_("B196B285-BAB4-101A-B69C-00AA00341D07", IEnumConnectionPoints)
	: public IUnknown
{
public:
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG cConnections,
		/* [length_is][size_is][out] */ LPCONNECTIONPOINT *ppCP,
		/* [out] */ ULONG *pcFetched) = 0;

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG cConnections) = 0;

	virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ IEnumConnectionPoints **ppEnum) = 0;

};

// -------------------------------------------------------------------------

MIDL_INTERFACE_("B196B284-BAB4-101A-B69C-00AA00341D07", IConnectionPointContainer)
 : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE EnumConnectionPoints( 
        /* [out] */ IEnumConnectionPoints __RPC_FAR *__RPC_FAR *ppEnum) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE FindConnectionPoint( 
        /* [in] */ REFIID riid,
        /* [out] */ IConnectionPoint __RPC_FAR *__RPC_FAR *ppCP) = 0;
    
};

// -------------------------------------------------------------------------

//#pragma pack(1)

typedef struct  tagCONNECTDATA
{
    IUnknown __RPC_FAR *pUnk;
    DWORD dwCookie;
}	CONNECTDATA;

//#pragma pack()

typedef struct tagCONNECTDATA __RPC_FAR* PCONNECTDATA;
typedef struct tagCONNECTDATA __RPC_FAR* LPCONNECTDATA;

MIDL_INTERFACE_("B196B287-BAB4-101A-B69C-00AA00341D07", IEnumConnections)
 : public IUnknown
{
public:
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
        /* [in] */ ULONG cConnections,
        /* [length_is][size_is][out] */ LPCONNECTDATA rgcd,
        /* [out] */ ULONG __RPC_FAR *pcFetched) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Skip( 
        /* [in] */ ULONG cConnections) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Clone( 
        /* [out] */ IEnumConnections __RPC_FAR *__RPC_FAR *ppEnum) = 0;
    
};

// -------------------------------------------------------------------------

typedef IConnectionPointContainer __RPC_FAR *PCONNECTIONPOINTCONTAINER;
typedef IConnectionPointContainer __RPC_FAR *LPCONNECTIONPOINTCONTAINER;

typedef IConnectionPoint __RPC_FAR *PCONNECTIONPOINT;
typedef IConnectionPoint __RPC_FAR *LPCONNECTIONPOINT;

typedef IEnumConnections __RPC_FAR *PENUMCONNECTIONS;
typedef IEnumConnections __RPC_FAR *LPENUMCONNECTIONS;

EXTERN_C const IID IID_IEnumConnections;
EXTERN_C const IID IID_IConnectionPoint;
EXTERN_C const IID IID_IConnectionPointContainer;

// -------------------------------------------------------------------------

#endif /* __OCIDL_H__ */
