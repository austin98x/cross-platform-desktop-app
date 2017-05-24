#include "stdafx.h"
#include "zapplication.h"
#include "zuiconfig.h"
#include "zdom.h"
#include <QFile>

ZApplication::ZApplication(int & argc, char ** argv, const QString &appName)
	: ZApplicationBase(argc, argv)
{
	m_pUiconfig = new ZUiConfigure(this);
}
	
ZApplication::~ZApplication()
{
	delete m_pUiconfig;
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
	QFileInfo finfo(xmlFile);
	if (!finfo.exists())
	{
		qWarning() << "ZApplication: XML file not exist:" << xmlFile;
	}

	ZDomDocument doc;
	if (!doc.setContent(finfo.absoluteFilePath()))
		return;

	if (!m_pUiconfig->setupMainXml(doc))
		return;
}

void ZApplication::SetupAppInfo(const QString& name, const QString& version, const QIcon& icon)
{
	this->setOrganizationDomain("www.xxx.com");
	this->setOrganizationName("xxx");
	this->setApplicationName(name);
	this->setApplicationVersion(version);
	this->setWindowIcon(icon);
}

void ZApplication::setUiConfigure(ZUiConfigure* ui)
{
	m_pUiconfig = ui;
}

ZUiConfigure* ZApplication::getUiConfigure()
{
	return m_pUiconfig;
}
