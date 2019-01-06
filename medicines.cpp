#include "medicines.h"

medicines::medicines() {}

QSqlQueryModel *medicines::get_overview_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery("select mid,approval_name_zh, basic_num from medicine");
		model->setHeaderData(0, Qt::Horizontal, "药品本位码");
		model->setHeaderData(1, Qt::Horizontal, "产品名");
		model->setHeaderData(2, Qt::Horizontal, "基础库存量");
		return model;
	}
	return nullptr;
}

QSqlQueryModel *medicines::get_analysis_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery("select mid,approval_name_zh, basic_num from medicine");
		model->setHeaderData(0, Qt::Horizontal, "药品本位码");
		model->setHeaderData(1, Qt::Horizontal, "产品名");
		model->setHeaderData(2, Qt::Horizontal, "基础库存量");
		return model;
	}
	return nullptr;
}

QSqlQueryModel *medicines::search_medichine(QString mid, QString ap_name,
											QString ap_num)
{
	if (database_mngr::get_connection().isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		QString sql =
			QString(
				"select "
				"mid, approval_name_zh, product_name_zh, approval_num "
				"from medicine "
				"where "
				"mid like '%%1%' and "
				"approval_name_zh like '%%2%' and  "
				"approval_num like '%%3%'")
				.arg(mid, ap_name, ap_num);
		qDebug() << sql;
		model->setQuery(sql);
		model->setHeaderData(0, Qt::Horizontal, "药品本位码");
		model->setHeaderData(1, Qt::Horizontal, "产品名");
		model->setHeaderData(2, Qt::Horizontal, "商品名");
		model->setHeaderData(3, Qt::Horizontal, "批准文号");
		return model;
	}
	return nullptr;
	/*
	if (database_mngr::get_connection().isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		QString sql =
			"select "
			"mid, approval_name_zh, product_name_zh, approval_num "
			"from medicine "
			"where "
			"mid like ? and approval_name_zh like ? and  approval_num like ?";
		QSqlQuery query;
		query.prepare(sql);
		query.addBindValue(mid);
		query.addBindValue(ap_name);
		query.addBindValue(ap_num);
		query.exec();
		if (query.lastError().isValid()) {
			qDebug() << "search medicine error";
		} else {
			model->setQuery(query);
			model->setHeaderData(0, Qt::Horizontal, "药品本位码");
			model->setHeaderData(1, Qt::Horizontal, "产品名");
			model->setHeaderData(2, Qt::Horizontal, "商品名");
			model->setHeaderData(3, Qt::Horizontal, "批准文号");
			return model;
		}
	}
	return nullptr;
	*/
}


QSqlError medicines::add_pur(QString mid, int num, double price,
							 QString supplier, QDate date, int staff)
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQuery query;
		query.prepare(
			"insert into purchase_record( "
			"num, date, wholesale_price, supplier, staff, mid, state) "
			"values( "
			"?, ?, ?, ?, ?, ?, ?)");
		query.addBindValue(num);
		query.addBindValue(date);
		query.addBindValue(price);
		query.addBindValue(supplier);
		query.addBindValue(staff);
		query.addBindValue(mid);
		query.addBindValue(0);
		query.exec();
		return query.lastError();
	}
	return db.lastError();
}
QSqlQueryModel *medicines::get_pur_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery(
			"select p.id as pur_id, m.mid as mid, "
			"m.approval_name_zh as ap_name, "
			"p.num as num "
			"from purchase_record as p,medicine as m "
			"where p.mid = m.mid and p.state = 0");
		model->setHeaderData(0, Qt::Horizontal, "采购单号");
		model->setHeaderData(1, Qt::Horizontal, "药品本位码");
		model->setHeaderData(2, Qt::Horizontal, "产品名");
		model->setHeaderData(3, Qt::Horizontal, "数量");
		if (model->lastError().isValid())
			return nullptr;
		qDebug() << "pur_model get";
		return model;
	}
	return nullptr;
}
