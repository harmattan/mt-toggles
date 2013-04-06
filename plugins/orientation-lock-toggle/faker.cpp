#include "faker.h"

#define SERVICE_NAME "com.mohammadag.glol"

Faker::Faker(const QString& val, QObject *parent) :
	QObject(parent), _bus(QDBusConnection::sessionBus()),
	_property(new FakeProperty("Screen.TopEdge")),
    _adaptor(new FakePropertyAdaptor(_property)),
    _isActive(false)
{
    setValue(val);
}

void Faker::start()
{
    _isActive = true;
	_bus.registerObject(_adaptor->objectPath(), _property);
	_bus.registerService(SERVICE_NAME);
	_property->startFaking();
}

void Faker::stop()
{
    _isActive = false;
	_property->stopFaking();
	_bus.unregisterService(SERVICE_NAME);
	_bus.unregisterObject(_adaptor->objectPath());
}

void Faker::setValue(const QString &val)
{
    _currentValue = val;
    _property->setValue(val);
}
