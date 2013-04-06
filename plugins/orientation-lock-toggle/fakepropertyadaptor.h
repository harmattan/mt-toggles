#ifndef FAKEPROPERTYADAPTOR_H
#define FAKEPROPERTYADAPTOR_H

#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusConnection>

#include "fakeproperty.h"

class FakePropertyAdaptor : public QDBusAbstractAdaptor
{
	Q_OBJECT
	Q_CLASSINFO("D-Bus Interface", "org.maemo.contextkit.Property")

public:
	explicit FakePropertyAdaptor(FakeProperty* property);
	QString objectPath() const;

signals:
	void ValueChanged(const QVariantList &values, const quint64& timestamp);

public slots:
	void Subscribe(const QDBusMessage& msg, QVariantList& values, quint64& timestamp);
	void Unsubscribe(const QDBusMessage& msg);
	void Get(QVariantList& values, quint64& timestamp);

protected:
	FakeProperty* _property;

protected slots:
	void propertyChanged();
};

#endif // FAKEPROPERTYADAPTOR_H
