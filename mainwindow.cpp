#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow), model(nullptr), timer(0)
{
	ui->setupUi(this);
	qDebug() << "staff_name: " << staff_mngr::getName();
	qDebug() << "staff_role: " << static_cast<int>(staff_mngr::getRole());

	main_tab = ui->main_tab;
	watcher = ui->watcher;
	watcher->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	switch (staff_mngr::getRole()) {
	case staff_mngr::Role::ADMIN: {
		ui->overview->setEnabled(true);
		ui->purchase_analysis->setEnabled(true);
		ui->purchase_record->setEnabled(true);
		watcher->setVisible(false);
		watcher = nullptr;
		break;
	}
	case staff_mngr::Role::MANAGER: {
		ui->overview->setEnabled(true);
		ui->in_record->setEnabled(true);
		ui->out_record->setEnabled(true);
		model = medicines::get_io_wait_mngr_model();
		watcher->setModel(model);
		break;
	}
	case staff_mngr::Role::INSPECTOR: {
		model = medicines::get_qc_wait_model();
		watcher->setModel(model);
		break;
	}
	case staff_mngr::Role::APPLICANT: {
		ui->application_record->setEnabled(true);
		watcher->setVisible(false);
		watcher = nullptr;
		break;
	}
	}
	connect(ui->sync, &QAction::triggered, this, &MainWindow::sync);

	if (main_tab) {
		connect(main_tab, &QTabWidget::tabCloseRequested, this,
				&MainWindow::on_tabclose);
	}

	if (watcher) {
		timer = QObject::startTimer(600000);
		qDebug() << "timer id: " << timer;
		connect(watcher, &QTableView::doubleClicked, this,
				&MainWindow::watcher_enter);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
	if (!timer)
		QObject::killTimer(timer);
}

void MainWindow::sync()
{
	qDebug() << "sync";
	if (model) {
		QSqlQueryModel *m = nullptr;
		switch (staff_mngr::getRole()) {
		case staff_mngr::Role::ADMIN: {
			break;
		}
		case staff_mngr::Role::MANAGER: {
			m = medicines::get_io_wait_mngr_model();
			break;
		}
		case staff_mngr::Role::INSPECTOR: {
			m = medicines::get_qc_wait_model();
			break;
		}
		case staff_mngr::Role::APPLICANT: {
			break;
		}
		}
		if (m) {
			watcher->setModel(m);
			model->deleteLater();
			model = m;
			qDebug() << "watcher new lines: " << model->rowCount();
		}
	}
	if (watcher)
		watcher->update();
}

void MainWindow::on_tabclose(int index)
{
	qDebug() << "tab " << index << "closed";
	main_tab->currentWidget()->deleteLater();
}

QWidget *MainWindow::add_widget(QWidget *widget, QString title)
{
	if (main_tab) {
		main_tab->addTab(widget, title);
		main_tab->setCurrentWidget(widget);
	}
	return widget;
}

void MainWindow::on_overview_triggered()
{
	qDebug() << "open overview";
	overview *ov = new overview(this);
	add_widget(ov, "概览");
}

void MainWindow::on_purchase_analysis_triggered()
{
	qDebug() << "open analysis";
	analysis *ana = new analysis(this);
	add_widget(ana, "采购分析");
}

void MainWindow::on_purchase_record_triggered()
{
	qDebug() << "open purchase_record";
	purchase_record *pur = new purchase_record(this);
	add_widget(pur, "申请采购");
}

void MainWindow::on_application_record_triggered()
{
	qDebug() << "open application_recorder";
	application_record *apr = new application_record(this);
	add_widget(apr, "申请用药");
}

void MainWindow::on_in_record_triggered()
{
	qDebug() << "open in_recorder";
	in_recorder *inr = new in_recorder(this);
	connect(inr, &in_recorder::commited, this, &MainWindow::sync);
	add_widget(inr, "入库单");
}

void MainWindow::on_out_record_triggered()
{
	qDebug() << "open out_recorder";
	out_recorder *otr = new out_recorder(this);
	connect(otr, &out_recorder::commited, this, &MainWindow::sync);
	add_widget(otr, "出库单");
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == timer) {
		qDebug() << "time event";
		sync();
	}

	QMainWindow::timerEvent(event);
}

void MainWindow::watcher_enter(const QModelIndex &index)
{
	Q_UNUSED(index);
	switch (staff_mngr::getRole()) {
	case staff_mngr::Role::ADMIN: {
		break;
	}
	case staff_mngr::Role::MANAGER: {
		QString type = model->index(index.row(), 0).data().toString();
		int id = model->index(index.row(), 1).data().toInt();
		if (type == "入库") {
			in_recorder *inr = new in_recorder(this, id);
			add_widget(inr, "入库单");
			connect(inr, &in_recorder::commited, this, &MainWindow::sync);
		} else if (type == "出库") {
			out_recorder *otr = new out_recorder(this, id);
			connect(otr, &out_recorder::commited, this, &MainWindow::sync);
			add_widget(otr, "出库单");
		}
		break;
	}
	case staff_mngr::Role::INSPECTOR: {
		QString type = model->index(index.row(), 0).data().toString();
		int io_id = model->index(index.row(), 1).data().toInt();
		quality_record *qur = nullptr;
		if (type == "入库质检请求") {
			qur = new quality_record(0, io_id, this);
		} else if (type == "出库质检请求") {
			qur = new quality_record(1, io_id, this);
		}
		if (qur) {
			add_widget(qur, "质检单");
			connect(qur, &quality_record::commited, this, &MainWindow::sync);
		}
		break;
	}
	case staff_mngr::Role::APPLICANT: {
		break;
	}
	}
}
