#include "inv_selecter.h"
#include "ui_inv_selecter.h"

inv_selecter::inv_selecter(QString _mid, QWidget *parent)
	: QDialog(parent), ui(new Ui::inv_selecter), mid(_mid)
{
	ui->setupUi(this);
	model = medicines::searh_inv(mid);
	if (!model)
		QMessageBox::critical(this, "错误", "选择失败", QMessageBox::Yes);
	ui->results->setModel(model);
	ui->results->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(ui->results, &QTableView::doubleClicked, this,
			&inv_selecter::confirm);
}

inv_selecter::~inv_selecter()
{
	delete ui;
	if (model)
		model->deleteLater();
}

QString inv_selecter::getBatch_num() const { return batch_num; }

int inv_selecter::getNum() const { return num; }

void inv_selecter::confirm(const QModelIndex &index)
{
	batch_num = model->index(index.row(), 0).data().toString();
	num = model->index(index.row(), 1).data().toInt();
	accept();
}
