#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QSharedPointer<staff_mngr> staff, QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	qDebug() << "staff_name: " << staff->getName();
	qDebug() << "staff_role: " << static_cast<int>(staff->getRole());
}

MainWindow::~MainWindow() { delete ui; }
