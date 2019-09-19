#pragma once

#include <QWidget>
#include <QToolButton>
#include "USBDiskDlg.h"

class ToolTipsDlg : public QWidget
{
	Q_OBJECT

public:
	ToolTipsDlg(USBDiskDlg *parent = NULL);
	~ToolTipsDlg();

	void initUI();

protected:
	//virtual void leaveEvent(QEvent* event);

private:
	QToolButton* m_pOpenToolBtn;
	QToolButton* m_pCloseToolBtn;
};
