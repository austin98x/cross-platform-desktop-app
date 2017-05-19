#ifndef __ZXAPP_APPLICATION_H__
#define __ZXAPP_APPLICATION_H__

#include "zshare/zapplication.h"

class ZxAppApplication : public ZApplication
{
	Q_OBJECT
public:
	ZxAppApplication(int &argc, char **argv);
	~ZxAppApplication();
};

#endif //__ZXAPP_APPLICATION_H__
