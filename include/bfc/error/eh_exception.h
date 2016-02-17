// -------------------------------------------------------------------------- //
//	File name		：	eh_exception.h
//	Author 			：	Austin
//	Create Time		：	2016-2-17 17:16:05
//	Description 	：	Exception 
//
// -------------------------------------------------------------------------- //

#ifndef __EH_EXCEPTION_H__
#define __EH_EXCEPTION_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------- //
// --> ks_exception

class ks_exception
{
	HRESULT hr;
public:
	ks_exception(HRESULT _hr) throw(): hr(_hr) {}

	ks_exception(const ks_exception& r) throw(): hr(r.hr) {}

	ks_exception& operator= (const ks_exception& r) throw()
	{
		if (this != &r)
		{
			hr = r.hr;
		}
		return *this;
	}
	HRESULT get_result() const throw() { return hr; }	
};

// -------------------------------------------------------------------------- //

#define ks_throw(hr)			throw ks_exception(hr)

// -------------------------------------------------------------------------- //

inline void throw_when_false(bool bv, HRESULT hr)
{
	if (!bv)
		throw ks_exception(hr);
}

inline void throw_when_failed(HRESULT hr)
{
	if (FAILED(hr))
		throw ks_exception(hr);
}

#define THROW_WHEN_FALSE	throw_when_false
#define THROW_WHEN_FAILED	throw_when_failed

#define THROW_WHEN_NULL_POINTER(p1)							\
	THROW_WHEN_FALSE((p1) != NULL, E_INVALIDARG)
#define THROW_WHEN_NULL_POINTER2(p1, p2)					\
	THROW_WHEN_FALSE((p1) != NULL && (p2) != NULL, E_INVALIDARG)
#define THROW_WHEN_NULL_POINTER3(p1, p2, p3)				\
	THROW_WHEN_FALSE((p1) != NULL && (p2) != NULL && (p3) != NULL, E_INVALIDARG)
#define THROW_WHEN_NULL_POINTER4(p1, p2, p3, p4)			\
	THROW_WHEN_FALSE((p1) != NULL && (p2) != NULL && (p3) != NULL && (p4) != NULL, E_INVALIDARG)
#define THROW_WHEN_NULL_POINTER5(p1, p2, p3, p4, p5)		\
	THROW_WHEN_FALSE((p1) != NULL && (p2) != NULL && (p3) != NULL && (p4) != NULL && (p5) != NULL, E_INVALIDARG)
#define THROW_WHEN_NULL_POINTER6(p1, p2, p3, p4, p5, p6)	\
	THROW_WHEN_FALSE((p1) != NULL && (p2) != NULL && (p3) != NULL && (p4) != NULL && (p5) != NULL && (p6) != NULL, E_INVALIDARG)

// -------------------------------------------------------------------------- //

#define KS_TRY				try
#define KS_CATCH_STD(e)		catch(ks_exception e)
#define KS_CATCH			catch
#define KS_CATCH_ELSE		catch(...)
#define KS_RETHROW			throw

// -------------------------------------------------------------------------- //

#define KS_BEGIN_WRAP		KS_TRY

#ifdef X_OS_WINDOWS
#define KS_END_WRAP_(hr)							\
	KS_CATCH_STD(ex) {								\
		return ex.get_result();						\
	}												\
	KS_CATCH_ELSE {									\
		assert(false); 								\
		return HRESULT_FROM_WIN32(GetLastError());	\
	}												\
	return hr;
#else
#define KS_END_WRAP_(hr)							\
	KS_CATCH_STD(ex) {								\
		return ex.get_result();						\
	}												\
	KS_CATCH_ELSE {									\
		assert(false); 								\
		return E_FAIL;								\
	}												\
	return hr;
#endif

#define KS_END_WRAP			KS_END_WRAP_(S_OK)

// -------------------------------------------------------------------------- //

#endif //__EH_EXCEPTION_H__
