#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QSharedPointer<staff_mngr> _staff, QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow), staff(_staff)
{
	ui->setupUi(this);
	qDebug() << "staff_name: " << staff->getName();
	qDebug() << "staff_role: " << static_cast<int>(staff->getRole());
	switch (staff->getRole()) {
	case staff_mngr::Role::ADMIN: {
		ui->overview->setEnabled(true);
		ui->purchase_analysis->setEnabled(true);
		ui->purchase_record->setEnabled(true);
		break;
	}
	case staff_mngr::Role::MANAGER: {
		ui->overview->setEnabled(true);
		ui->in_record->setEnabled(true);
		ui->out_record->setEnabled(true);
		break;
	}
	case staff_mngr::Role::INSPECTOR: {
		ui->quality_record->setEnabled(true);
		break;
	}
	case staff_mngr::Role::APPLICANT: {
		ui->application_record->setEnabled(true);
		break;
	}
	}
	connect(ui->sync, &QAction::triggered, this, &MainWindow::sync);

	main_tab = ui->main_tab;
	connect(main_tab, &QTabWidget::tabCloseRequested, this,
			&MainWindow::on_tabclose);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::sync() { qDebug() << "sync"; }

void MainWindow::on_tabclose(int index)
{
	qDebug() << "tab " << index << "closed";
	main_tab->currentWidget()->deleteLater();
}

QWidget *MainWindow::add_widget(QWidget *widget, QString title)
{
	main_tab->addTab(widget, title);
	main_tab->setCurrentWidget(widget);
	// widget->show();
	return widget;
}

void MainWindow::on_overview_triggered()
{
	qDebug() << "open overview";
	overview *ov = new overview;
	add_widget(ov, "概览");
}
