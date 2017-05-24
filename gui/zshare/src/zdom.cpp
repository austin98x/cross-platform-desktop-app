#include "stdafx.h"
#include "zdom.h"
#include <QFile>

ZDomDocument::ZDomDocument()
{

}

ZDomDocument::~ZDomDocument()
{

}

bool ZDomDocument::setContent(const QString & filePath)
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning() << "ZApplication: Can not load ui xml file! path:" << filePath;
		return false;
	}
	QString errmsg;
	int errline = 0;
	if (!m_doc.setContent(&file, &errmsg, &errline))
	{
		qWarning() << "ZDomDocument:" << errline << ":" << errmsg;
		return false;
	}
	m_filePath = filePath;
	return true;
}

bool ZDomDocument::setContentText(const QString& text)
{
	QString errmsg;
	int errline = 0;
	if (!m_doc.setContent(text, &errmsg, &errline))
	{
		qWarning() << "ZDomDocument:" << errline << ":" << errmsg;
		return false;
	}

	return true;
}

ZDomElement ZDomDocument::zdocumentElement() const
{
	return ZDomElement(qdocumentElement(), m_filePath);
}

QDomElement ZDomDocument::qdocumentElement() const
{
	return m_doc.documentElement();
}

bool ZDomDocument::isNull() const
{
	return m_doc.isNull();
}

QString ZDomDocument::filePath() const
{
	return m_filePath;
}

///////////////////////////////////////////////////////////////////////////
ZDomElement::ZDomElement()
{
	customAttribute();
}

ZDomElement::ZDomElement(const ZDomElement& rhs)
	: m_qElement(rhs.m_qElement), m_tc(rhs.m_tc), m_tcParent(rhs.m_tcParent), m_filePath(rhs.m_filePath)
{
	customAttribute();
}

ZDomElement::ZDomElement(const QDomElement& e, const QString& filepath, const QByteArray& tc)
	: m_tcParent(tc), m_tc(tc), m_filePath(filepath)
{
	QString subtc = e.attribute("tc");
	if (!subtc.isNull())
	{
		if (!m_tc.isEmpty())
			m_tc.append(".");
		m_tc.append(subtc.toUtf8());
	}
	m_qElement = e;
	customAttribute();
}

ZDomElement::~ZDomElement()
{

}

bool ZDomElement::needFilter(const QDomElement& e) const
{
	if (e.hasAttribute("filter"))
	{
		QString attr = e.attribute("filter");
		if (!isThroughFilter(attr))
		{
			return true;
		}
	}
	return false;
}

void ZDomElement::customAttribute()
{
	if (hasAttribute("customAttribute"))
	{
		QString attr = attribute("customAttribute");
		QStringList assignList = attr.split("IF");
		foreach(QString assignAttr, assignList)
		{
			if (assignAttr.isEmpty())
				continue;

			int conLeft = assignAttr.indexOf("(") + 1;
			int conRight = assignAttr.indexOf(")") - 1;
			int conLength = conRight - conLeft + 1;
			QString conditions = assignAttr.mid(conLeft, conLength);

			int assignLeft = assignAttr.indexOf("{") + 1;
			int assignRight = assignAttr.indexOf("}") - 1;
			int assignLength = assignRight - assignLeft + 1;
			QString assignments = assignAttr.mid(assignLeft, assignLength);

			if (isThroughFilter(conditions))
			{
				QStringList assignmentList = assignments.split(";");
				foreach(QString assignment, assignmentList)
				{
					QStringList attrAndValue = assignment.split("=");
					if (attrAndValue.count() > 1)
					{
						m_qElement.setAttribute(attrAndValue.first(), attrAndValue.last());
					}
				}
			}
		}
	}
}

bool ZDomElement::isNull()
{
	return m_qElement.isNull();
}

QString ZDomElement::attribute(const QString& name, const QString& defValue) const
{
	QString r = m_qElement.attribute(name, defValue);
	return translate(r);
}

bool ZDomElement::hasAttribute(const QString& name) const
{
	return m_qElement.hasAttribute(name);
}

QDomNamedNodeMap ZDomElement::attributes() const
{
	return m_qElement.attributes();
}

QString ZDomElement::tagName() const
{
	return m_qElement.tagName();
}

void ZDomElement::removeAttribute(const QString &name)
{
	m_qElement.removeAttribute(name);
}

ZDomElement ZDomElement::firstChildElement(const QString &tagName /*= QString()*/) const
{
	QDomElement child = m_qElement.firstChildElement(tagName);

	while (!child.isNull() && needFilter(child))
	{
		child = child.nextSiblingElement(tagName);
	}

	return ZDomElement(child, m_filePath, m_tc);
}

ZDomElement ZDomElement::nextSiblingElement(const QString &tagName /*= QString()*/) const
{
	QDomElement next = m_qElement.nextSiblingElement(tagName);

	while (!next.isNull() && needFilter(next))
	{
		next = next.nextSiblingElement(tagName);
	}

	return ZDomElement(next, m_filePath, m_tcParent);
}

int ZDomElement::lineNumber() const
{
	return m_qElement.lineNumber();
}

QString ZDomElement::filePath() const
{
	return m_filePath;
}

QString ZDomElement::translate(const QString& attr) const
{
	QString r = attr;
	if (r.size() > 1 && r.at(0) == '@')
	{
		int second_at = r.indexOf('@', 1);
		if (second_at != -1)
		{
			QString disamb = r.mid(second_at + 1);
			r = qApp->translate(m_tc, r.mid(1, second_at - 1).toUtf8().data(), disamb.toUtf8().data(), QApplication::UnicodeUTF8);
		}
		else
		{
			r = qApp->translate(m_tc, r.toUtf8().data() + 1, NULL, QApplication::UnicodeUTF8);
		}
	}

	// if have lengthvariant, get the first.
	QStringList l = r.split(QChar(ushort(0x9c)));
	if (l.length() > 0)
		r = l[0];

	return r;
}

QString ZDomElement::text() const
{
	QDomNode cloneNode = m_qElement.cloneNode();
	QDomElement cloneEle = cloneNode.toElement();
	cloneEle.setAttribute("tc", QString(m_tc));
	QString str;
	QTextStream stream(&str);
	cloneEle.save(stream, 0);
	return str;
}

bool ZDomElement::isMatch(const QString &other,const QString &src) const
{
	QStringList list = src.split(",");
	foreach (QString expr,list)
	{
		QString str = expr.trimmed();
		if (str == other)
			return true;
	}

	return false;
}

QString ZDomElement::getPlatform() const
{
#if defined(Q_OS_WIN32)
	QString platform = "windows";
#elif defined(Q_OS_UNIX)
	QString platform = "unix";
#elif defined(Q_OS_MAC)
	QString platform = "mac";
#else
	#error "Unknown platform!";
#endif

	return platform;
}

ZDomElement::CONDITION_TYPE ZDomElement::condition(QString &expr, QString &varname, QString &val) const
{
	CONDITION_TYPE type = INVALID;

	QStringList list = expr.split("!=");
	if (list.count() == 2)
	{
		type = NOEQUAL;
	}
	else if (list.count() == 1)
	{
		list = expr.split("=");
		if (list.count() == 2)
		{
			type = EQUAL;
		}
	}

	if (type != INVALID)
	{
		varname = list[0].trimmed();
		val = list[1].trimmed();
	}

	return type;
}

bool ZDomElement::dealCondition(const QString &valInput, const QString &val, CONDITION_TYPE type) const
{
	if (type == EQUAL)
	{
		return isMatch(valInput, val);
	}
	else if (type == NOEQUAL)
	{
		return !isMatch(valInput, val);
	}
	return true;
}

bool ZDomElement::dealCondition(const bool &valInput, const QString &val, CONDITION_TYPE type) const
{
	if (type == EQUAL)
	{
		return valInput == QVariant(val).toBool();
	}
	else if (type == NOEQUAL)
	{
		return valInput != QVariant(val).toBool();
	}
	return true;
}

bool ZDomElement::isThroughFilter(const QString &attr) const
{
	QStringList list = attr.split("|");
	foreach (QString exp, list)
	{
		if (isThroughFilterCond(exp))
			return true;
	}
	return false;
}

bool ZDomElement::isThroughFilterCond(const QString &cond) const
{
	QStringList list = cond.split(";");
	foreach (QString exp, list)
	{
		QString varname;
		QString val;

		CONDITION_TYPE type = condition(exp, varname, val);

		if (type == INVALID)
			return true;

		if (QString::compare(varname,"platform") == 0)
		{
			if (!dealCondition(getPlatform(), val, type))
				return false;
		}
		else
		{
			qWarning("filter format error!");
		}
	}

	return true;
}
