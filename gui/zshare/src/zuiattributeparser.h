#ifndef __ZUI_ATTRIBUTEPARSER_H__
#define __ZUI_ATTRIBUTEPARSER_H__

#include "zglobal.h"

class ZCommands;
class ZCommand;
class ZDomDocument;
class ZDomElement;

class Z_EXPORT ZUiAttributeParser : public QObject
{
public:
	enum Type
	{
		Type_Unknown = -1,
		Type_String,
		Type_Command,
		Type_Bool,
		Type_Int,
		Type_Icon,
		Type_Enum,
		Type_Color,
		Type_Double,
	};
	typedef QMap<QString, int> enummap_type;
	typedef QMap<QString, enummap_type> enummaps_type;

	ZUiAttributeParser(QObject* parent);
	~ZUiAttributeParser();

	bool setupMainXml(const ZDomDocument& mdoc);
	bool setupXml(const ZDomDocument& doc);
	void resetXml();
#if 0
	QVariant parseAttribute(const QString& var, const QString& val, ZCommands* cmds);
	QVariant parseAttribute(Type type, const QString& val, ZCommands* cmds);
	QVariant parseAttribute(int type, const QString& val, ZCommands* cmds);
#endif
	static bool parseBool(const QString& val);
	static int parseInt(const QString& val, bool* isSucceed = NULL);
	static double parseDouble(const QString& val, bool* isSucceed = NULL);
	static QIcon parseIcon(const QString& val);
	static QVariant parseEnum(const enummap_type& em, const QString& val);
	static QVariant parseColor(const QString& val);
	static ZCommand * parseCommand(ZCommands* cmds, const QString& val);

private:
	Type recognizedType(const QString & t);
	enummap_type _parseEnumList(ZDomElement & e);

private:
	QMap<QString, Type> m_attrType;
	enummaps_type m_enumMaps;
};

#endif//__ZUI_ATTRIBUTEPARSER_H__
