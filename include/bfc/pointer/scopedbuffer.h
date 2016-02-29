/* -------------------------------------------------------------------------
//	File name		：	scopedbuffer.h
//	Author 			：	Austin
//	Create Time		：	2016-2-29 10:38:25
//	Description 	：	ks_scopedbuffer
//
// -----------------------------------------------------------------------*/
#ifndef __SCOPEDBUFFER_H__
#define __SCOPEDBUFFER_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

_BFC_BEGIN

// -------------------------------------------------------------------------
// --> ks_scopedbuffer

template <typename T>
class ks_scopedbuffer
{
public:
	ks_scopedbuffer(size_t size)
		: m_pData(NULL)
		, m_size(size)
	{
		m_valid = size > 0;
		if (m_valid)
		{
			m_pData = new T[size];
			memset((void*)m_pData, 0, size * sizeof(T));
		}
	}

	~ks_scopedbuffer()
	{
		if (m_valid)
			delete[] m_pData;
	}

	T* data()
	{
		return m_pData;
	}

	size_t size() const
	{
		return m_size;
	}

private:
	ks_scopedbuffer(const ks_scopedbuffer& counter)
	{
	}

	ks_scopedbuffer& operator = (const ks_scopedbuffer& counter)
	{
		return *this;
	}

private:
	bool	m_valid;
	T*		m_pData;
	size_t	m_size;
};

// --------------------------------------------------------------------------

_BFC_END

#endif // __SCOPEDBUFFER_H__
