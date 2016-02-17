#ifndef __TEST_H__
#define __TEST_H__

#ifdef X_OS_WINDOWS
#include "TestWindows.h"
#elif defined(X_OS_LINUX)
#include "TestLinux.h"
#endif

#endif /* __TEST_H__ */
