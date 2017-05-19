#ifndef __ZAPPLICATION_H__
#define __ZAPPLICATION_H__

#include "zglobal.h"

#define ZApplicationBase QApplication

class Z_EXPORT ZApplication : public ZApplicationBase
{
	Q_OBJECT
public:
	ZApplication (int & argc, char ** argv, const QString &appName);
	~ZApplication();
};

#define zApp ((ZApplication *)qApp)

#endif //__ZAPPLICATION_H__
