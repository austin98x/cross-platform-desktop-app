#include "stdafx.h"
#include "zapplication.h"

ZApplication::ZApplication(int & argc, char ** argv, const QString &appName)
	: ZApplicationBase(argc, argv)
{

}
	
ZApplication::~ZApplication()
{

}

void ZApplication::SetupFont()
{
	QFont font = this->font();
	this->setFont(font);
}

void ZApplication::SetupTranslator()
{
	QTranslator qtTranslator;
	qtTranslator.load("xxx_zh");
	this->installTranslator(&qtTranslator);
}

void ZApplication::SetupXmlUserface(const QString& xmlFile)
{

}

void ZApplication::SetupAppInfo(const QString& name, const QString& version, const QIcon& icon)
{
	this->setApplicationName(name);
	this->setApplicationVersion(version);
	this->setWindowIcon(icon);
}
