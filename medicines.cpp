#include "medicines.h"

medicines::medicines() {}

QSqlQueryModel *medicines::get_overview_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery("select * from overview");
		model->setHeaderData(0, Qt::Horizontal, "药品本位码");
		model->setHeaderData(1, Qt::Horizontal, "批准文号");
		model->setHeaderData(2, Qt::Horizontal, "总量");
		model->setHeaderData(3, Qt::Horizontal, "基础数量");
		model->setHeaderData(4, Qt::Horizontal, "产品名");
		model->setHeaderData(5, Qt::Horizontal, "产品名(eng)");
		model->setHeaderData(6, Qt::Horizontal, "商品名");
		model->setHeaderData(7, Qt::Horizontal, "商品名(eng)");
		model->setHeaderData(8, Qt::Horizontal, "处方类型");
		model->setHeaderData(9, Qt::Horizontal, "规格");
		model->setHeaderData(10, Qt::Horizontal, "零售价");
		model->setHeaderData(11, Qt::Horizontal, "储存要求");
		model->setHeaderData(12, Qt::Horizontal, "生产厂商");
		model->setHeaderData(13, Qt::Horizontal, "保质期");
		return model;
	}
	return nullptr;
}

QSqlQueryModel *medicines::get_analysis_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		int range = 14;
		QString sql =
			"select "
			"o.mid,medicine.approval_name_zh, "
			"o.speed,inv.num, floor(inv.num/o.speed) as remine_day "
			"from "
			"( "
			"select out_record.mid ,(sum(out_record.num))/%1 as speed "
			"from out_record "
			"where datediff(curdate(),date) <= %1 "
			"group by out_record.mid "
			") as o "
			"join "
			"( "
			"select inventory.mid,(sum(all_num)) as num "
			"from inventory "
			"group by inventory.mid "
			") as inv "
			"on o.mid = inv.mid "
			"join medicine "
			"on o.mid = medicine.mid "
			"order by remine_day ";
		model->setQuery(sql.arg(range));
		model->setHeaderData(0, Qt::Horizontal, "药品本位码");
		model->setHeaderData(1, Qt::Horizontal, "产品名");
		model->setHeaderData(2, Qt::Horizontal,
							 QString::number(range) + "天消耗速度");
		model->setHeaderData(3, Qt::Horizontal, "剩余总量");
		model->setHeaderData(4, Qt::Horizontal, "预估剩余时间");
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
		model->setQuery("select * from pur_wait");
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

QSqlQueryModel *medicines::get_io_wait_mngr_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery("select * from io_wait_mngr");
		model->setHeaderData(0, Qt::Horizontal, "类型");
		model->setHeaderData(1, Qt::Horizontal, "单号");
		model->setHeaderData(2, Qt::Horizontal, "状态");
		model->setHeaderData(3, Qt::Horizontal, "药品本位码");
		model->setHeaderData(4, Qt::Horizontal, "日期");
		if (model->lastError().isValid())
			return nullptr;
		qDebug() << "io_wait_mngr_model get";
		return model;
	}
	return nullptr;
}

QSqlError medicines::add_inr(QString mid, int batch_num, int num, QDate date,
							 int staff, int pur_id)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		QSqlQuery query;
		query.prepare(
			"insert into in_record ( "
			"state, mid, batch_num, num, date, staff, purchase_record "
			") values(?, ?, ?, ?, ?, ?, ?)");
		query.addBindValue(0);
		query.addBindValue(mid);
		query.addBindValue(batch_num);
		query.addBindValue(num);
		query.addBindValue(date);
		query.addBindValue(staff);
		query.addBindValue(pur_id);
		query.exec();
		err = query.lastError();
	} else {
		err = db.lastError();
	}
	if (err.isValid()) {
		qDebug() << err;
	}
	return err;
}
