#include "out_recorder.h"
#include "ui_out_recorder.h"

out_recorder::out_recorder(QWidget *parent, int _otr)
	: QWidget(parent), otr(_otr), ui(new Ui::out_recorder)
{
	ui->setupUi(this);
}

out_recorder::~out_recorder() { delete ui; }
