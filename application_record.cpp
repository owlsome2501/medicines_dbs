#include "application_record.h"
#include "ui_application_record.h"

application_record::application_record(QWidget *parent)
	: QWidget(parent), ui(new Ui::application_record)
{
	ui->setupUi(this);
	date = QDate::currentDate();
	ui->date->setText(date.toString("yyyy.MM.dd"));
	ui->staff->setText(staff_mngr::getName());

	ui->num->setValidator(new QIntValidator(1, 10000, this));
}

application_record::~application_record() { delete ui; }

void application_record::on_select_mid_clicked()
{
	medicine_selecter mselecter(this);
	if (mselecter.exec() == QDialog::Accepted) {
		ui->mid->setText(mselecter.getMid());
		ui->ap_name->setText(mselecter.getAp_name());
	}
	mselecter.deleteLater();
}

void application_record::on_commit_clicked()
{
	if (ui->mid->text().length() > 0 && ui->num->text().length() > 0 &&
		ui->destination->text().length() > 0) {
		if (medicines::add_apr(ui->mid->text(), ui->num->text().toInt(), date,
							   ui->destination->text(), staff_mngr::getId())
				.isValid()) {
			QMessageBox::critical(this, "错误", "添加失败", QMessageBox::Yes);
		} else {
			ui->commit->setEnabled(false);
			QMessageBox::information(this, "提示", "添加成功",
									 QMessageBox::Yes);
		}
	}
}
