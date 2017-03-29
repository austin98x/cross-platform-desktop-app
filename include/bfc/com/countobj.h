/* -------------------------------------------------------------------------
//	File name		：	countobj.h
//	Author 			：	Austin
//	Create Time		：	2016-3-1 10:46:15
//	Description 	：	KCountObject
//
// -----------------------------------------------------------------------*/
#ifndef __COUNTOBJ_H__
#define __COUNTOBJ_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

#include "../pointer/stdptr.h"

_BFC_BEGIN

// -------------------------------------------------------------------------
// --> KCountObject

#ifndef KS_VALID_REFCOUNT
#define KS_VALID_REFCOUNT(nRef)	assert((unsigned)(nRef) < 2000000000)
#endif

#ifndef KS_INVALID_REFCOUNT
#define KS_INVALID_REFCOUNT		2147483647
#endif

#ifndef CONEW_
#define CONEW_(ComClass)	new _BFC KCountObject<ComClass>
#endif

template <class E>
class KCountObject : public E
{
public:
	KCountObject()
	{
		m_nRef = 1;
	}
	ULONG __stdcall AddRef()
	{
		KS_VALID_REFCOUNT(m_nRef);
		return ++m_nRef;
	}
	ULONG __stdcall Release()
	{
		KS_VALID_REFCOUNT(m_nRef);
		ULONG l = --m_nRef;
		if (l == 0)
		{
			m_nRef = KS_INVALID_REFCOUNT;
			delete this;
		}
		return l;
	}
	
protected:
	long m_nRef;
};

// -------------------------------------------------------------------------
// --> KCountObjectPtr

template <class ComClass>
class KCountObjectPtr : public ks_stdptr< KCountObject<ComClass> >
{
public:
	typedef ks_stdptr< KCountObject<ComClass> > _Base;
	typedef KCountObjectPtr<ComClass> _Myt;

public:
	using _Base::operator=;

private:
	using _Base::_ptr;

public:
	KCountObjectPtr(enum_create_instance)
	{
		_ptr = new KCountObject<ComClass>;
	}
};

// -------------------------------------------------------------------------

_BFC_END

#endif /* __COUNTOBJ_H__ */
