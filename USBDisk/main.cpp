#include "USBDiskDlg.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	USBDiskDlg w;
	w.show();
	return a.exec();
}
