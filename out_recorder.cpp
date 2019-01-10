#include "out_recorder.h"
#include "ui_out_recorder.h"

out_recorder::out_recorder(QWidget *parent, int _otr)
	: QWidget(parent), otr(_otr), ui(new Ui::out_recorder), num_limit(0),
	  num_out_sum(0)
{
	ui->setupUi(this);
	date = QDate::currentDate();
	out_list = ui->out_list;

	ui->date->setText(date.toString("yyyy/M/d"));
	ui->staff->setText(staff_mngr::getName());
	QIntValidator *iv = new QIntValidator(1, 10000, this);
	ui->num->setValidator(iv);
	ui->all_num->setValidator(iv);
	ui->detail->setVisible(false);
	if (otr != -1) {
		ui->all_num->setReadOnly(true);

		ui->select_apr->setVisible(false);
		ui->select_inv->setVisible(false);
		ui->req_qur->setVisible(false);

		ui->all_inv_num->setVisible(false);
		ui->label_all_inv_num->setVisible(false);
		ui->inv_num->setVisible(false);
		ui->label_inv_num->setVisible(false);

		QSqlQueryModel *model = medicines::get_otr_info(otr);
		if (model && model->rowCount() == 1) {
			QSqlRecord rec = model->record(0);
			int state = rec.value(0).toInt();
			qDebug() << "inr state: " << state;
			ui->apr_id->setText(QString::number(rec.value(1).toInt()));
			ui->mid->setText(rec.value(2).toString());
			ui->ap_name->setText(rec.value(3).toString());
			ui->apr_num->setText(QString::number(rec.value(4).toInt()));
			ui->goted->setText(QString::number(rec.value(5).toInt()));
			ui->batch_num->setText(rec.value(6).toString());
			ui->all_num->setText(QString::number(rec.value(7).toInt()));
			ui->date->setText(rec.value(8).toDate().toString("yyyy/M/d"));
			ui->staff->setText(rec.value(9).toString());
			int qur_id_tmp = rec.value(10).toInt();
			ui->quality->setText(rec.value(11).toString());
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

out_recorder::~out_recorder() { delete ui; }

void out_recorder::on_select_apr_clicked()
{
	apr_selecter aselecter(this);
	if (aselecter.exec() == QDialog::Accepted) {
		qDebug() << "aselecter acc";
		ui->apr_id->setText(QString::number(aselecter.getApr_id()));
		ui->apr_num->setText(QString::number(aselecter.getAll_num()));
		ui->mid->setText(aselecter.getMid());
		ui->ap_name->setText(aselecter.getAp_name());
		ui->goted->setText(QString::number(aselecter.getGoted()));
		ui->all_inv_num->setText(QString::number(aselecter.getAll_inv_num()));

		ui->select_inv->setEnabled(true);
	}
	aselecter.deleteLater();
}

void out_recorder::on_select_inv_clicked()
{
	if (ui->mid->text().length() > 0) {
		inv_selecter iselecter(ui->mid->text(), this);
		if (iselecter.exec() == QDialog::Accepted) {
			qDebug() << "aselecter acc";
			ui->batch_num->setText(iselecter.getBatch_num());
			ui->inv_num->setText(QString::number(iselecter.getNum()));

			ui->req_qur->setEnabled(true);
		}
		iselecter.deleteLater();
	}
}

void out_recorder::on_select_storage_clicked()
{
	if (ui->mid->text().length() > 0 && ui->batch_num->text().length() > 0) {
		storage_select sselecter(ui->mid->text(), ui->batch_num->text(), this);
		if (sselecter.exec() == QDialog::Accepted) {
			qDebug() << "aselecter acc";
			ui->wid->setText(QString::number(sselecter.getWid()));
			num_limit = sselecter.getNum();
		}
		sselecter.deleteLater();
	}
}


void out_recorder::update_commit_btn()
{
	if (ui->all_num->text().toInt() == num_out_sum)
		ui->commit->setEnabled(true);
	else
		ui->commit->setEnabled(false);
}

void out_recorder::on_insert_clicked()
{
	if (ui->wid->text().length() > 0 && ui->num->text().length() > 0) {
		int wid = ui->wid->text().toInt();
		int num = ui->num->text().toInt();
		if (num > num_limit) {
			qDebug() << "num limit: " << num_limit;
			QMessageBox::warning(this, "警告", "申请数值过大",
								 QMessageBox::Yes);
		} else if (num > 0) {
			bool dup = false;
			auto model = out_list->model();
			for (int i = 0; i != model->rowCount(); ++i) {
				int wid_t = model->data(model->index(i, 0)).toInt();
				if (wid == wid_t) {
					dup = true;
					break;
				}
			}
			if (dup) {
				QMessageBox::warning(this, "警告", "已使用过本货架",
									 QMessageBox::Yes);
			} else {
				int row_length = out_list->rowCount();
				out_list->insertRow(row_length);
				out_list->setItem(row_length, 0,
								  new QTableWidgetItem(QString::number(wid)));
				out_list->setItem(row_length, 1,
								  new QTableWidgetItem(QString::number(num)));
				ui->wid->clear();
				ui->num->clear();
				num_out_sum += num;
				update_commit_btn();
			}
		}
	}
}

void out_recorder::on_rollback_clicked()
{
	if (out_list->rowCount() > 0) {
		num_out_sum -=
			out_list->item(out_list->rowCount() - 1, 1)->text().toInt();
		out_list->removeRow(out_list->rowCount() - 1);
		update_commit_btn();
	}
}

void out_recorder::on_req_qur_clicked()
{
	if (ui->mid->text().length() > 0 && ui->batch_num->text().length() > 0 &&
		ui->all_num->text().length() > 0) {
		int num = ui->all_num->text().toInt();
		int apr_num = ui->apr_num->text().toInt();
		int goted = ui->goted->text().toInt();
		if (num + goted > apr_num) {
			QMessageBox::warning(this, "警告", "出库数量超过请求",
								 QMessageBox::Yes);
			return;
		}
		if (medicines::add_otr(ui->mid->text(), ui->batch_num->text(), num,
							   date, staff_mngr::getId(),
							   ui->apr_id->text().toInt())
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

void out_recorder::on_commit_clicked()
{
	if (medicines::commit_otr(otr, out_list->model()).isValid()) {
		QMessageBox::critical(this, "错误", "出库失败", QMessageBox::Yes);
	} else {
		ui->commit->setEnabled(false);
		ui->abort->setEnabled(false);
		ui->insert->setEnabled(false);
		ui->rollback->setEnabled(false);
		ui->select_storage->setEnabled(false);
		emit commited();
		QMessageBox::information(this, "提示", "出库成功", QMessageBox::Yes);
	}
}

void out_recorder::on_abort_clicked()
{
	if (medicines::abort_otr(otr).isValid()) {
		QMessageBox::critical(this, "错误", "请求失败", QMessageBox::Yes);
	} else {
		ui->commit->setEnabled(false);
		ui->abort->setEnabled(false);
		ui->insert->setEnabled(false);
		ui->rollback->setEnabled(false);
		ui->select_storage->setEnabled(false);
		emit commited();
		QMessageBox::information(this, "提示", "已拒绝", QMessageBox::Yes);
	}
}
