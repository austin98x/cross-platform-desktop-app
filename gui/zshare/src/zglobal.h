#ifndef __ZGLOBAL_H__
#define __ZGLOBAL_H__

#include <QtCore/qglobal.h>

#ifndef Z_EXPORT
# if defined ZSHARE_LIB
#  define Z_EXPORT Q_DECL_EXPORT
# else
#  define Z_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif //__ZGLOBAL_H__
