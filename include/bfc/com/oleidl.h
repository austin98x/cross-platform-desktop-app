/* -------------------------------------------------------------------------
//	File name		：	oleidl.h
//	Author 			：	Austin
//	Create Time		：	2016-2-25 12:38:45
//	Description 	：	Define interface for Linux platform
//
// -----------------------------------------------------------------------*/
#ifndef __OLEIDL_H__
#define __OLEIDL_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

#if 0
typedef /* [unique] */ IOleAdviseHolder *LPOLEADVISEHOLDER;

EXTERN_C const IID IID_IOleAdviseHolder;

MIDL_INTERFACE("00000111-0000-0000-C000-000000000046")
IOleAdviseHolder : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE Advise(
        /* [unique][in] */ IAdviseSink *pAdvise,
        /* [out] */ DWORD *pdwConnection) = 0;

    virtual HRESULT STDMETHODCALLTYPE Unadvise(
        /* [in] */ DWORD dwConnection) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumAdvise(
        /* [out] */ IEnumSTATDATA **ppenumAdvise) = 0;

    virtual HRESULT STDMETHODCALLTYPE SendOnRename(
        /* [unique][in] */ IMoniker *pmk) = 0;

    virtual HRESULT STDMETHODCALLTYPE SendOnSave( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE SendOnClose( void) = 0;

};

typedef /* [unique] */ IOleCache *LPOLECACHE;

EXTERN_C const IID IID_IOleCache;

MIDL_INTERFACE("0000011e-0000-0000-C000-000000000046")
IOleCache : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE Cache(
		/* [unique][in] */ FORMATETC *pformatetc,
        /* [in] */ DWORD advf,
		/* [out] */ DWORD *pdwConnection) = 0;

    virtual HRESULT STDMETHODCALLTYPE Uncache(
        /* [in] */ DWORD dwConnection) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumCache(
		/* [out] */ IEnumSTATDATA **ppenumSTATDATA) = 0;

    virtual HRESULT STDMETHODCALLTYPE InitCache(
		/* [unique][in] */ IDataObject *pDataObject) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetData(
		/* [unique][in] */ FORMATETC *pformatetc,
		/* [unique][in] */ STGMEDIUM *pmedium,
        /* [in] */ BOOL fRelease) = 0;

};

typedef /* [unique] */ IOleCache2 *LPOLECACHE2;

#define	UPDFCACHE_NODATACACHE	( 0x1 )

#define	UPDFCACHE_ONSAVECACHE	( 0x2 )

#define	UPDFCACHE_ONSTOPCACHE	( 0x4 )

#define	UPDFCACHE_NORMALCACHE	( 0x8 )

#define	UPDFCACHE_IFBLANK	( 0x10 )

#define	UPDFCACHE_ONLYIFBLANK	( 0x80000000 )

#define	UPDFCACHE_IFBLANKORONSAVECACHE	( ( UPDFCACHE_IFBLANK | UPDFCACHE_ONSAVECACHE )  )

#define	UPDFCACHE_ALL	( ( DWORD  )~UPDFCACHE_ONLYIFBLANK )

#define	UPDFCACHE_ALLBUTNODATACACHE	( ( UPDFCACHE_ALL & ( DWORD  )~UPDFCACHE_NODATACACHE )  )

typedef /* [v1_enum] */
enum tagDISCARDCACHE
{
	DISCARDCACHE_SAVEIFDIRTY	= 0,
	DISCARDCACHE_NOSAVE	= 1
} 	DISCARDCACHE;


EXTERN_C const IID IID_IOleCache2;

MIDL_INTERFACE("00000128-0000-0000-C000-000000000046")
IOleCache2 : public IOleCache
{
public:
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE UpdateCache(
        /* [in] */ LPDATAOBJECT pDataObject,
        /* [in] */ DWORD grfUpdf,
        /* [in] */ LPVOID pReserved) = 0;

    virtual HRESULT STDMETHODCALLTYPE DiscardCache(
        /* [in] */ DWORD dwDiscardOptions) = 0;

};

typedef /* [unique] */ IOleCacheControl *LPOLECACHECONTROL;

EXTERN_C const IID IID_IOleCacheControl;

MIDL_INTERFACE("00000129-0000-0000-C000-000000000046")
IOleCacheControl : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE OnRun(
		LPDATAOBJECT pDataObject) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnStop( void) = 0;

};
#endif

// -------------------------------------------------------------------------

EXTERN_C const IID IID_IParseDisplayName;

MIDL_INTERFACE_("0000011a-0000-0000-C000-000000000046", IParseDisplayName)
	: public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE ParseDisplayName(
		/* [unique][in] */ IBindCtx *pbc,
		/* [in] */ LPOLESTR pszDisplayName,
		/* [out] */ ULONG *pchEaten,
		/* [out] */ IMoniker **ppmkOut) = 0;
};

typedef /* [unique] */ IParseDisplayName *LPPARSEDISPLAYNAME;

// -------------------------------------------------------------------------

EXTERN_C const IID IID_IOleContainer;

MIDL_INTERFACE_("0000011b-0000-0000-C000-000000000046", IOleContainer)
	: public IParseDisplayName
{
public:
    virtual HRESULT STDMETHODCALLTYPE EnumObjects(
        /* [in] */ DWORD grfFlags,
		/* [out] */ IEnumUnknown **ppenum) = 0;

    virtual HRESULT STDMETHODCALLTYPE LockContainer(
        /* [in] */ BOOL fLock) = 0;
};

typedef /* [unique] */ IOleContainer *LPOLECONTAINER;

// -------------------------------------------------------------------------

EXTERN_C const IID IID_IOleItemContainer;

MIDL_INTERFACE_("0000011c-0000-0000-C000-000000000046", IOleItemContainer)
	: public IOleContainer
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetObject(
		/* [in] */ LPOLESTR pszItem,
		/* [in] */ DWORD dwSpeedNeeded,
		/* [unique][in] */ IBindCtx *pbc,
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void **ppvObject) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetObjectStorage(
		/* [in] */ LPOLESTR pszItem,
		/* [unique][in] */ IBindCtx *pbc,
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void **ppvStorage) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsRunning(
		/* [in] */ LPOLESTR pszItem) = 0;

};

typedef /* [unique] */ IOleItemContainer *LPOLEITEMCONTAINER;

// -------------------------------------------------------------------------

EXTERN_C const IID IID_IOleClientSite;

MIDL_INTERFACE_("00000118-0000-0000-C000-000000000046", IOleClientSite)
	: public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE SaveObject( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMoniker(
        /* [in] */ DWORD dwAssign,
        /* [in] */ DWORD dwWhichMoniker,
		/* [out] */ IMoniker **ppmk) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetContainer(
		/* [out] */ IOleContainer **ppContainer) = 0;

    virtual HRESULT STDMETHODCALLTYPE ShowObject( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnShowWindow(
        /* [in] */ BOOL fShow) = 0;

    virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout( void) = 0;
};

typedef /* [unique] */ IOleClientSite *LPOLECLIENTSITE;

// -------------------------------------------------------------------------

#if 0
typedef
enum tagOLEGETMONIKER
{
	OLEGETMONIKER_ONLYIFTHERE	= 1,
	OLEGETMONIKER_FORCEASSIGN	= 2,
	OLEGETMONIKER_UNASSIGN	= 3,
	OLEGETMONIKER_TEMPFORUSER	= 4
} 	OLEGETMONIKER;

typedef
enum tagOLEWHICHMK
{
	OLEWHICHMK_CONTAINER	= 1,
	OLEWHICHMK_OBJREL	= 2,
	OLEWHICHMK_OBJFULL	= 3
} 	OLEWHICHMK;

typedef
enum tagUSERCLASSTYPE
{
	USERCLASSTYPE_FULL	= 1,
	USERCLASSTYPE_SHORT	= 2,
	USERCLASSTYPE_APPNAME	= 3
} 	USERCLASSTYPE;
#endif

typedef
enum tagOLEMISC
{
	OLEMISC_RECOMPOSEONRESIZE	= 0x1,
	OLEMISC_ONLYICONIC	= 0x2,
	OLEMISC_INSERTNOTREPLACE	= 0x4,
	OLEMISC_STATIC	= 0x8,
	OLEMISC_CANTLINKINSIDE	= 0x10,
	OLEMISC_CANLINKBYOLE1	= 0x20,
	OLEMISC_ISLINKOBJECT	= 0x40,
	OLEMISC_INSIDEOUT	= 0x80,
	OLEMISC_ACTIVATEWHENVISIBLE	= 0x100,
	OLEMISC_RENDERINGISDEVICEINDEPENDENT	= 0x200,
	OLEMISC_INVISIBLEATRUNTIME	= 0x400,
	OLEMISC_ALWAYSRUN	= 0x800,
	OLEMISC_ACTSLIKEBUTTON	= 0x1000,
	OLEMISC_ACTSLIKELABEL	= 0x2000,
	OLEMISC_NOUIACTIVATE	= 0x4000,
	OLEMISC_ALIGNABLE	= 0x8000,
	OLEMISC_SIMPLEFRAME	= 0x10000,
	OLEMISC_SETCLIENTSITEFIRST	= 0x20000,
	OLEMISC_IMEMODE	= 0x40000,
	OLEMISC_IGNOREACTIVATEWHENVISIBLE	= 0x80000,
	OLEMISC_WANTSTOMENUMERGE	= 0x100000,
	OLEMISC_SUPPORTSMULTILEVELUNDO	= 0x200000
} 	OLEMISC;

typedef
enum tagOLECLOSE
{
	OLECLOSE_SAVEIFDIRTY	= 0,
	OLECLOSE_NOSAVE	= 1,
	OLECLOSE_PROMPTSAVE	= 2
} 	OLECLOSE;

typedef struct tagLOGPALETTE LOGPALETTE;

typedef void* LPMSG;
typedef void* HWND;

struct IEnumOLEVERB;
EXTERN_C const IID IID_IOleObject;

MIDL_INTERFACE_("00000112-0000-0000-C000-000000000046", IOleObject)
	: public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE SetClientSite(
		/* [unique][in] */ IOleClientSite *pClientSite) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetClientSite(
		/* [out] */ IOleClientSite **ppClientSite) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetHostNames(
		/* [in] */ LPCOLESTR szContainerApp,
		/* [unique][in] */ LPCOLESTR szContainerObj) = 0;

    virtual HRESULT STDMETHODCALLTYPE Close(
        /* [in] */ DWORD dwSaveOption) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetMoniker(
        /* [in] */ DWORD dwWhichMoniker,
		/* [unique][in] */ IMoniker *pmk) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMoniker(
        /* [in] */ DWORD dwAssign,
        /* [in] */ DWORD dwWhichMoniker,
		/* [out] */ IMoniker **ppmk) = 0;

    virtual HRESULT STDMETHODCALLTYPE InitFromData(
		/* [unique][in] */ IDataObject *pDataObject,
        /* [in] */ BOOL fCreation,
        /* [in] */ DWORD dwReserved) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetClipboardData(
        /* [in] */ DWORD dwReserved,
		/* [out] */ IDataObject **ppDataObject) = 0;

    virtual HRESULT STDMETHODCALLTYPE DoVerb(
        /* [in] */ LONG iVerb,
		/* [unique][in] */ LPMSG lpmsg,
		/* [unique][in] */ IOleClientSite *pActiveSite,
        /* [in] */ LONG lindex,
		/* [in] */ HWND hwndParent,
		/* [unique][in] */ LPCRECT lprcPosRect) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumVerbs(
		/* [out] */ IEnumOLEVERB **ppEnumOleVerb) = 0;

    virtual HRESULT STDMETHODCALLTYPE Update( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE IsUpToDate( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetUserClassID(
		/* [out] */ CLSID *pClsid) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetUserType(
        /* [in] */ DWORD dwFormOfType,
		/* [out] */ LPOLESTR *pszUserType) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetExtent(
        /* [in] */ DWORD dwDrawAspect,
		/* [in] */ SIZEL *psizel) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetExtent(
        /* [in] */ DWORD dwDrawAspect,
		/* [out] */ SIZEL *psizel) = 0;

    virtual HRESULT STDMETHODCALLTYPE Advise(
		/* [unique][in] */ IAdviseSink *pAdvSink,
		/* [out] */ DWORD *pdwConnection) = 0;

    virtual HRESULT STDMETHODCALLTYPE Unadvise(
        /* [in] */ DWORD dwConnection) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnumAdvise(
		/* [out] */ IEnumSTATDATA **ppenumAdvise) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMiscStatus(
        /* [in] */ DWORD dwAspect,
		/* [out] */ DWORD *pdwStatus) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetColorScheme(
		/* [in] */ LOGPALETTE *pLogpal) = 0;

};

typedef /* [unique] */ IOleObject *LPOLEOBJECT;

typedef
enum tagOLERENDER
{
	OLERENDER_NONE	= 0,
	OLERENDER_DRAW	= 1,
	OLERENDER_FORMAT	= 2,
	OLERENDER_ASIS	= 3
} 	OLERENDER;

typedef OLERENDER *LPOLERENDER;

typedef struct tagOBJECTDESCRIPTOR
{
	UINT32 cbSize;
	CLSID clsid;
	DWORD dwDrawAspect;
	SIZE sizel;
	POINT pointl;
	DWORD dwStatus;
	DWORD dwFullUserTypeName;
	DWORD dwSrcOfCopy;
} 	OBJECTDESCRIPTOR;

typedef struct tagOBJECTDESCRIPTOR *POBJECTDESCRIPTOR;

typedef struct tagOBJECTDESCRIPTOR *LPOBJECTDESCRIPTOR;

typedef struct tagOBJECTDESCRIPTOR LINKSRCDESCRIPTOR;

typedef struct tagOBJECTDESCRIPTOR *PLINKSRCDESCRIPTOR;

typedef struct tagOBJECTDESCRIPTOR *LPLINKSRCDESCRIPTOR;

//-------------------------------------------------------------------------

#if 0
typedef /* [unique] */ IOleWindow *LPOLEWINDOW;

EXTERN_C const IID IID_IOleWindow;

MIDL_INTERFACE("00000114-0000-0000-C000-000000000046")
IOleWindow : public IUnknown
{
public:
    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow(
		/* [out] */ HWND *phwnd) = 0;

    virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(
        /* [in] */ BOOL fEnterMode) = 0;
};

typedef /* [unique] */ IOleLink *LPOLELINK;

typedef
enum tagOLEUPDATE
{	OLEUPDATE_ALWAYS	= 1,
	OLEUPDATE_ONCALL	= 3
} 	OLEUPDATE;

typedef OLEUPDATE *LPOLEUPDATE;

typedef OLEUPDATE *POLEUPDATE;

typedef
enum tagOLELINKBIND
{
	OLELINKBIND_EVENIFCLASSDIFF	= 1
} 	OLELINKBIND;


EXTERN_C const IID IID_IOleLink;

MIDL_INTERFACE("0000011d-0000-0000-C000-000000000046")
IOleLink : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE SetUpdateOptions(
        /* [in] */ DWORD dwUpdateOpt) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetUpdateOptions(
		/* [out] */ DWORD *pdwUpdateOpt) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetSourceMoniker(
		/* [unique][in] */ IMoniker *pmk,
		/* [in] */ REFCLSID rclsid) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetSourceMoniker(
		/* [out] */ IMoniker **ppmk) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetSourceDisplayName(
		/* [in] */ LPCOLESTR pszStatusText) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetSourceDisplayName(
		/* [out] */ LPOLESTR *ppszDisplayName) = 0;

    virtual HRESULT STDMETHODCALLTYPE BindToSource(
        /* [in] */ DWORD bindflags,
		/* [unique][in] */ IBindCtx *pbc) = 0;

    virtual HRESULT STDMETHODCALLTYPE BindIfRunning( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetBoundSource(
		/* [out] */ IUnknown **ppunk) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnbindSource( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE Update(
		/* [unique][in] */ IBindCtx *pbc) = 0;
};

typedef
enum tagBINDSPEED
{
	BINDSPEED_INDEFINITE	= 1,
	BINDSPEED_MODERATE	= 2,
	BINDSPEED_IMMEDIATE	= 3
} 	BINDSPEED;

typedef /* [v1_enum] */
enum tagOLECONTF
{
	OLECONTF_EMBEDDINGS	= 1,
	OLECONTF_LINKS	= 2,
	OLECONTF_OTHERS	= 4,
	OLECONTF_ONLYUSER	= 8,
	OLECONTF_ONLYIFRUNNING	= 16
} 	OLECONTF;

typedef /* [unique] */ IOleInPlaceUIWindow *LPOLEINPLACEUIWINDOW;

typedef RECT BORDERWIDTHS;

typedef LPRECT LPBORDERWIDTHS;

typedef LPCRECT LPCBORDERWIDTHS;


EXTERN_C const IID IID_IOleInPlaceUIWindow;

MIDL_INTERFACE("00000115-0000-0000-C000-000000000046")
IOleInPlaceUIWindow : public IOleWindow
{
public:
    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetBorder(
		/* [out] */ LPRECT lprectBorder) = 0;

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE RequestBorderSpace(
		/* [unique][in] */ LPCBORDERWIDTHS pborderwidths) = 0;

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetBorderSpace(
		/* [unique][in] */ LPCBORDERWIDTHS pborderwidths) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetActiveObject(
		/* [unique][in] */ IOleInPlaceActiveObject *pActiveObject,
		/* [unique][string][in] */ LPCOLESTR pszObjName) = 0;
};

typedef /* [unique] */ IOleInPlaceActiveObject *LPOLEINPLACEACTIVEOBJECT;


EXTERN_C const IID IID_IOleInPlaceActiveObject;

MIDL_INTERFACE("00000117-0000-0000-C000-000000000046")
IOleInPlaceActiveObject : public IOleWindow
{
public:
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE TranslateAccelerator(
        /* [in] */ LPMSG lpmsg) = 0;

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(
        /* [in] */ BOOL fActivate) = 0;

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE OnDocWindowActivate(
        /* [in] */ BOOL fActivate) = 0;

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE ResizeBorder(
        /* [in] */ LPCRECT prcBorder,
        /* [unique][in] */ IOleInPlaceUIWindow *pUIWindow,
        /* [in] */ BOOL fFrameWindow) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnableModeless(
        /* [in] */ BOOL fEnable) = 0;

};

typedef /* [unique] */ IOleInPlaceFrame *LPOLEINPLACEFRAME;

typedef struct tagOIFI
{
	UINT cb;
	BOOL fMDIApp;
	HWND hwndFrame;
	HACCEL haccel;
	UINT cAccelEntries;
} 	OLEINPLACEFRAMEINFO;

typedef struct tagOIFI *LPOLEINPLACEFRAMEINFO;

typedef struct tagOleMenuGroupWidths
{
	LONG width[ 6 ];
} 	OLEMENUGROUPWIDTHS;

typedef struct tagOleMenuGroupWidths *LPOLEMENUGROUPWIDTHS;

typedef HGLOBAL HOLEMENU;


EXTERN_C const IID IID_IOleInPlaceFrame;

MIDL_INTERFACE("00000116-0000-0000-C000-000000000046")
IOleInPlaceFrame : public IOleInPlaceUIWindow
{
public:
    virtual HRESULT STDMETHODCALLTYPE InsertMenus(
		/* [in] */ HMENU hmenuShared,
		/* [out][in] */ LPOLEMENUGROUPWIDTHS lpMenuWidths) = 0;

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetMenu(
		/* [in] */ HMENU hmenuShared,
		/* [in] */ HOLEMENU holemenu,
		/* [in] */ HWND hwndActiveObject) = 0;

    virtual HRESULT STDMETHODCALLTYPE RemoveMenus(
		/* [in] */ HMENU hmenuShared) = 0;

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetStatusText(
		/* [unique][in] */ LPCOLESTR pszStatusText) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnableModeless(
        /* [in] */ BOOL fEnable) = 0;

    virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(
		/* [in] */ LPMSG lpmsg,
        /* [in] */ WORD wID) = 0;

};

typedef /* [unique] */ IOleInPlaceObject *LPOLEINPLACEOBJECT;


EXTERN_C const IID IID_IOleInPlaceObject;

MIDL_INTERFACE("00000113-0000-0000-C000-000000000046")
IOleInPlaceObject : public IOleWindow
{
public:
    virtual HRESULT STDMETHODCALLTYPE InPlaceDeactivate( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE UIDeactivate( void) = 0;

    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetObjectRects(
		/* [in] */ LPCRECT lprcPosRect,
		/* [in] */ LPCRECT lprcClipRect) = 0;

    virtual HRESULT STDMETHODCALLTYPE ReactivateAndUndo( void) = 0;

};

typedef /* [unique] */ IOleInPlaceSite *LPOLEINPLACESITE;


EXTERN_C const IID IID_IOleInPlaceSite;

MIDL_INTERFACE("00000119-0000-0000-C000-000000000046")
IOleInPlaceSite : public IOleWindow
{
public:
    virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnUIActivate( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetWindowContext(
		/* [out] */ IOleInPlaceFrame **ppFrame,
		/* [out] */ IOleInPlaceUIWindow **ppDoc,
		/* [out] */ LPRECT lprcPosRect,
		/* [out] */ LPRECT lprcClipRect,
		/* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo) = 0;

    virtual HRESULT STDMETHODCALLTYPE Scroll(
        /* [in] */ SIZE scrollExtant) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(
        /* [in] */ BOOL fUndoable) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE DiscardUndoState( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnPosRectChange(
		/* [in] */ LPCRECT lprcPosRect) = 0;

};

EXTERN_C const IID IID_IContinue;

MIDL_INTERFACE("0000012a-0000-0000-C000-000000000046")
IContinue : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE FContinue( void) = 0;
};

typedef /* [unique] */ IViewObject *LPVIEWOBJECT;

EXTERN_C const IID IID_IViewObject;

MIDL_INTERFACE("0000010d-0000-0000-C000-000000000046")
IViewObject : public IUnknown
{
public:
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Draw(
        /* [in] */ DWORD dwDrawAspect,
        /* [in] */ LONG lindex,
        /* [unique][in] */ void *pvAspect,
        /* [unique][in] */ DVTARGETDEVICE *ptd,
        /* [in] */ HDC hdcTargetDev,
        /* [in] */ HDC hdcDraw,
        /* [in] */ LPCRECTL lprcBounds,
        /* [unique][in] */ LPCRECTL lprcWBounds,
        /* [in] */ BOOL ( STDMETHODCALLTYPE *pfnContinue )(
            ULONG_PTR dwContinue),
        /* [in] */ ULONG_PTR dwContinue) = 0;

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetColorSet(
        /* [in] */ DWORD dwDrawAspect,
        /* [in] */ LONG lindex,
        /* [unique][in] */ void *pvAspect,
        /* [unique][in] */ DVTARGETDEVICE *ptd,
        /* [in] */ HDC hicTargetDev,
        /* [out] */ LOGPALETTE **ppColorSet) = 0;

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Freeze(
        /* [in] */ DWORD dwDrawAspect,
        /* [in] */ LONG lindex,
        /* [unique][in] */ void *pvAspect,
        /* [out] */ DWORD *pdwFreeze) = 0;

    virtual HRESULT STDMETHODCALLTYPE Unfreeze(
        /* [in] */ DWORD dwFreeze) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetAdvise(
        /* [in] */ DWORD aspects,
        /* [in] */ DWORD advf,
		/* [unique][in] */ IAdviseSink *pAdvSink) = 0;

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetAdvise(
        /* [unique][out] */ DWORD *pAspects,
        /* [unique][out] */ DWORD *pAdvf,
        /* [out] */ IAdviseSink **ppAdvSink) = 0;

};

typedef /* [unique] */ IViewObject2 *LPVIEWOBJECT2;


EXTERN_C const IID IID_IViewObject2;

MIDL_INTERFACE("00000127-0000-0000-C000-000000000046")
IViewObject2 : public IViewObject
{
public:
    virtual HRESULT STDMETHODCALLTYPE GetExtent(
        /* [in] */ DWORD dwDrawAspect,
        /* [in] */ LONG lindex,
		/* [unique][in] */ DVTARGETDEVICE *ptd,
		/* [out] */ LPSIZEL lpsizel) = 0;
};

#endif

// -------------------------------------------------------------------------

EXTERN_C const IID IID_IDropSource;

MIDL_INTERFACE_("00000121-0000-0000-C000-000000000046", IDropSource)
    : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE QueryContinueDrag(
        /* [in] */ BOOL fEscapePressed,
        /* [in] */ DWORD grfKeyState) = 0;

    virtual HRESULT STDMETHODCALLTYPE GiveFeedback(
        /* [in] */ DWORD dwEffect) = 0;

};

typedef /* [unique] */ IDropSource *LPDROPSOURCE;

//-------------------------------------------------------------------------

#define	MK_ALT	( 0x20 )

#define	DROPEFFECT_NONE	( 0 )

#define	DROPEFFECT_COPY	( 1 )

#define	DROPEFFECT_MOVE	( 2 )

#define	DROPEFFECT_LINK	( 4 )

#define	DROPEFFECT_SCROLL	( 0x80000000 )

// default inset-width of the hot zone, in pixels
//   typical use: GetProfileInt("windows","DragScrollInset",DD_DEFSCROLLINSET)
#define	DD_DEFSCROLLINSET	( 11 )

// default delay before scrolling, in milliseconds
//   typical use: GetProfileInt("windows","DragScrollDelay",DD_DEFSCROLLDELAY)
#define	DD_DEFSCROLLDELAY	( 50 )

// default scroll interval, in milliseconds
//   typical use: GetProfileInt("windows","DragScrollInterval", DD_DEFSCROLLINTERVAL)
#define	DD_DEFSCROLLINTERVAL	( 50 )

// default delay before dragging should start, in milliseconds
//   typical use: GetProfileInt("windows", "DragDelay", DD_DEFDRAGDELAY)
#define	DD_DEFDRAGDELAY	( 200 )

// default minimum distance (radius) before dragging should start, in pixels
//   typical use: GetProfileInt("windows", "DragMinDist", DD_DEFDRAGMINDIST)
#define	DD_DEFDRAGMINDIST	( 2 )

EXTERN_C const IID IID_IDropTarget;

MIDL_INTERFACE_("00000122-0000-0000-C000-000000000046", IDropTarget)
    : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE DragEnter(
		/* [unique][in] */ IDataObject *pDataObj,
        /* [in] */ DWORD grfKeyState,
        /* [in] */ POINTL pt,
		/* [out][in] */ DWORD *pdwEffect) = 0;

    virtual HRESULT STDMETHODCALLTYPE DragOver(
        /* [in] */ DWORD grfKeyState,
        /* [in] */ POINTL pt,
		/* [out][in] */ DWORD *pdwEffect) = 0;

    virtual HRESULT STDMETHODCALLTYPE DragLeave( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE Drop(
		/* [unique][in] */ IDataObject *pDataObj,
        /* [in] */ DWORD grfKeyState,
        /* [in] */ POINTL pt,
		/* [out][in] */ DWORD *pdwEffect) = 0;

};

typedef /* [unique] */ IDropTarget *LPDROPTARGET;

//-------------------------------------------------------------------------

#if 0

EXTERN_C const IID IID_IDropSourceNotify;

MIDL_INTERFACE("0000012B-0000-0000-C000-000000000046")
IDropSourceNotify : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE DragEnterTarget(
        /* [in] */ HWND hwndTarget) = 0;

    virtual HRESULT STDMETHODCALLTYPE DragLeaveTarget( void) = 0;

};

#endif

// -------------------------------------------------------------------------

typedef struct tagOLEVERB *LPOLEVERB;

typedef /* [v1_enum] */
enum tagOLEVERBATTRIB
{
	OLEVERBATTRIB_NEVERDIRTIES	= 1,
	OLEVERBATTRIB_ONCONTAINERMENU	= 2
} 	OLEVERBATTRIB;

EXTERN_C const IID IID_IEnumOLEVERB;

MIDL_INTERFACE_("00000104-0000-0000-C000-000000000046", IEnumOLEVERB)
	: public IUnknown
{
public:
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next(
        /* [in] */ ULONG celt,
        /* [length_is][size_is][out] */ LPOLEVERB rgelt,
        /* [out] */ ULONG *pceltFetched) = 0;

    virtual HRESULT STDMETHODCALLTYPE Skip(
        /* [in] */ ULONG celt) = 0;

    virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ IEnumOLEVERB **ppenum) = 0;

};

typedef /* [unique] */ IEnumOLEVERB *LPENUMOLEVERB;

//-------------------------------------------------------------------------

#if 0
/* Additional Prototypes for ALL interfaces * /

unsigned long     CLIPFORMAT_UserSize(     unsigned long *, unsigned long            , CLIPFORMAT * );
unsigned char *   CLIPFORMAT_UserMarshal(  unsigned long *, unsigned char *, CLIPFORMAT * );
unsigned char *   CLIPFORMAT_UserUnmarshal(unsigned long *, unsigned char *, CLIPFORMAT * );
void              CLIPFORMAT_UserFree(     unsigned long *, CLIPFORMAT * );

unsigned long     HACCEL_UserSize(     unsigned long *, unsigned long            , HACCEL * );
unsigned char *   HACCEL_UserMarshal(  unsigned long *, unsigned char *, HACCEL * );
unsigned char *   HACCEL_UserUnmarshal(unsigned long *, unsigned char *, HACCEL * );
void              HACCEL_UserFree(     unsigned long *, HACCEL * );

unsigned long     HDC_UserSize(     unsigned long *, unsigned long            , HDC * );
unsigned char *   HDC_UserMarshal(  unsigned long *, unsigned char *, HDC * );
unsigned char *   HDC_UserUnmarshal(unsigned long *, unsigned char *, HDC * );
void              HDC_UserFree(     unsigned long *, HDC * );

unsigned long     HGLOBAL_UserSize(     unsigned long *, unsigned long            , HGLOBAL * );
unsigned char *   HGLOBAL_UserMarshal(  unsigned long *, unsigned char *, HGLOBAL * );
unsigned char *   HGLOBAL_UserUnmarshal(unsigned long *, unsigned char *, HGLOBAL * );
void              HGLOBAL_UserFree(     unsigned long *, HGLOBAL * );

unsigned long     HMENU_UserSize(     unsigned long *, unsigned long            , HMENU * );
unsigned char *   HMENU_UserMarshal(  unsigned long *, unsigned char *, HMENU * );
unsigned char *   HMENU_UserUnmarshal(unsigned long *, unsigned char *, HMENU * );
void              HMENU_UserFree(     unsigned long *, HMENU * );

unsigned long     HWND_UserSize(     unsigned long *, unsigned long            , HWND * );
unsigned char *   HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * );
unsigned char *   HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * );
void              HWND_UserFree(     unsigned long *, HWND * );

unsigned long     STGMEDIUM_UserSize(     unsigned long *, unsigned long            , STGMEDIUM * );
unsigned char *   STGMEDIUM_UserMarshal(  unsigned long *, unsigned char *, STGMEDIUM * );
unsigned char *   STGMEDIUM_UserUnmarshal(unsigned long *, unsigned char *, STGMEDIUM * );
void              STGMEDIUM_UserFree(     unsigned long *, STGMEDIUM * );

unsigned long     CLIPFORMAT_UserSize64(     unsigned long *, unsigned long            , CLIPFORMAT * );
unsigned char *   CLIPFORMAT_UserMarshal64(  unsigned long *, unsigned char *, CLIPFORMAT * );
unsigned char *   CLIPFORMAT_UserUnmarshal64(unsigned long *, unsigned char *, CLIPFORMAT * );
void              CLIPFORMAT_UserFree64(     unsigned long *, CLIPFORMAT * );

unsigned long     HACCEL_UserSize64(     unsigned long *, unsigned long            , HACCEL * );
unsigned char *   HACCEL_UserMarshal64(  unsigned long *, unsigned char *, HACCEL * );
unsigned char *   HACCEL_UserUnmarshal64(unsigned long *, unsigned char *, HACCEL * );
void              HACCEL_UserFree64(     unsigned long *, HACCEL * );

unsigned long     HDC_UserSize64(     unsigned long *, unsigned long            , HDC * );
unsigned char *   HDC_UserMarshal64(  unsigned long *, unsigned char *, HDC * );
unsigned char *   HDC_UserUnmarshal64(unsigned long *, unsigned char *, HDC * );
void              HDC_UserFree64(     unsigned long *, HDC * );

unsigned long     HGLOBAL_UserSize64(     unsigned long *, unsigned long            , HGLOBAL * );
unsigned char *   HGLOBAL_UserMarshal64(  unsigned long *, unsigned char *, HGLOBAL * );
unsigned char *   HGLOBAL_UserUnmarshal64(unsigned long *, unsigned char *, HGLOBAL * );
void              HGLOBAL_UserFree64(     unsigned long *, HGLOBAL * );

unsigned long     HMENU_UserSize64(     unsigned long *, unsigned long            , HMENU * );
unsigned char *   HMENU_UserMarshal64(  unsigned long *, unsigned char *, HMENU * );
unsigned char *   HMENU_UserUnmarshal64(unsigned long *, unsigned char *, HMENU * );
void              HMENU_UserFree64(     unsigned long *, HMENU * );

unsigned long     HWND_UserSize64(     unsigned long *, unsigned long            , HWND * );
unsigned char *   HWND_UserMarshal64(  unsigned long *, unsigned char *, HWND * );
unsigned char *   HWND_UserUnmarshal64(unsigned long *, unsigned char *, HWND * );
void              HWND_UserFree64(     unsigned long *, HWND * );

unsigned long     STGMEDIUM_UserSize64(     unsigned long *, unsigned long            , STGMEDIUM * );
unsigned char *   STGMEDIUM_UserMarshal64(  unsigned long *, unsigned char *, STGMEDIUM * );
unsigned char *   STGMEDIUM_UserUnmarshal64(unsigned long *, unsigned char *, STGMEDIUM * );
void              STGMEDIUM_UserFree64(     unsigned long *, STGMEDIUM * );

/ * end of Additional Prototypes */
#endif // #if 0

//-------------------------------------------------------------------------

#endif /* __OLEIDL_H__ */
