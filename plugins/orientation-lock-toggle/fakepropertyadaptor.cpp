#include <QtCore/QRegExp>
#include <QtCore/QDebug>
#include <QtDBus/QDBusMessage>

#include "fakepropertyadaptor.h"

FakePropertyAdaptor::FakePropertyAdaptor(FakeProperty* property) :
	QDBusAbstractAdaptor(property), _property(property)
{
	connect(_property, SIGNAL(valueChanged()), SLOT(propertyChanged()));
}

QString FakePropertyAdaptor::objectPath() const
{
	if (_property->key().startsWith("/"))
		return QString(_property->key());

	return QString("/org/maemo/contextkit/") +
			QString(_property->key()).replace(".", "/").replace(QRegExp("[^A-Za-z0-9_/]"), "_");
}

void FakePropertyAdaptor::Subscribe(const QDBusMessage& msg, QVariantList& values, quint64& timestamp)
{
	Q_UNUSED(msg);
	Get(values, timestamp);
}

void FakePropertyAdaptor::Unsubscribe(const QDBusMessage& msg)
{
	Q_UNUSED(msg);
}

void FakePropertyAdaptor::Get(QVariantList& values, quint64& timestamp)
{
	values << _property->value();
	timestamp = _property->timestamp();
}

void FakePropertyAdaptor::propertyChanged()
{
	QVariantList values;
	quint64 timestamp;
	Get(values, timestamp);
	emit ValueChanged(values, timestamp);
}
