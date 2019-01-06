#include "medicines.h"

medicines::medicines() {}

QSqlQueryModel *medicines::get_overview_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlTableModel;
		model->setQuery("select mid,approval_name_zh, basic_num from medicine");
		model->setHeaderData(0, Qt::Horizontal, "药品本位码");
		model->setHeaderData(1, Qt::Horizontal, "产品名称");
		model->setHeaderData(2, Qt::Horizontal, "基础库存量");
		return model;
	} else
		return nullptr;
}
