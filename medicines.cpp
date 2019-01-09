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

QSqlError medicines::add_inr(QString mid, int batch_num, int all_num,
							 QDate date, int staff, int pur_id,
							 QDate production_date)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		//若库存记录不存在则插入库存记录
		query.prepare(
			"insert into inventory (mid, batch_num, all_num, production_date) "
			"select * from (select ?,?,?,?) as tmp "
			"where not exists( "
			"select mid from inventory "
			"where mid=? and batch_num=?"
			")limit 1");
		query.addBindValue(mid);
		query.addBindValue(batch_num);
		query.addBindValue(0);
		query.addBindValue(production_date);
		query.addBindValue(mid);
		query.addBindValue(batch_num);
		query.exec();
		//插入入库记录
		query.prepare(
			"insert into in_record ( "
			"state, mid, batch_num, num, date, staff, purchase_record "
			") values(?, ?, ?, ?, ?, ?, ?)");
		query.addBindValue(0);
		query.addBindValue(mid);
		query.addBindValue(batch_num);
		query.addBindValue(all_num);
		query.addBindValue(date);
		query.addBindValue(staff);
		query.addBindValue(pur_id);
		query.exec();
		//更新采购记录状态
		query.prepare("update purchase_record set state=1 where id = ?");
		query.addBindValue(pur_id);
		query.exec();
		err = query.lastError();
		if (err.isValid())
			db.rollback();
		else
			db.commit();
	} else {
		err = db.lastError();
	}
	if (err.isValid()) {
		qDebug() << err;
	}
	return err;
}

QSqlQueryModel *medicines::get_qc_wait_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery("select * from qc_wait");
		model->setHeaderData(0, Qt::Horizontal, "类型");
		model->setHeaderData(1, Qt::Horizontal, "单号");
		model->setHeaderData(2, Qt::Horizontal, "药品本位码");
		model->setHeaderData(3, Qt::Horizontal, "日期");
		if (model->lastError().isValid())
			return nullptr;
		qDebug() << "qc_wait_model get";
		return model;
	}
	return nullptr;
}

QSqlQueryModel *medicines::get_io_info_for_qc(int type, int id)
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		if (type == 0) {
			model->setQuery(
				QString("select in_record.mid, batch_num , approval_name_zh "
						"from in_record ,medicine "
						"where in_record.mid = medicine.mid  "
						"and in_record.id = %1")
					.arg(id));
		} else {
			model->setQuery(
				QString("select out_record.mid, batch_num , approval_name_zh "
						"from out_record ,medicoute "
						"where out_record.mid = medicoute.mid "
						"and out_record.id = %1")
					.arg(id));
		}
		if (model->lastError().isValid())
			return nullptr;
		qDebug() << "io_info get";
		return model;
	}
	return nullptr;
}

QSqlError medicines::add_qur(int type, int io_id, int quality, QString detail,
							 int staff, QDate date)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		query.prepare(
			"insert into quality_record "
			"( quality, details, staff, date) "
			"values(?, ?, ?, ?)");
		query.addBindValue(quality);
		query.addBindValue(detail);
		query.addBindValue(staff);
		query.addBindValue(date);
		query.exec();
		if (type == 0) {
			query.prepare(
				"update in_record set state=1, quality_record=last_insert_id() "
				"where id = ?");
			query.addBindValue(io_id);
		} else {
			query.prepare(
				"update out_record set state=1, "
				"quality_record=last_insert_id() "
				"where id = ?");
			query.addBindValue(io_id);
		}
		query.exec();
		err = query.lastError();
		if (err.isValid())
			db.rollback();
		else
			db.commit();
	} else {
		err = db.lastError();
	}
	if (err.isValid()) {
		qDebug() << err;
	}
	return err;
}

QSqlQueryModel *medicines::get_inr_info(int id)
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery(
			QString("select "
					"in_record.state, "
					"in_record.mid, "
					"in_record.batch_num, "
					"in_record.num, "
					"in_record.date, "
					"staff.name, "
					"in_record.quality_record, "
					"in_record.purchase_record, "
					"inventory.production_date, "
					"case "
					"when quality_record.quality = 0 then '合格' "
					"when quality_record.quality = 1 then '不合格' "
					"else '' "
					"end as quality,"
					"medicine.approval_name_zh "
					"from inventory,medicine, staff, "
					"in_record left join quality_record "
					"on in_record.quality_record = quality_record.id "
					"where in_record.id = %1 and "
					"in_record.mid = inventory.mid and "
					"in_record.batch_num = inventory.batch_num and "
					"in_record.mid = medicine.mid and "
					"in_record.staff = staff.id")
				.arg(id));
		if (model->lastError().isValid()) {
			qDebug() << model->lastError();
			return nullptr;
		}
		qDebug() << "io_info get";
		return model;
	}
	return nullptr;
}

QSqlError medicines::commit_inr(int id, QAbstractItemModel *model)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		query.prepare(
			"update in_record, purchase_record, inventory "
			"set in_record.state = 2, purchase_record.state = 2, "
			"inventory.all_num = inventory.all_num + in_record.num "
			"where in_record.purchase_record = purchase_record.id and "
			"in_record.mid = inventory.mid and "
			"in_record.batch_num = inventory.batch_num and "
			"in_record.id = ?");
		query.addBindValue(id);
		query.exec();
		for (int i = 0; i != model->rowCount(); ++i) {
			int wid = model->data(model->index(i, 0)).toInt();
			int num = model->data(model->index(i, 1)).toInt();
			query.prepare(
				"insert into storage (mid, batch_num, wid, num) "
				"select mid, batch_num,?,? from in_record "
				"where id = ? "
				"on duplicate key update storage.num=storage.num+?");
			query.addBindValue(wid);
			query.addBindValue(num);
			query.addBindValue(id);
			query.addBindValue(num);
			query.exec();
		}
		err = query.lastError();
		if (err.isValid())
			db.rollback();
		else
			db.commit();
	} else {
		err = db.lastError();
	}
	if (err.isValid()) {
		qDebug() << err;
	}
	return err;
}


QSqlError medicines::abort_inr(int id)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		query.prepare(
			"update in_record, purchase_record "
			"set in_record.state = 3, purchase_record.state = 3 "
			"where in_record.purchase_record = purchase_record.id and "
			"in_record.id = ?");
		query.addBindValue(id);
		query.exec();
		err = query.lastError();
		if (err.isValid())
			db.rollback();
		else
			db.commit();
	} else {
		err = db.lastError();
	}
	if (err.isValid()) {
		qDebug() << err;
	}
	return err;
}
