#pragma once

#include <QtWidgets/QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QMouseEvent>

class ToolTipsDlg;

class USBDiskDlg : public QDialog
{
	Q_OBJECT

public:
	USBDiskDlg(QWidget *parent = Q_NULLPTR);
	void initUI();

protected:
	virtual void enterEvent(QEvent* event);
	virtual void leaveEvent(QEvent* event);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private:
	QLabel		 * m_pLabel;
	QProgressBar * m_pProgressBar; 
	QLabel		 * m_pTipsLabel;

	ToolTipsDlg  * dlg;
};
