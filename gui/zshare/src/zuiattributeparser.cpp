#include "stdafx.h"
#include "zuiattributeparser.h"
#include "zdom.h"
//#include "zcommands.h"
//#include "zcommand.h"
#include <QFile>

ZUiAttributeParser::ZUiAttributeParser(QObject* parent)
	: QObject(parent)
{

}

ZUiAttributeParser::~ZUiAttributeParser()
{

}

bool ZUiAttributeParser::setupMainXml(const ZDomDocument& mdoc)
{
	ZDomElement e = mdoc.zdocumentElement().firstChildElement("attributes");
	if (e.isNull())
		return false;

	QString path = e.attribute("path");
	if (path.isEmpty())
	{
		qWarning() << "attributes at " << e.lineNumber() << ": " << " need path attribute.";
		return false;
	}

	QFileInfo finfo(QFileInfo(mdoc.filePath()).dir(), path);
	if (!finfo.exists())
	{
		qWarning() << "ZUiAttributeParser: XML: file not exist:" << path;
		return false;
	}

	ZDomDocument doc;
	if (!doc.setContent(finfo.absoluteFilePath()))
		return false;

	return setupXml(doc);
}

bool ZUiAttributeParser::setupXml(const ZDomDocument& doc)
{
	ZDomElement e = doc.zdocumentElement();
	ZDomElement sub = e.firstChildElement("attributes").firstChildElement("attribute");
	for (; !sub.isNull(); sub = sub.nextSiblingElement("attribute"))
	{
		QString name = sub.attribute("name");
		Type type = recognizedType(sub.attribute("type"));
		if (type == Type_Unknown)
			continue;
		m_attrType[name] = type;
		if (type == Type_Enum)
		{
			m_enumMaps[name] = _parseEnumList(sub);
		}
	}

	return true;
}

void ZUiAttributeParser::resetXml()
{
	m_attrType.clear();
	m_enumMaps.clear();
}

#if 0
QVariant ZUiAttributeParser::parseAttribute(const QString& var, const QString& val, ZCommands* cmds)
{
	QMap<QString, Type>::iterator it = m_attrType.find(var);
	Type t = Type_Unknown;
	if (it != m_attrType.end())
	{
		t = *it;
	}

	if (t == Type_Enum)
	{
		return parseEnum(m_enumMaps.value(var), val);
	}

	return parseAttribute(t, val, cmds);
}

QVariant ZUiAttributeParser::parseAttribute(Type type, const QString& val, ZCommands* cmds)
{
	switch (type)
	{
	case Type_String:
		return val;
	case Type_Bool:
		return parseBool(val);
	case Type_Int:
		return parseInt(val);
	case Type_Double:
		return parseDouble(val);
	case Type_Command:
		return qVariantFromValue(parseCommand(cmds, val));
	case Type_Icon:
		return parseIcon(val);
	case Type_Color:
		return parseColor(val);
	}
	return QVariant();
}

QVariant ZUiAttributeParser::parseAttribute(int type, const QString& val, ZCommands* cmds)
{
	static const int s_KCommand_TypeID = qMetaTypeId<ZCommand*>();

	Type t = Type_Unknown;
	if (type == s_KCommand_TypeID)
	{
		t = Type_Command;
	}
	else
	{
		switch (type)
		{
		case QVariant::String:
			t = Type_String; break;
		case QVariant::Bool:
			t = Type_Bool; break;
		case QVariant::Int:
			t = Type_Int; break;
		case QVariant::Icon:
			t = Type_Icon; break;
		}
	}

	return parseAttribute(t, val, cmds);
}
#endif

bool ZUiAttributeParser::parseBool(const QString& val)
{
	if (val.isEmpty())
		return false;
	bool bInt = false;
	int x = val.toInt(&bInt);
	if (bInt && x == 0)
		return false;
	if (val.trimmed().toLower() == "false")
		return false;
	return true;
}

int ZUiAttributeParser::parseInt(const QString& val, bool* isSucceed)
{
	bool bInt = false;
	int x = val.toInt(&bInt);
	if (!bInt)
	{
		if (isSucceed)
			*isSucceed = false;
		return -1;
	}
	if (isSucceed)
		*isSucceed = true;
	return x;
}

ZCommand * ZUiAttributeParser::parseCommand(ZCommands* cmds, const QString& val)
{
#if 0
	ZCommand * cmd = cmds->command(val);
	if (!cmd)
	{
		qWarning() << "can not find command named:" << val;
		return NULL;
	}
	return cmd;
#else
	return NULL;
#endif
}

QIcon ZUiAttributeParser::parseIcon(const QString& val)
{
	QIcon icon;
	icon.addFile(val);
	return icon;
}

double ZUiAttributeParser::parseDouble(const QString& val, bool* isSucceed)
{
	bool bDouble = false;
	double x = val.toDouble(&bDouble);
	if (!bDouble)
	{
		if (isSucceed)
			*isSucceed = false;
		return -1;
	}
	if (isSucceed)
		*isSucceed = true;
	return x;
}

QVariant ZUiAttributeParser::parseEnum(const enummap_type& em, const QString& val)
{
	if (em.find(val) != em.end())
	{
		return em.value(val);
	}
	qWarning() << "Unknown enum:" << val;
	return QVariant();
}

QVariant ZUiAttributeParser::parseColor(const QString& val)
{
	bool bok = false;
	return QVariant(val.toUInt(&bok,16));
}

ZUiAttributeParser::enummap_type ZUiAttributeParser::_parseEnumList(ZDomElement& e)
{
	enummap_type em;
	int lastvalue = -1;
	ZDomElement s = e.firstChildElement("item");
	for (; !s.isNull(); s = s.nextSiblingElement("item"))
	{
		QString name = s.attribute("name");
		QString sv = s.attribute("value");
		int v = lastvalue + 1;
		if (!sv.isNull())
		{
			bool bInt;
			int x = sv.toInt(&bInt);
			if (!bInt)
				qWarning() << "bad format, at line: " << e.lineNumber();
			else
				v = x;
		}
		em[name] = v;
		lastvalue = v;
	}
	return em;
}

ZUiAttributeParser::Type ZUiAttributeParser::recognizedType(const QString& t)
{
	if (t.isEmpty())
		return Type_String;
	if (t == "string")
		return Type_String;
	if (t == "command")
		return Type_Command;
	if (t == "bool")
		return Type_Bool;
	if (t == "int")
		return Type_Int;
	if (t == "icon")
		return Type_Icon;
	if (t == "enum")
		return Type_Enum;
	if (t == "color")
		return Type_Color;
	if (t == "double")
		return Type_Double;
	return Type_Unknown;
}
