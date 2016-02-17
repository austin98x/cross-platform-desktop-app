// -------------------------------------------------------------------------- //
//	File name		：	eh_check.h
//	Author 			：	Austin
//	Create Time		：	2016-2-17 16:53:45
//	Description 	：	Check error flow  
//
// -------------------------------------------------------------------------- //

#ifndef __EH_CHECK_H__
#define __EH_CHECK_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------- //

#define KS_EXIT					KS_EXIT_HERE

// -------------------------------------------------------------------------- //
// --> KS_CHECK

#define KS_CHECK_BOOLEX(result, expr)										\
	if (!(result))															\
	{																		\
		expr;																\
		TRACE(__X("KS_CHECK goto exit : %S(%S@%d)\n"), __FUNCTION__, __FILE__, __LINE__); \
		goto KS_EXIT;														\
	}

#define KS_CHECK_BOOL(result)												\
	if (!(result))															\
	{																		\
		TRACE(__X("KS_CHECK goto exit : %S(%S@%d)\n"), __FUNCTION__, __FILE__, __LINE__); \
		goto KS_EXIT;														\
	}

#define KS_CHECK(hr)				KS_CHECK_BOOL(SUCCEEDED(hr))


#define CHECK_BOOLEX(result, expr)											\
	if (!(result))															\
	{																		\
		expr;																\
		goto KS_EXIT;														\
	}

#define CHECK_BOOL(result)													\
	if (!(result))															\
	{																		\
		goto KS_EXIT;														\
	}

#define CHECK(hr)					CHECK_BOOL(SUCCEEDED(hr))

#define RETURN						return

#define KS_VALID_HR(hr)	{if(FAILED(hr))	return hr;}

// -------------------------------------------------------------------------- //

#endif // __EH_CHECK_H__
