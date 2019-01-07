#include "in_recorder.h"
#include "ui_in_recorder.h"

in_recorder::in_recorder(QWidget *parent, int _inr)
	: QWidget(parent), ui(new Ui::in_recorder), inr(_inr)
{
	ui->setupUi(this);
	date = QDate::currentDate();
	ui->date->setText(date.toString("yyyy/M/d"));
	ui->staff->setText(staff_mngr::getName());
	QIntValidator *iv = new QIntValidator(this);
	ui->all_num->setValidator(iv);
	ui->num->setValidator(iv);
	ui->wid->setValidator(iv);

	if (inr == -1) {
		ui->detail->setVisible(false);
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
	}
}

void in_recorder::on_req_qur_clicked()
{
	if (ui->mid->text().length() > 0 && ui->batch_num->text().length() > 0 &&
		ui->all_num->text().length() > 0 &&
		ui->production_date->text().length() > 0) {
		if (medicines::add_inr(ui->mid->text(), ui->batch_num->text().toInt(),
							   ui->num->text().toInt(), date,
							   staff_mngr::getId(), ui->pur_id->text().toInt())
				.isValid()) {
			QMessageBox::critical(this, "错误", "申请失败", QMessageBox::Yes);
		} else
			QMessageBox::information(this, "提示", "申请成功, 已暂存",
									 QMessageBox::Yes);
	}
}
