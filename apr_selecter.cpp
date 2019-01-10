#include "apr_selecter.h"
#include "ui_apr_selecter.h"

apr_selecter::apr_selecter(QWidget *parent)
	: QDialog(parent), ui(new Ui::apr_selecter)
{
	ui->setupUi(this);
	model = medicines::get_apr_model();
	if (!model)
		QMessageBox::critical(this, "错误", "选择失败", QMessageBox::Yes);
	ui->results->setModel(model);
	ui->results->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(ui->results, &QTableView::doubleClicked, this,
			&apr_selecter::confirm);
}

apr_selecter::~apr_selecter()
{
	delete ui;
	if (model)
		model->deleteLater();
}

int apr_selecter::getApr_id() const { return apr_id; }

QString apr_selecter::getMid() const { return mid; }

QString apr_selecter::getAp_name() const { return ap_name; }

int apr_selecter::getAll_num() const { return all_num; }

void apr_selecter::confirm(const QModelIndex &index)
{
	apr_id = model->index(index.row(), 0).data().toInt();
	mid = model->index(index.row(), 1).data().toString();
	ap_name = model->index(index.row(), 2).data().toString();
	all_num = model->index(index.row(), 3).data().toInt();
	goted = model->index(index.row(), 4).data().toInt();
	all_inv_num = model->index(index.row(), 5).data().toInt();
	accept();
}

int apr_selecter::getAll_inv_num() const { return all_inv_num; }

int apr_selecter::getGoted() const { return goted; }
