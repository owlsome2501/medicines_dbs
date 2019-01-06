#include "analysis.h"
#include "ui_analysis.h"

analysis::analysis(QWidget *parent) : QWidget(parent), ui(new Ui::analysis)
{
	ui->setupUi(this);
	QSqlQueryModel *table_model = medicines::get_analysis_model();
	if (table_model) {
		ui->table->setModel(table_model);
		ui->table->horizontalHeader()->setSectionResizeMode(
			QHeaderView::Stretch);
	} else
		QMessageBox::warning(this, "错误", "获取列表失败", QMessageBox::Yes);
}

analysis::~analysis() { delete ui; }
