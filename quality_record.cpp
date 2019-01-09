#include "quality_record.h"
#include "ui_quality_record.h"

quality_record::quality_record(int _type, int _io_id, QWidget *parent)
	: QWidget(parent), ui(new Ui::quality_record), type(_type), io_id(_io_id)
{
	date = QDate::currentDate();
	ui->setupUi(this);
	ui->io_id->setText(QString::number(io_id));
	ui->staff->setText(staff_mngr::getName());
	ui->date->setText(date.toString("yyyy/M/d"));
	QSqlQueryModel *model = medicines::get_io_info_for_qc(type, io_id);
	qDebug() << "io_info count: " << model->rowCount();
	if (model && model->rowCount() == 1) {
		QSqlRecord rec = model->record(0);
		ui->mid->setText(rec.value("mid").toString());
		ui->ap_name->setText(rec.value("approval_name_zh").toString());
		ui->batch_num->setText(rec.value("batch_num").toString());
		model->deleteLater();
	}
}

quality_record::~quality_record() { delete ui; }

void quality_record::on_commit_clicked()
{
	int quality = 0;
	if (ui->quality->currentText() == "合格")
		quality = 0;
	else
		quality = 1;
	if (medicines::add_qur(type, io_id, quality, ui->detail->toPlainText(),
						   staff_mngr::getId(), date)
			.isValid()) {
		QMessageBox::critical(this, "错误", "提交失败", QMessageBox::Yes);
	} else {
		ui->commit->setEnabled(false);
		emit commited();
		QMessageBox::information(this, "提示", "提交成功", QMessageBox::Yes);
	}
}
