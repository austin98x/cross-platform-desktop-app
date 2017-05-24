#include "stdafx.h"
#include "zuiconfig.h"
#include "zuiattributeparser.h"
#include "zdom.h"

ZUiConfigure::ZUiConfigure(QObject* parent)
{
	m_pAttrParser = new ZUiAttributeParser(parent);
}

ZUiConfigure::~ZUiConfigure()
{

}

bool ZUiConfigure::setupMainXml(const ZDomDocument& mdoc)
{
	if (!m_pAttrParser->setupMainXml(mdoc))
		return false;

	return true;
}

void ZUiConfigure::resetXml()
{
	m_pAttrParser->resetXml();
}
