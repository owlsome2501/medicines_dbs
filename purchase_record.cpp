#include "purchase_record.h"
#include "ui_purchase_record.h"

purchase_record::purchase_record(QWidget *parent)
	: QWidget(parent), ui(new Ui::purchase_record)
{
	ui->setupUi(this);
	date = QDate::currentDate();
	ui->date->setText(date.toString("yyyy.MM.dd"));
	ui->staff->setText(staff_mngr::getName());

	ui->num->setValidator(new QIntValidator(this));
	ui->price->setValidator(new QDoubleValidator(this));
}

purchase_record::~purchase_record() { delete ui; }

void purchase_record::on_select_mid_clicked()
{
	medicine_selecter mselecter(this);
	if (mselecter.exec() == QDialog::Accepted) {
		ui->mid->setText(mselecter.getMid());
		ui->ap_name->setText(mselecter.getAp_name());
	}
}

void purchase_record::on_commit_clicked()
{
	if (ui->mid->text().length() > 0 && ui->num->text().length() > 0 &&
		ui->price->text().length() > 0 && ui->supplier->text().length() > 0) {
		int num = ui->num->text().toInt();
		double price = ui->price->text().toDouble();
		if (!medicines::add_pur(ui->mid->text(), num, price,
								ui->supplier->text(), date, staff_mngr::getId())
				 .isValid())
			QMessageBox::information(this, "提示", "添加成功",
									 QMessageBox::Yes);
		else
			QMessageBox::critical(this, "错误", "添加失败", QMessageBox::Yes);
	}
}
