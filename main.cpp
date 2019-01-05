#include "database_mngr.h"
#include "login_dialog.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSqlError sqlerr = database_mngr::connect();
	if (sqlerr.isValid()) {
		QMessageBox::critical(nullptr, "错误", sqlerr.text(), QMessageBox::Yes);
		return -1;
	}
	login_dialog logind;
	if (logind.exec() == QDialog::Accepted) {
		MainWindow w(logind.staff);
		w.show();
		return a.exec();
	}
	return -1;
}
