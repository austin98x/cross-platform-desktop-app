// -------------------------------------------------------------------------- //
//	File name		：	thread.h
//	Author 			：	Austin
//	Create Time		：	2017-3-30 16:54:21
//	Description 	：	thread
//
// -------------------------------------------------------------------------- //

#ifndef __THREAD_H__
#define __THREAD_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif


// -------------------------------------------------------------------------- //
#ifdef X_CC_GCC
inline LONG InterlockedIncrement(LONG *p)
{
	return __sync_add_and_fetch(p, 1);
}

inline LONG InterlockedDecrement(LONG *p)
{
	return __sync_sub_and_fetch(p, 1);
}

inline LONG InterlockedIncrement(INT32 *p)
{
	return __sync_add_and_fetch(p, 1);
}

inline LONG InterlockedDecrement(INT32 *p)
{
	return __sync_sub_and_fetch(p, 1);
}
#endif

// -------------------------------------------------------------------------- //

#endif// __THREAD_H__
