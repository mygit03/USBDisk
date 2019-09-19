#pragma once

#include <QWidget>
#include <windows.h>
#include <QAbstractNativeEventFilter>

struct DISKINFO
{
	QString name;
	qint64  size;
	qint64	availableSize;
};

class USBDisk : public QWidget, public QAbstractNativeEventFilter
{
	Q_OBJECT

public:
	DISKINFO GetDiskInfo(QString fileName);

protected:
	bool nativeEventFilter(const QByteArray& eventType, void* message, long* result);

signals:
	void sigUDiskCome(QString uDiskName);
	void sigUDiskRemove();

private:
	char FirstDriveFromMask(ULONG unitmask);
};
