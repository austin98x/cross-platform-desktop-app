/* -------------------------------------------------------------------------
//	File name		：	bstr.h
//	Author 			：	Austin
//	Create Time		：	2016-2-25 14:20:15
//	Description 	：	ks_bstr
//
// -----------------------------------------------------------------------*/

#ifndef __KS_BSTR_H__
#define __KS_BSTR_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif


// -------------------------------------------------------------------------
// --> ks_bstr

_BFC_BEGIN

class ks_bstr
{
public:
	typedef BSTR type;
	typedef UINT size_type;

protected:
	BSTR _bstr;

private:
	ks_bstr(const ks_bstr&);
	void operator=(const ks_bstr&);

public:
	ks_bstr()
	{
		_bstr = NULL;
	}
	ks_bstr(LPCWSTR wcs)
	{
		_bstr = SysAllocString(wcs);
	}
	ks_bstr(LPCWSTR wcs, size_type cch)
	{
		_bstr = SysAllocStringLen(wcs, cch);
	}
	~ks_bstr()
	{
		SysFreeString(_bstr);
		_bstr = NULL;
	}

public:
	(operator BSTR)() const
	{
		return _bstr;
	}
	BSTR* operator&()
	{
		assert(_bstr == NULL);
		return &_bstr;
	}
	LPCWSTR c_str() const
	{
		return _bstr;
	}
	void assign(LPCWSTR wcs)
	{
		SysReAllocString(&_bstr, wcs);
	}
	void assign(LPCWSTR wcs, size_type cch)
	{
		SysReAllocStringLen(&_bstr, wcs, cch);
	}
	BOOL empty() const
	{
		return SysStringLen(_bstr) == 0;
	}
	size_type size() const
	{
		return SysStringLen(_bstr);
	}
	BSTR detach()
	{
		BSTR tmp = _bstr;
		_bstr = NULL;
		return tmp;
	}
	void attach(BSTR bstr)
	{
		SysFreeString(_bstr);
		_bstr = bstr;
	}
	void clear()
	{
		SysFreeString(_bstr);
		_bstr = NULL;
	}
	bool isEqual(BSTR bstr) const
	{
		enum { bytes_of_char = sizeof(WCHAR) };
		const unsigned int len = SysStringLen(bstr);
		return (len == SysStringLen(_bstr)) ? 
			(memcmp(_bstr, bstr, bytes_of_char*len) == 0) : FALSE;
	}
	bool isEqualString(LPCWSTR wcs) const
	{
		enum { bytes_of_char = sizeof(WCHAR) };
		const unsigned int len = xstrlen(wcs);
		return (len == SysStringLen(_bstr)) ?
			(memcmp(_bstr, wcs, bytes_of_char*len) == 0) : FALSE;
	}
};

_BFC_END

// -------------------------------------------------------------------------
#endif // __KS_BSTR_H__
