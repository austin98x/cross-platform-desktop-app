/* -------------------------------------------------------------------------- */
//	File name		：	scopedptr.h
//	Author 			：	Austin
//	Create Time		：	2016-2-29 10:33:20
//	Description 	：	ks_scopedptr
//
// -------------------------------------------------------------------------- */
#ifndef __SCOPEDPTR_H__
#define __SCOPEDPTR_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

_BFC_BEGIN

// -------------------------------------------------------------------------
// --> ks_scopedptr

template <class E>
class ks_scopedptr
{
public:
	ks_scopedptr()
		: _ptr(NULL)
	{
	}
	
	ks_scopedptr(E *p)
		: _ptr(p)
	{
	}
	
	~ks_scopedptr()	
	{
		delete _ptr;
	}
public:
	E * get() const
	{
		return _ptr;
	}
	
	E * operator -> () const
	{
		return _ptr;
	}	
	
	void attach(E * p)
	{
		delete _ptr;
		_ptr = p;	
	}
	
	E * detach()
	{
		E * p = _ptr;
		_ptr = NULL;
		return p;
	}
	
	void clear()
	{	
		delete _ptr;
		_ptr = NULL;
	}

	E** operator&() // The assert on operator& usually indicates a bug.
	{ assert(_ptr == NULL); return &_ptr; }

private:
	ks_scopedptr(const ks_scopedptr<E> &p);
	E* operator=(const ks_scopedptr<E> &p);
	
private:
	E *_ptr;
};

// --------------------------------------------------------------------------

_BFC_END

#endif /* __SCOPEDPTR_H__ */
