#include "stdafx.h"
#include "zxappapplication.h"
#include "zxappmainwindow.h"

void initEnv()
{
}

extern "C" int main(int argc, char *argv[])
{
	int retCode = 0;
	initEnv();
	ZxAppApplication app(argc, argv);
	ZxAppMainWindow mainWin;
	mainWin.show();
	retCode = app.exec();

	return retCode;
}