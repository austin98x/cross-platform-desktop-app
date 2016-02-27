/* -------------------------------------------------------------------------
//	File name		：	stdptr.h
//	Author 			：	Austin
//	Create Time		：	2016-2-27 17:13:15
//	Description 	：	ks_stdptr ks_comptr
//
// -----------------------------------------------------------------------*/
#ifndef __STD_PTR_H__
#define __STD_PTR_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

_BFC_BEGIN

// -------------------------------------------------------------------------

enum enum_create_instance { create_instance };

// -------------------------------------------------------------------------
// --> ks_stdptr : smart point for COM object

template <class E>
class ks_stdptr
{
protected:
	E* _ptr;

public:
	ks_stdptr() { _ptr = NULL; }
	ks_stdptr(int __nil) { assert(__nil == 0); _ptr = NULL; }
	ks_stdptr(long __nil) { assert(__nil == 0); _ptr = NULL; }
	ks_stdptr(enum_create_instance f) { _ptr = new E; }
#ifdef X_OS_WINDOWS
	ks_stdptr(REFCLSID clsid) : _ptr(NULL)
	{
		CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, __uuid(E), (void**)&_ptr);
	}
#endif
	ks_stdptr(E* p)
	{
		_ptr = p;
		if (_ptr)
			_ptr->AddRef();
	}
	ks_stdptr(const ks_stdptr<E>& p)
	{
		_ptr = p._ptr;
		if (_ptr)
			_ptr->AddRef();
	}
	ks_stdptr(IUnknown* pUnk) : _ptr(NULL)
	{
		if (pUnk)
			pUnk->QueryInterface(__uuid(E), (void**)&_ptr);
	}
#if !defined(X_OS_WINDOWS)
	ks_stdptr(IUnknown* pUnk, REFIID iid) : _ptr(NULL)
	{
		if (pUnk)
			pUnk->QueryInterface(iid, (void**)&_ptr);
	}
	template <class Type>
	ks_stdptr(const ks_stdptr<Type>& p) : _ptr(NULL)
	{
		if (p)
			p->QueryInterface(__uuid(E), (void**)&_ptr);
	}
#endif

	~ks_stdptr()
	{
		if (_ptr)
			_ptr->Release();
	}

	void attach(E* p)
	{
		if (_ptr)
			_ptr->Release();
		_ptr = p;
	}
	E* detach()
	{
		E* tmp = _ptr;
		_ptr = NULL;
		return tmp;
	}
	void clear()
	{
		if (_ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
	}

	E* operator=(E* p)
	{
		if (p)
			p->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p;
	}
	E* operator=(const ks_stdptr<E>& p)
	{
		if (p._ptr)
			p._ptr->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p._ptr;
	}
	E* operator=(int __nil)
	{
		assert(__nil == 0);
		if (_ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
		return NULL;
	}
	E* operator=(long __nil)
	{
		assert(__nil == 0);
		if (_ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
		return NULL;
	}
	E* operator=(IUnknown* pUnk)
	{
		if (pUnk)
			pUnk->QueryInterface(__uuid(E), (void**)&pUnk);
		if (_ptr)
			_ptr->Release();
		return _ptr = (E*)pUnk;
	}
#if !defined(X_OS_WINDOWS)
	template <class Type>
	E* operator=(const ks_stdptr<Type>& p)
	{
		E* pTemp = NULL;
		if (p)
			p->QueryInterface(__uuid(E), (void**)&pTemp);
		if (_ptr)
			_ptr->Release();
		return _ptr = pTemp;
	}
#endif

	bool IsEqualObject(IUnknown* pOther) const
	{
		if (pOther)
		{
			if (_ptr == NULL)
				return false;
			IUnknown* pThis;
			_ptr->QueryInterface(IID_IUnknown, (void**)&pThis);
			pOther->QueryInterface(IID_IUnknown, (void**)&pOther);
			pThis->Release();
			pOther->Release();
			return (pThis == pOther);
		}
		return (_ptr == NULL);
	}

	E& operator*() const
		{ return *_ptr; }
	operator E*() const
		{ return _ptr; }
	E* get() const
		{ return _ptr; }
	E** operator&() // The assert on operator& usually indicates a bug.
		{ assert(_ptr == NULL); return &_ptr; }
	E* operator->() const
		{ return _ptr; }
	bool operator!() const
		{ return _ptr == NULL; }
	bool operator==(E* p) const
		{ return _ptr == p; }
	bool operator!=(E* p) const
		{ return _ptr != p; }
};

// -------------------------------------------------------------------------
// --> ks_stdptr : specialization for IUnknown

template <>
class ks_stdptr<IUnknown>
{
public:
	typedef IUnknown E;

protected:
	E* _ptr;

public:
	ks_stdptr() { _ptr = NULL; }
	ks_stdptr(int __nil) { assert(__nil == 0); _ptr = NULL; }
	ks_stdptr(long __nil) { assert(__nil == 0); _ptr = NULL; }
#ifdef X_OS_WINDOWS
	ks_stdptr(REFCLSID clsid) : _ptr(NULL)
	{
		CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&_ptr);
	}
#endif
	ks_stdptr(E* p)
	{
		_ptr = p;
		if (_ptr)
			_ptr->AddRef();
	}
	ks_stdptr(const ks_stdptr<E>& p)
	{
		_ptr = p._ptr;
		if (_ptr)
			_ptr->AddRef();
	}

#if !defined(X_OS_WINDOWS)
	template <class Type>
	ks_stdptr(const ks_stdptr<Type>& p)
	{
		_ptr = p;
		if (_ptr)
			_ptr->AddRef();
	}
#endif

	~ks_stdptr()
	{
		if (_ptr)
			_ptr->Release();
	}

	void attach(E* p)
	{
		if (_ptr)
			_ptr->Release();
		_ptr = p;
	}
	E* detach()
	{
		E* tmp = _ptr;
		_ptr = NULL;
		return tmp;
	}
	void clear()
	{
		if (_ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
	}

	E* operator=(E* p)
	{
		if (p)
			p->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p;
	}
	E* operator=(const ks_stdptr<E>& p)
	{
		if (p._ptr)
			p._ptr->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p._ptr;
	}
	E* operator=(int __nil)
	{
		assert(__nil == 0);
		if (_ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
		return NULL;
	}
	E* operator=(long __nil)
	{
		assert(__nil == 0);
		if (_ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
		return NULL;
	}
#if !defined(X_OS_WINDOWS)
	template <class Type>
	E* operator=(const ks_stdptr<Type>& sp)
	{
		Type* p = sp;
		if (p)
			p->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p;
	}
#endif

	bool IsEqualObject(IUnknown* pOther)
	{
		if (pOther)
		{
			if (_ptr == NULL)
				return false;
			IUnknown* pThis;
			_ptr->QueryInterface(IID_IUnknown, (void**)&pThis);
			pOther->QueryInterface(IID_IUnknown, (void**)&pOther);
			pThis->Release();
			pOther->Release();
			return (pThis == pOther);
		}
		return (_ptr == NULL);
	}

	E& operator*() const
		{ return *_ptr; }
	operator E*() const
		{ return _ptr; }
	E** operator&() // The assert on operator& usually indicates a bug.
		{ assert(_ptr == NULL); return &_ptr; }
	E* operator->() const
		{ return _ptr; }
	bool operator!() const
		{ return _ptr == NULL; }
	bool operator==(E* p) const
		{ return _ptr == p; }
	bool operator!=(E* p) const
		{ return _ptr != p; }
	bool operator==(int x) const
		{ assert(x == 0); return _ptr == NULL; }
	bool operator!=(int x) const
		{ assert(x == 0); return _ptr != NULL; }
	bool operator==(long x) const
		{ assert(x == 0); return _ptr == NULL; }
	bool operator!=(long x) const
		{ assert(x == 0); return _ptr != NULL; }
};

// -------------------------------------------------------------------------
// --> ks_comptr : ks_stdptr with given GUID

template <class E, const IID* piid>
class ks_comptr : public ks_stdptr<E>
{
public:
	typedef ks_stdptr<E> _base;

private:
	using _base::_ptr;

public:
	ks_comptr() {}
	ks_comptr(E* p) : _base(p) {}
	ks_comptr(const _base& p) : _base(p._ptr) {}
	ks_comptr(IUnknown* pUnk)
	{
		if (pUnk)
			pUnk->QueryInterface(*piid, (void**)&_ptr);
	}
	ks_comptr(REFCLSID clsid)
	{
		//CreateInstance(clsid, *piid, (void**)&_ptr);
	}

	E* operator=(E* p)
	{
		if (p)
			p->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p;
	}
	E* operator=(const ks_stdptr<E>& p)
	{
		if (p._ptr)
			p._ptr->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p._ptr;
	}
	E* operator=(const ks_comptr<E, piid>& p)
	{
		if (p._ptr)
			p._ptr->AddRef();
		if (_ptr)
			_ptr->Release();
		return _ptr = p._ptr;
	}
	E* operator=(int __nil)
	{
		assert(__nil == 0);
		if (_ptr)
		{
			_ptr->Release();
			_ptr = NULL;
		}
		return NULL;
	}
	E* operator=(IUnknown* pUnk)
	{
		if (pUnk)
			pUnk->QueryInterface(*piid, (void**)&pUnk);
		if (_ptr)
			_ptr->Release();
		return _ptr = (E*)pUnk;
	}

	bool IsEqualObject(IUnknown* pOther)
	{
		if (pOther)
		{
			if (_ptr == NULL)
				return false;
			IUnknown* pThis;
			_ptr->QueryInterface(IID_IUnknown, (void**)&pThis);
			pOther->QueryInterface(IID_IUnknown, (void**)&pOther);
			pThis->Release();
			pOther->Release();
			return (pThis == pOther);
		}
		return (_ptr == NULL);
	}
};

// -------------------------------------------------------------------------
// --> ks_comptr : specialization for IUnknown

template<>
class ks_comptr<IUnknown, &IID_IUnknown> : public ks_stdptr<IUnknown>
{
public:
	typedef ks_stdptr<IUnknown> _base;

public:
	ks_comptr() {}
	ks_comptr(const _base& p) : _base(p) {}
	ks_comptr(IUnknown* pUnk) : _base(pUnk) {}
	ks_comptr(REFCLSID clsid)
	{
		//CreateInstance(clsid, IID_IUnknown, (void**)&_ptr);
	}

	bool IsEqualObject(IUnknown* pOther)
	{
		if (pOther)
		{
			if (_ptr == NULL)
				return false;
			IUnknown* pThis;
			_ptr->QueryInterface(IID_IUnknown, (void**)&pThis);
			pOther->QueryInterface(IID_IUnknown, (void**)&pOther);
			pThis->Release();
			pOther->Release();
			return (pThis == pOther);
		}
		return (_ptr == NULL);
	}
};

// --------------------------------------------------------------------------

_BFC_END

#endif /* __STD_PTR_H__ */
