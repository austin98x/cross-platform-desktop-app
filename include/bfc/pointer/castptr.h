//	File name		：	castptr.h
//	Author 			：	Austin
//	Create Time		：	2016-2-27 17:12:10
//	Description 	：	ks_castptr

#ifndef __CAST_PTR_H__
#define __CAST_PTR_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

_BFC_BEGIN

// -------------------------------------------------------------------------
// --> ks_castptr : smart pointer for type conversion.

template< class _Ty >
class ks_castptr
{
private:
	_Ty* _ptr;

public:
	ks_castptr() { _ptr = NULL; }
	ks_castptr(int __nil) { assert(__nil == 0); _ptr = 0; }
	ks_castptr(long __nil) { assert(__nil == 0); _ptr = 0; }
	ks_castptr(_Ty* p) { _ptr = p; }
	ks_castptr(const ks_castptr<_Ty>& cp) { _ptr = (_Ty*)cp; }
	ks_castptr(const ks_stdptr<_Ty>& sp) { _ptr = (_Ty*)sp; }

	void clear()
	{
		_ptr = NULL;
	}

	template<class _Type>
	ks_castptr(_Type* p) 
	{
		_ptr = static_cast<_Ty*>(p);
		assert(_check(p));
	}
	template<class _Type>
	ks_castptr(const ks_castptr<_Type>& p) 
	{
		_ptr = static_cast<_Ty*>((_Type*)p);
		assert(_check((_Type*)p));
	}
	template<class _Type>
	ks_castptr(const ks_stdptr<_Type>& p)
	{
		_Type* sp = (_Type*)p;
		_ptr = static_cast<_Ty*>(sp);
		assert(_check(sp));
	}

	_Ty* operator=(int __nil)
	{
		assert(__nil == 0);
		_ptr = 0;
		return _ptr;
	}
	_Ty* operator=(const ks_castptr<_Ty>& cp)
	{
		_ptr = (_Ty*)cp;
		return _ptr;
	}
	_Ty* operator=(const ks_stdptr<_Ty>& sp)
	{
		_ptr = (_Ty*)sp;
		return _ptr;
	}
	template<class _Type>
	_Ty* operator=(_Type* p)
	{
		_ptr = static_cast<_Ty*>(p);
		assert(_check(p));
		return _ptr;
	}
	template<class _Type>
	_Ty* operator=(const ks_castptr<_Type>& sp)
	{
		_ptr = static_cast<_Ty*>((_Type*)sp);
		assert(_check((_Type*)sp));
		return _ptr;
	}
	template<class _Type>
	_Ty* operator=(const ks_stdptr<_Type>& sp)
	{
		_Type* p = (_Type*)sp;
		_ptr = static_cast<_Ty*>(p);
		assert(_check(p));
		return _ptr;
	}

	BOOL operator==(_Ty* p) const {	return _ptr == p;	}
	BOOL operator!=(_Ty* p) const {	return _ptr != p;	}
	BOOL operator!() const { return _ptr == NULL; }
	_Ty& operator*() const { return *_ptr; }
	_Ty* get() const { return _ptr; }
	operator _Ty*() const { return _ptr; }
	_Ty** operator&() { return &_ptr; }
	_Ty* operator->() const { return _ptr; }

private:
	template<class _Type>
	bool _check(_Type* p)
	{
		// type check for DEBUG
#ifdef _DEBUG
		if (!p)
			return true;
		_Ty* pd = dynamic_cast<_Ty*>(p);
		return (pd && pd == _ptr);
#endif 
		return true;
	}
};

// -------------------------------------------------------------------------

_BFC_END

#endif // __CAST_PTR_H__
