#ifndef FAKER_H
#define FAKER_H

#include <QtDBus/QDBusConnection>

#include "fakeproperty.h"
#include "fakepropertyadaptor.h"

class Faker : public QObject
{
    Q_OBJECT
public:
	explicit Faker(const QString& val, QObject *parent = 0);
    QString currentValue() { return _currentValue; }
    bool isActive() { return _isActive; }

signals:

public slots:
	void start();
	void stop();
    void setValue(const QString &val);

protected:
	QDBusConnection _bus;
	FakeProperty *_property;
	FakePropertyAdaptor *_adaptor;

private:
    QString _currentValue;
    bool _isActive;
};

#endif // FAKER_H
