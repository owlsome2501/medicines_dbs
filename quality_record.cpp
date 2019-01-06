#include "quality_record.h"
#include "ui_quality_record.h"

quality_record::quality_record(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::quality_record)
{
	ui->setupUi(this);
}

quality_record::~quality_record()
{
	delete ui;
}
