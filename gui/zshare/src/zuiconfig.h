#ifndef __ZUICONFIG_H__
#define __ZUICONFIG_H__

#include "zglobal.h"

class ZDomDocument;
class ZUiAttributeParser;

class Z_EXPORT ZUiConfigure
{
public:
	ZUiConfigure(QObject* parent);
	~ZUiConfigure();

	bool setupMainXml(const ZDomDocument& mdoc);
	void resetXml();

private:
	ZUiAttributeParser* m_pAttrParser;
};

#endif //__ZUICONFIG_H__
