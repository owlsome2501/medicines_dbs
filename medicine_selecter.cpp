#include "medicine_selecter.h"
#include "ui_medicine_selecter.h"

medicine_selecter::medicine_selecter(QWidget *parent)
	: QDialog(parent), ui(new Ui::medicine_selecter), model(nullptr)
{
	ui->setupUi(this);
	connect(ui->results, &QTableView::doubleClicked, this,
			&medicine_selecter::confirm);
}

medicine_selecter::~medicine_selecter()
{
	delete ui;
	if (model)
		model->deleteLater();
}
void medicine_selecter::keyPressEvent(QKeyEvent *evt)
{
	if (evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return)
		return;
	else
		QDialog::keyPressEvent(evt);
}

void medicine_selecter::on_search_clicked()
{
	QSqlQueryModel *m = medicines::search_medichine(
		ui->mid->text(), ui->ap_name->text(), ui->ap_num->text());
	if (m) {
		if (model)
			model->deleteLater();
		model = m;
		ui->results->setModel(model);
	}
	ui->results->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void medicine_selecter::confirm(const QModelIndex &index)
{
	qDebug() << "double index: " << index;
	mid = model->index(index.row(), 0).data().toString();
	ap_name = model->index(index.row(), 1).data().toString();
	accept();
}

QString medicine_selecter::getAp_name() const { return ap_name; }

QString medicine_selecter::getMid() const { return mid; }
