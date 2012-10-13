/*
 * by lovewilliam <lovewilliam@gmail.com>
 */

#include "dataobject.h"

DataObject::DataObject(QObject *parent)
: QObject(parent)
{
}


DataObject::DataObject(QString _name ,bool _isTicked,QObject* parent)
:QObject(parent)
{
	m_name = _name;
	m_ticked = _isTicked;
}

void DataObject::setName(QString _name)
{
	m_name = _name;
	emit nameChanged();
}

void DataObject::setTicked(bool _ticked)
{
	m_ticked = _ticked;
	emit tickChanged(m_name,m_ticked);
}

QString DataObject::getName()
{
	return m_name;
}

bool DataObject::isTicked()
{
	return m_ticked;
}

