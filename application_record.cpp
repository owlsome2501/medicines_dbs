#include "application_record.h"
#include "ui_application_record.h"

application_record::application_record(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::application_record)
{
	ui->setupUi(this);
}

application_record::~application_record()
{
	delete ui;
}
