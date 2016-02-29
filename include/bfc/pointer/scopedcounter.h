/* -------------------------------------------------------------------------
//	File name		：	scopedcounter.h
//	Author 			：	Austin
//	Create Time		：	2016-2-29 10:36:14
//	Description 	：	ks_scopedcounter
//
// -----------------------------------------------------------------------*/
#ifndef __SCOPEDCOUNTER_H__
#define __SCOPEDCOUNTER_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

_BFC_BEGIN

// -------------------------------------------------------------------------
// --> ks_scopedcounter

template <typename T>
class ks_scopedcounter
{
public:
	ks_scopedcounter(T* pData)
		: m_pData(pData)
	{
		ASSERT(m_pData);
		++(*m_pData);
	}

	~ks_scopedcounter()
	{
		--(*m_pData);
	}

private:
	ks_scopedcounter(const ks_scopedcounter& counter)
	{
	}

	ks_scopedcounter& operator = (const ks_scopedcounter& counter)
	{
		return *this;
	}

private:
	T *m_pData;
};

// --------------------------------------------------------------------------

_BFC_END

#endif // __SCOPEDCOUNTER_H__
