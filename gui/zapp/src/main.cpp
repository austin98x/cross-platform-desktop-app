#include "stdafx.h"
#include "zxappapplication.h"

void initEnv()
{
}

extern "C" int main(int argc, char *argv[])
{
	int retCode = 0;
	initEnv();
	ZxAppApplication app(argc, argv);
	retCode = app.exec();

	return retCode;
}