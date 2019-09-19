#include "ToolTipsDlg.h"

#include <QHBoxLayout>

ToolTipsDlg::ToolTipsDlg(USBDiskDlg * parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	//setFixedSize(100, 300);
	initUI();

	hide();
}

ToolTipsDlg::~ToolTipsDlg()
{
}

void ToolTipsDlg::initUI()
{
	m_pOpenToolBtn = new QToolButton;
	m_pCloseToolBtn = new QToolButton;

	m_pOpenToolBtn->setText(tr(" 打开U盘 "));
	m_pCloseToolBtn->setText(tr(" 拔出U盘 "));

	m_pOpenToolBtn->setIcon(QIcon(":/image/open.png"));
	m_pCloseToolBtn->setIcon(QIcon(":/image/close.png"));

	m_pOpenToolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	m_pCloseToolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->addWidget(m_pOpenToolBtn);
	hLayout->addStretch();
	hLayout->addWidget(m_pCloseToolBtn);

	setLayout(hLayout);
}

//void ToolTipsDlg::leaveEvent(QEvent* event)
//{
//	this->close();
//}
