#include "in_recorder.h"
#include "ui_in_recorder.h"

in_recorder::in_recorder(QWidget *parent, int _inr)
	: QWidget(parent), ui(new Ui::in_recorder), inr(_inr), storage_num_sum(0)
{
	ui->setupUi(this);
	date = QDate::currentDate();
	storage = ui->storage;

	ui->date->setText(date.toString("yyyy/M/d"));
	ui->staff->setText(staff_mngr::getName());
	QIntValidator *iv = new QIntValidator(1, 10000, this);
	ui->all_num->setValidator(iv);
	ui->num->setValidator(iv);
	ui->wid->setValidator(iv);
	ui->detail->setVisible(false);
	if (inr != -1) {
		ui->all_num->setReadOnly(true);
		ui->batch_num->setReadOnly(true);
		ui->production_date->setReadOnly(true);
		ui->select_pur->setVisible(false);
		ui->req_qur->setVisible(false);
		QSqlQueryModel *model = medicines::get_inr_info(inr);
		if (model && model->rowCount() == 1) {
			QSqlRecord rec = model->record(0);
			int state = rec.value(0).toInt();
			qDebug() << "inr state: " << state;
			ui->mid->setText(rec.value(1).toString());
			ui->batch_num->setText(rec.value(2).toString());
			ui->all_num->setText(QString::number(rec.value(3).toInt()));
			ui->date->setText(rec.value(4).toDate().toString("yyyy/M/d"));
			ui->staff->setText(rec.value(5).toString());
			int qur_id_tmp = rec.value(6).toInt();
			ui->pur_id->setText(QString::number(rec.value(7).toInt()));
			ui->production_date->setDate(rec.value(8).toDate());
			ui->quality->setText(rec.value(9).toString());
			ui->ap_name->setText(rec.value(10).toString());
			ui->pur_num->setText(QString::number(rec.value(11).toInt()));
			ui->goted->setText(QString::number(rec.value(12).toInt()));
			model->deleteLater();
			if (state == 0) {
				ui->qur_id->setText("");
			} else {
				ui->qur_id->setText(QString::number(qur_id_tmp));
				ui->detail->setVisible(true);
			}
		} else {
			qDebug() << "model row err count: " << model->rowCount();
		}
	}
}

in_recorder::~in_recorder() { delete ui; }

void in_recorder::on_select_pur_clicked()
{
	pur_selecter pselecter(this);
	if (pselecter.exec() == QDialog::Accepted) {
		qDebug() << "pselecter acc";
		ui->pur_id->setText(QString::number(pselecter.getPur_id()));
		ui->mid->setText(pselecter.getMid());
		ui->ap_name->setText(pselecter.getAp_name());
		ui->pur_num->setText(QString::number(pselecter.getNum()));
		ui->goted->setText(QString::number(pselecter.getGoted()));
	}
	pselecter.deleteLater();
}

void in_recorder::on_req_qur_clicked()
{
	if (ui->mid->text().length() > 0 && ui->batch_num->text().length() > 0 &&
		ui->all_num->text().length() > 0) {
		int num = ui->all_num->text().toInt();
		int pur_num = ui->pur_num->text().toInt();
		int goted = ui->goted->text().toInt();
		if (num + goted > pur_num) {
			QMessageBox::warning(this, "警告", "入库数量超过订单",
								 QMessageBox::Yes);
			return;
		}
		if (medicines::add_inr(ui->mid->text(), ui->batch_num->text(), num,
							   date, staff_mngr::getId(),
							   ui->pur_id->text().toInt(),
							   ui->production_date->date())
				.isValid()) {
			QMessageBox::critical(this, "错误", "申请失败", QMessageBox::Yes);
		} else {
			ui->req_qur->setEnabled(false);
			emit commited();
			QMessageBox::information(this, "提示", "申请成功, 已暂存",
									 QMessageBox::Yes);
		}
	}
}

void in_recorder::update_commit_btn()
{
	if (ui->all_num->text().toInt() == storage_num_sum)
		ui->commit->setEnabled(true);
	else {
		ui->commit->setEnabled(false);
	}
}

void in_recorder::on_insert_clicked()
{
	if (ui->wid->text().length() > 0 && ui->num->text().length() > 0) {
		int wid = ui->wid->text().toInt();
		int num = ui->num->text().toInt();
		if (num > 0) {
			storage->insertRow(storage->rowCount());
			storage->setItem(storage->rowCount() - 1, 0,
							 new QTableWidgetItem(QString::number(wid)));
			storage->setItem(storage->rowCount() - 1, 1,
							 new QTableWidgetItem(QString::number(num)));
			ui->wid->clear();
			ui->num->clear();
			storage_num_sum += num;
			update_commit_btn();
		}
	}
}

void in_recorder::on_rollback_clicked()
{
	if (storage->rowCount() > 0) {
		storage_num_sum -=
			storage->item(storage->rowCount() - 1, 1)->text().toInt();
		storage->removeRow(storage->rowCount() - 1);
		update_commit_btn();
	}
}

void in_recorder::on_commit_clicked()
{
	if (medicines::commit_inr(inr, storage->model()).isValid()) {
		QMessageBox::critical(this, "错误", "入库失败", QMessageBox::Yes);
	} else {
		ui->commit->setEnabled(false);
		ui->abort->setEnabled(false);
		ui->insert->setEnabled(false);
		ui->rollback->setEnabled(false);
		emit commited();
		QMessageBox::information(this, "提示", "入库成功", QMessageBox::Yes);
	}
}

void in_recorder::on_abort_clicked()
{
	if (medicines::abort_inr(inr).isValid()) {
		QMessageBox::critical(this, "错误", "请求失败", QMessageBox::Yes);
	} else {
		ui->commit->setEnabled(false);
		ui->abort->setEnabled(false);
		ui->insert->setEnabled(false);
		ui->rollback->setEnabled(false);
		emit commited();
		QMessageBox::information(this, "提示", "已拒绝", QMessageBox::Yes);
	}
}
