#include "USBDisk.h"

#include <dbt.h>
#include <QStorageInfo>
#include <QDebug>

bool USBDisk::nativeEventFilter(const QByteArray& eventType, void* message, long* result)
{
	MSG* msg = reinterpret_cast<MSG*>(message);
	int msgType = msg->message;
	if (msgType == WM_DEVICECHANGE) {
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
		switch (msg->wParam) {
		case DBT_DEVICEARRIVAL:
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME) {
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				if (lpdbv->dbcv_flags == 0) {
					QString USBDiskName = QString(this->FirstDriveFromMask(lpdbv->dbcv_unitmask));
					emit sigUDiskCome(USBDiskName);
				}
			}
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME) {
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				if (lpdbv->dbcv_flags == 0) {
					emit sigUDiskRemove();
				}
			}
			break;
		case DBT_DEVNODES_CHANGED:
			break;
		default:
			break;
		}
	}
	return QWidget::nativeEvent(eventType, message, result);
}

char USBDisk::FirstDriveFromMask(ULONG unitmask)
{
	char i;
	for (i = 0; i < 26; ++i) {
		if (unitmask & 0x1) {
			break;
		}
		unitmask = unitmask >> 1;
	}
	return (i + 'A');
}

DISKINFO USBDisk::GetDiskInfo(QString path)
{
#if 1
	DISKINFO info;
	QStorageInfo storage(path);
	qDebug() << "rootpath:" << storage.rootPath();
	info.name = storage.displayName().append(QString("(%1)").arg(path));
	info.size = storage.bytesTotal();
	info.availableSize = storage.bytesAvailable();
#else
	foreach(const QStorageInfo & storage, QStorageInfo::mountedVolumes())
	{
		if (storage.isValid() && storage.isReady()) {
			if (!storage.isReadOnly()) {
				qDebug() << "";
				qDebug() << "rootpath:" << storage.rootPath();
				qDebug() << "name:" << storage.name();
				qDebug() << "displayname:" << storage.displayName();
				qDebug() << "fileSystemType:" << storage.fileSystemType();
				qDebug() << "size:" << storage.bytesTotal() / 1000 / 1000 << "MB";
				qDebug() << "availableSize:" << storage.bytesAvailable() / 1000 / 1000 << "MB";
			}
		}
	}
#endif

	return info;
}
