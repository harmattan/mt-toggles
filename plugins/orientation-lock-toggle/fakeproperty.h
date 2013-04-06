#ifndef FAKEPROPERTY_H
#define FAKEPROPERTY_H

#include <QtCore/QVariant>

class FakeProperty : public QObject
{
    Q_OBJECT
public:
	explicit FakeProperty(const QString& key, QObject *parent = 0);
	QString key() const;
	QVariant value() const;
	quint64 timestamp() const;

signals:
	void valueChanged();

public slots:
	void setValue(const QVariant& value);
	void startFaking();
	void stopFaking();

protected:
	QString _key;
	QVariant _value;
	quint64 _timestamp;

};

#endif // FAKEPROPERTY_H
