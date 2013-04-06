#include "fakeproperty.h"

FakeProperty::FakeProperty(const QString& key, QObject* parent) :
	QObject(parent), _key(key), _value(), _timestamp(0)
{
}

QString FakeProperty::key() const
{
	return _key;
}

QVariant FakeProperty::value() const
{
	return _value;
}

quint64 FakeProperty::timestamp() const
{
	return _timestamp;
}

void FakeProperty::setValue(const QVariant &value)
{
	_value = value;
	if (_timestamp) {
		emit valueChanged();
	}
}

void FakeProperty::startFaking()
{
	_timestamp = Q_INT64_C(-1); /* To have priority over other providers */
	emit valueChanged();
}

void FakeProperty::stopFaking()
{
	_timestamp = 0; /* To stop having priority over other providers */
	emit valueChanged();
}
