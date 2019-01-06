#include "purchase_record.h"
#include "ui_purchase_record.h"

purchase_record::purchase_record(QWidget *parent)
	: QWidget(parent), ui(new Ui::purchase_record)
{
	ui->setupUi(this);
}

purchase_record::~purchase_record() { delete ui; }

void purchase_record::on_select_mid_clicked() {}
