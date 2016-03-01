/* -------------------------------------------------------------------------
//	File name		：	comdef.h
//	Author 			：	Austin
//	Create Time		：	2016-3-1 10:36:10
//	Description 	：	COM define
//
// -----------------------------------------------------------------------*/
#ifndef __COMDEF_H__
#define __COMDEF_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------

#ifndef X_OS_WINDOWS
inline BOOL operator==(REFGUID rguid1, REFGUID rguid2)
{
	return ((INT32*) &rguid1)[0] == ((INT32*) &rguid2)[0]
		&& ((INT32*) &rguid1)[1] == ((INT32*) &rguid2)[1]
		&& ((INT32*) &rguid1)[2] == ((INT32*) &rguid2)[2]
		&& ((INT32*) &rguid1)[3] == ((INT32*) &rguid2)[3];
}

inline BOOL operator!=(const GUID& guidOne, const GUID& guidOther)
{
    return !(guidOne == guidOther);
}
#endif

inline BOOL _XInlineIsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
	return ((INT32*) &rguid1)[0] == ((INT32*) &rguid2)[0]
		&& ((INT32*) &rguid1)[1] == ((INT32*) &rguid2)[1]
		&& ((INT32*) &rguid1)[2] == ((INT32*) &rguid2)[2]
		&& ((INT32*) &rguid1)[3] == ((INT32*) &rguid2)[3];
}

inline BOOL _XInlineIsEqualUnknown(REFGUID rguid1)
{
	return ((INT32*) &rguid1)[0] == 0
		&& ((INT32*) &rguid1)[1] == 0
#ifdef __BYTESWAP__
		&& ((INT32*) &rguid1)[2] == 0xC0000000
		&& ((INT32*) &rguid1)[3] == 0x00000046;
#else
		&& ((INT32*) &rguid1)[2] == 0x000000C0
		&& ((INT32*) &rguid1)[3] == 0x46000000;
#endif
}

#define InlineIsEqualGUID(rguid1, rguid2)	_XInlineIsEqualGUID(rguid1, rguid2)
#define InlineIsEqualUnknown(rguid1)		_XInlineIsEqualUnknown(rguid1)

#ifndef ISEQUAL_GUID
#define ISEQUAL_GUID(g1, g2)				InlineIsEqualGUID(g1, g2)
#define ISEQUAL_IID(g1, g2)					InlineIsEqualGUID(g1, g2)
#define ISEQUAL_CLSID(g1, g2)				InlineIsEqualGUID(g1, g2)
#endif

#ifndef IsEqualGUID
#define IsEqualGUID(g1, g2)					InlineIsEqualGUID(g1, g2)
#define IsEqualIID(g1, g2)					InlineIsEqualGUID(g1, g2)
#define IsEqualCLSID(g1, g2)				InlineIsEqualGUID(g1, g2)
#endif

#define _ksCompareGUID(g1, g2)				memcmp(&(g1), &(g2), sizeof(GUID))

#ifndef COMPARE_GUID
#define COMPARE_GUID(g1, g2)				_ksCompareGUID(g1, g2)
#define COMPARE_IID(g1, g2)					_ksCompareGUID(g1, g2)
#define COMPARE_CLSID(g1, g2)				_ksCompareGUID(g1, g2)
#endif

inline
STDMETHODIMP_(bool) operator<(REFGUID rguid1, REFGUID rguid2) 
{
	return COMPARE_GUID(rguid1, rguid2) < 0;
}

// -------------------------------------------------------------------------

#ifndef _KS_SAFECAST
#define _KS_SAFECAST(Interface)			(void**)static_cast<Interface**>
#endif

#ifndef CREATE_INSTANCE_
#define CREATE_INSTANCE_(ComClass, Interface, ppv)							\
	CreateInstance(__clsid(ComClass), __iid(Interface), _KS_SAFECAST(Interface)(ppv))
#endif

#ifndef CREATE_INSTANCE_AGG_
#define CREATE_INSTANCE_AGG_(ComClass, ppv, pOuter)							\
	CreateInstance(__clsid(ComClass), _KS_SAFECAST(IUnknown)(ppv), pOuter)
#endif

#ifndef QUERYINTERFACE
#define QUERYINTERFACE(Interface, ppv)										\
	QueryInterface(__iid(Interface), _KS_SAFECAST(Interface)(ppv))
#endif

#ifndef QI
#define QI(Interface, ppv)													\
	QueryInterface(__iid(Interface), _KS_SAFECAST(Interface)(ppv))
#endif

#ifndef KS_ASSIGN
#define KS_ASSIGN(Dest, Src)												\
{																			\
	if ((Src) != NULL)														\
		(Src)->AddRef();													\
	if ((Dest) != NULL)														\
		(Dest)->Release();													\
	(Dest) = (Src);															\
}
#endif

#ifndef RELEASE
#define RELEASE(pUnk)														\
	if ((pUnk) != NULL)														\
	{																		\
		(pUnk)->Release();													\
		(pUnk) = NULL;														\
	}
#endif

#ifndef KS_RELEASE
#define KS_RELEASE(pUnk)		RELEASE(pUnk)
#endif

#ifndef KS_CLOSE
#define KS_CLOSE(pUnk)														\
	if ((pUnk) != NULL)														\
	{																		\
		(pUnk)->Close();													\
		(pUnk)->Release();													\
		(pUnk) = NULL;														\
	}
#endif

#ifndef KS_TERM
#define KS_TERM(pUnk)														\
	if ((pUnk) != NULL)														\
	{																		\
		(pUnk)->Term();														\
		(pUnk)->Release();													\
		(pUnk) = NULL;														\
	}
#endif

#ifndef IS_KINDOF
#define IS_KINDOF(pUnk, Interface)		IsKindOf(pUnk, __iid(Interface))
#endif

// -------------------------------------------------------------------------

#define BEGIN_GETINTERFACE(ComClass)										\
STDMETHODIMP ComClass::GetInterface(REFIID riid, void** ppvObject)			\
{																			\
	if (0);

#define ADD_INTERFACE2(Interface, pIntf)									\
	else if (ISEQUAL_IID(riid, __iid(Interface)))							\
		*ppvObject = static_cast<Interface*>(pIntf);

#define END_GETINTERFACE()													\
	else																	\
	{																		\
		TRACE_GUIDX(__X("GetInterface - IID not found"), riid);				\
		*ppvObject = NULL;													\
		return E_NOINTERFACE;												\
	}																		\
	if (*ppvObject == NULL)													\
	{																		\
		TRACE_GUIDX(__X("GetInterface - null object found"), riid);			\
		return E_NOINTERFACE;												\
	}																		\
	((IUnknown*)(*ppvObject))->AddRef();									\
	return S_OK;															\
}

// -------------------------------------------------------------------------

inline 
bool __stdcall IsKindOf(IUnknown* pUnk, REFIID iid)
{
	IUnknown* pQuery;
	if (pUnk && pUnk->QueryInterface(iid, (void**)&pQuery) == S_OK)
	{
		pQuery->Release();
		return (pUnk == pQuery);
	}
	return false;
}

template <class container>
void __stdcall RefClear(container& r)
{
	typedef typename container::iterator iterator;
	for (iterator it = r.begin(); it != r.end(); ++it)
	{
		if (*it)
			(*it)->Release();
	}
	r.clear();
}

inline
ULONG __stdcall RefCount(IUnknown* pUnk)
{
	pUnk->AddRef();
	return pUnk->Release();
}

// -------------------------------------------------------------------------

#endif /* __COMDEF_H__ */
