#include "pur_selecter.h"
#include "ui_pur_selecter.h"

pur_selecter::pur_selecter(QWidget *parent)
	: QDialog(parent), ui(new Ui::pur_selecter)
{
	ui->setupUi(this);
	model = medicines::get_pur_model();
	if (!model)
		QMessageBox::critical(this, "错误", "添加失败", QMessageBox::Yes);
	ui->results->setModel(model);
	ui->results->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(ui->results, &QTableView::doubleClicked, this,
			&pur_selecter::confirm);
}

pur_selecter::~pur_selecter()
{
	delete ui;
	if (model)
		model->deleteLater();
}

int pur_selecter::getPur_id() const { return pur_id; }

void pur_selecter::confirm(const QModelIndex &index)
{
	pur_id = model->index(index.row(), 0).data().toInt();
	mid = model->index(index.row(), 1).data().toString();
	ap_name = model->index(index.row(), 2).data().toString();
	accept();
}

QString pur_selecter::getAp_name() const { return ap_name; }

QString pur_selecter::getMid() const { return mid; }
