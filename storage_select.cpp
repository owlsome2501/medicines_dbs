#include "storage_select.h"
#include "ui_storage_select.h"

storage_select::storage_select(QString _mid, QString _batch_num,
							   QWidget *parent)
	: QDialog(parent), ui(new Ui::storage_select), mid(_mid),
	  batch_num(_batch_num)
{
	ui->setupUi(this);
	model = medicines::searh_storage(mid, batch_num);
	if (!model)
		QMessageBox::critical(this, "错误", "选择失败", QMessageBox::Yes);
	ui->results->setModel(model);
	ui->results->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(ui->results, &QTableView::doubleClicked, this,
			&storage_select::confirm);
}

storage_select::~storage_select()
{
	delete ui;
	if (model)
		model->deleteLater();
}

void storage_select::confirm(const QModelIndex &index)
{
	wid = model->index(index.row(), 0).data().toInt();
	num = model->index(index.row(), 1).data().toInt();
	accept();
}

int storage_select::getNum() const { return num; }

int storage_select::getWid() const { return wid; }
