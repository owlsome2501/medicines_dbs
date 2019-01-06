#include "in_recorder.h"
#include "ui_in_recorder.h"

in_recorder::in_recorder(QWidget *parent)
	: QWidget(parent), ui(new Ui::in_recorder)
{
	ui->setupUi(this);
	date = QDate::currentDate();
	ui->date->setText(date.toString("yyyy.MM.dd"));
	ui->staff->setText(staff_mngr::getName());
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
