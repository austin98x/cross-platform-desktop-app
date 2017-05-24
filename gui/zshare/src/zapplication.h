﻿#ifndef __ZAPPLICATION_H__
#define __ZAPPLICATION_H__

#include "zglobal.h"

class ZUiConfigure;

#define ZApplicationBase QApplication

class Z_EXPORT ZApplication : public ZApplicationBase
{
	Q_OBJECT
public:
	ZApplication (int & argc, char ** argv, const QString &appName);
	~ZApplication();

	void SetupFont();
	void SetupTranslator();
	void SetupXmlUserface(const QString& xmlFile);
	void SetupAppInfo(const QString& name, const QString& version, const QIcon& icon);

	void setUiConfigure(ZUiConfigure* ui);
	ZUiConfigure* getUiConfigure();

private:
	ZUiConfigure* m_pUiconfig;
};

#define zApp ((ZApplication *)qApp)

#endif //__ZAPPLICATION_H__
