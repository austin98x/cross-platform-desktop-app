#include "stdafx.h"
#include "zxappapplication.h"

ZxAppApplication::ZxAppApplication(int &argc, char **argv) : ZApplication(argc, argv, "app")
{
	SetupFont();
	SetupTranslator();
	SetupXmlUserface("app.xml");
	QIcon icon("xxx.ico");
	SetupAppInfo("APP", "v1.0", icon);
}

ZxAppApplication::~ZxAppApplication()
{

}
