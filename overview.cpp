#include "overview.h"
#include "ui_overview.h"

overview::overview(QWidget *parent) : QWidget(parent), ui(new Ui::overview)
{
	ui->setupUi(this);
	QSqlQueryModel *table_model = medicines::get_overview_model();
	if (table_model) {
		ui->table->setModel(table_model);
		ui->table->horizontalHeader()->setSectionResizeMode(
			QHeaderView::ResizeToContents);
	} else
		QMessageBox::warning(this, "错误", "获取列表失败", QMessageBox::Yes);
}

overview::~overview() { delete ui; }
