#ifndef __ZDOM_H__
#define __ZDOM_H__

#include "zglobal.h"
#include <QDomDocument>

class ZDomElement;

class Z_EXPORT ZDomDocument
{
public:
	ZDomDocument();
	~ZDomDocument();

	bool setContent(const QString & filePath);
	bool setContentText(const QString& text);
	ZDomElement zdocumentElement() const;
	QDomElement qdocumentElement() const;
	bool isNull() const;
	QString filePath() const;

private:
	QDomDocument m_doc;
	QString m_filePath;
};

class Z_EXPORT ZDomElement
{
public:
	enum CONDITION_TYPE
	{
		INVALID,
		EQUAL,
		NOEQUAL,
	};

	ZDomElement();
	ZDomElement(const ZDomElement& rhs);
	ZDomElement(const QDomElement& e, const QString& filepath, const QByteArray& tc = "");
	~ZDomElement();

	bool needFilter(const QDomElement& e) const;
	void customAttribute();
	bool isNull();
	QString attribute(const QString& name, const QString& defValue = QString()) const;
	bool hasAttribute(const QString& name) const;
	QDomNamedNodeMap attributes() const;
	QString tagName() const;
	void removeAttribute(const QString& name);
	ZDomElement firstChildElement(const QString &tagName = QString()) const;
	ZDomElement nextSiblingElement(const QString &tagName = QString()) const;
	int lineNumber() const;
	QString filePath() const;
	QString translate(const QString& attr) const;
	QString text() const;

private:
	bool isMatch(const QString &other, const QString &src) const;
	QString getPlatform() const;
	CONDITION_TYPE condition(QString &expr, QString &varname, QString &val) const;
	bool dealCondition(const QString &valInput, const QString &val, CONDITION_TYPE type) const;
	bool dealCondition(const bool &valInput, const QString &val, CONDITION_TYPE type) const;
	bool isThroughFilter(const QString &attr) const;
	bool isThroughFilterCond(const QString &cond) const;

private:
	QByteArray m_tc;
	QByteArray m_tcParent;
	QDomElement m_qElement;
	QString m_filePath;
};

#endif //__ZDOM_H__
