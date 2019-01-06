#include "medicine_selecter.h"
#include "ui_medicine_selecter.h"

medicine_selecter::medicine_selecter(QWidget *parent)
	: QDialog(parent), ui(new Ui::medicine_selecter)
{
	ui->setupUi(this);
}

medicine_selecter::~medicine_selecter() { delete ui; }
void medicine_selecter::keyPressEvent(QKeyEvent *evt)
{
	if (evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return)
		return;
	else
		QDialog::keyPressEvent(evt);
}
