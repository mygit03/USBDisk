#include "USBDiskDlg.h"

#include "USBDisk.h"
#include "ToolTipsDlg.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QToolButton>
#include <QFont>

#define GB (1024.0 * 1024.0 * 1024.0)

USBDisk* m_pUSBDisk = NULL;
bool m_Drag;                //判断鼠标左键是否按下
QPoint m_DragPosition;

USBDiskDlg::USBDiskDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	//setWindowOpacity(0.5);

	initUI();
	dlg = new ToolTipsDlg(/*this*/);

	m_pUSBDisk = new USBDisk;

	qApp->installNativeEventFilter(m_pUSBDisk);

	connect(m_pUSBDisk, &USBDisk::sigUDiskCome, [=](QString uDiskName) {
		DISKINFO info = m_pUSBDisk->GetDiskInfo(uDiskName + ":");
		QString size = QString::number(info.availableSize / GB, 'f', 2);
		QString useSize = QString::number((info.size - info.availableSize) / GB, 'f', 2);
		QString allSize = QString::number(info.size / GB, 'f', 2);

		m_pLabel->setText(tr("<strong>%1<br>剩余空间:%2GB</strong>").arg(info.name).arg(size));
		m_pProgressBar->setRange(0, allSize.toDouble());
		m_pProgressBar->setValue(useSize.toDouble());
		m_pTipsLabel->setText(tr("<strong>%1GB/%2GB</strong>").arg(useSize).arg(allSize));

		this->show();
	});
	connect(m_pUSBDisk, &USBDisk::sigUDiskRemove, [=]() {
		m_pLabel->setText(tr("U Disk Remove!"));

		this->hide();
	});
}

void USBDiskDlg::initUI()
{
	QToolButton* iconToolBtn = new QToolButton;
	iconToolBtn->setAutoRaise(true);
	iconToolBtn->setAutoRepeat(true);
	QIcon icon(":/image/udisk.png");
	iconToolBtn->setIcon(icon);
	iconToolBtn->setIconSize(QSize(80, 80));

	m_pLabel = new QLabel;
	m_pLabel->setWordWrap(true);
	QFont font;
	font.setPixelSize(13);
	m_pLabel->setFont(font);

	m_pProgressBar = new QProgressBar;

	m_pTipsLabel = new QLabel;

	QGridLayout* gridLayout = new QGridLayout;
	gridLayout->addWidget(iconToolBtn, 0, 0, 3, 1);
	gridLayout->addWidget(m_pLabel, 0, 1, 1, 1);
	gridLayout->addWidget(m_pProgressBar, 1, 1, 1, 1);
	gridLayout->addWidget(m_pTipsLabel, 2, 1, 1, 1);

	setLayout(gridLayout);
}

void USBDiskDlg::enterEvent(QEvent* event)
{
	dlg->show();
}

void USBDiskDlg::leaveEvent(QEvent* event)
{
	dlg->close();
}

void USBDiskDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void USBDiskDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void USBDiskDlg::mouseReleaseEvent(QMouseEvent* event)
{
	m_Drag = false;
}
