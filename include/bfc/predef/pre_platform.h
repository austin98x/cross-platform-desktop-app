// -------------------------------------------------------------------------- //
//	File name		：	pre_platform.h
//	Author 			：	Austin
//	Create Time		：	2016-2-16 13:35:25
//	Description 	：	Detect(OS、Compiler、CPU、STL...)
//
// -------------------------------------------------------------------------- //

#ifndef __BFC_PLATFORM_H__
#define __BFC_PLATFORM_H__

#ifndef __BFC_INCLUDE__
#	error This file is not intended to be included separately
#endif

// -------------------------------------------------------------------------- //
// --> Platform(OS) Detection

#if defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__)
#	define X_OS_WINDOWS
#elif defined(__linux__) || defined(__LINUX__) || defined(LINUX) || defined(_LINUX)
#	define X_OS_LINUX
#	define X_OS_UNIX
#elif defined(_AIX)
#	define X_OS_AIX
#	define X_OS_UNIX
#elif defined(_SEQUENT_)
#	define X_OS_PTX
#	define X_OS_UNIX
#elif defined(_HP_UX) || defined(__hpux) || defined(_HPUX_SOURCE)
#	define X_OS_HPUX
#	define X_OS_UNIX
#elif defined(SOLARIS) || defined(__SVR4)
#	define X_OS_SOLARIS
#	define X_OS_UNIX
#elif defined(_SCO_DS)
#	define X_OS_OPENSERVER
#	define X_OS_UNIX
#elif defined(__UNIXWARE__) || defined(__USLC__)
#	define X_OS_UNIXWARE
#	define X_OS_UNIX
#elif defined(__FreeBSD__)
#	define X_OS_FREEBSD
#	define X_OS_UNIX
#elif defined(IRIX) || defined(__sgi)
#	define X_OS_IRIX
#	define X_OS_UNIX
#elif defined(__MVS__) || defined(EXM_OS390)
#	define X_OS_OS390
#	define X_OS_UNIX
#elif defined(__OS400__)
#	define X_OS_AS400
#	define X_OS_UNIX
#elif defined(__TANDEM)
#	define X_OS_TANDEM
#	define X_OS_UNIX
#elif defined(__APPLE__) && defined(__MACH__)
#	define X_OS_MACOS
#	define X_OS_UNIX
#	include <TargetConditionals.h>
#	if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#		define X_OS_IOS
#	elif defined(TARGET_OS_MAC) && TARGET_OS_MAC
#		define X_OS_MACOSX
#	endif
#elif defined(__MSDX_OS__)
#	define X_OS_DOS
#elif defined(__alpha) && defined(__osf__)
#	define X_OS_TRU64
#elif defined(__OS2__)
#	define X_OS_OS2
#else
#	error "Unknown OS Planform!!!"
#endif

// -------------------------------------------------------------------------- //
// --> Platform(Compiler) Detection

#if defined(__BORLANDC__)
#	define X_CC_BC
#	define X_CC_BCB
#	if defined(SYSMAC_H)
#		define X_BCB_USECLX
#	endif
#elif defined(_MSC_VER)
#	define X_CC_VC
#elif defined(__GNUG__) || defined(__GNUC__)
#	define X_CC_GCC
#	if defined(__clang__)
#		define X_CC_CLANG
#	endif
#elif defined(__xlC__)
#	define X_CC_CSET
#elif defined(X_OS_SOLARIS)
#	if defined(__SUNPRO_CC) && (__SUNPRO_CC >=0x500)
#		define X_CC_SUNCC5
#	elif defined(__SUNPRO_CC) && (__SUNPRO_CC <0x500)
#		define X_CC_SUNCC
#	elif defined(_EDG_RUNTIME_USES_NAMESPACES)
#		define X_CC_SOLARIS_KAICC
#	elif defined(__GNUG__)
#		define X_CC_GCC
#	else
#		error "Unknown C/C++ Compiler!!!"
#	endif
#elif defined(X_OS_HPUX)
#	if defined(EXM_HPUX)
#		define X_CC_HPUX_KAICC
#	elif (__cplusplus == 1)
#		define X_CC_HPUX_CC
#	elif (__cplusplus == 199707 || __cplusplus == 199711)
#		define X_CC_HPUX_aCC
#	endif
#elif defined(X_OS_IRIX)
#	define X_CC_MIPSPRO_CC
#elif defined(X_OS_PTX)
#	define X_CC_PTX_CC
#elif defined(X_OS_TANDEM)
#	define X_CC_TANDEMCC
#elif defined(X_OS_OS390) && defined(__cplusplus)
#	define X_CC_MVSCPP
#elif defined(__IBMC__) || defined(__IBMCPP__)
#	if defined(X_OS_WIN32)
#		define X_CC_IBMVAW32
#	elif defined(X_CC_OS2)
#		define X_CC_IBMVAOS2
#		if (__IBMC__ >= 400 || __IBMCPP__ >= 400)
#			define X_CC_IBMVA4_OS2
#		endif
#	endif
#elif defined(X_OS_TRU64) && defined(__DECCXX)
#	define X_CC_DECCXX
#elif defined(__MWERKS__)
#	define X_CC_METROWERKS
#elif defined(__clang__)
#	define X_CC_GCC
#	define X_CC_CLANG
#else
#	error "Unknown C/C++ Compiler!!!"
#endif

#if defined(__MT__) && !defined(_MT)
#   define _MT
#endif

// -------------------------------------------------------------------------- //
// --> Platform(CPU) Detection

#if defined(_M_IX86) || defined(__i386__)
#	define X_CPU_X86
#elif defined(_M_X64) || defined(__amd64__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IA64) || defined(_M_AMD64)
#	define X_CPU_X86_64
#elif defined(__SPARC__) || defined(SPARC) || defined(_SPARC)
#	define X_CPU_SPARC
#elif defined(__mips__) || defined(mips) || defined (_mips) || (__mips)
#	define X_CPU_MIPS
#elif defined(__arm__)
#	define X_CPU_ARM
#elif defined(__arm64__) || defined (__aarch64__)
#	define X_CPU_ARM_64
#elif defined(__sw_64__)
#	define X_CPU_SW_64
#else
#	error "Unknown CPU Arch!!!"
#endif

// -------------------------------------------------------------------------- //

#endif// __BFC_PLATFORM_H__
