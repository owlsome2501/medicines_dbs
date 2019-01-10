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
		model->setHeaderData(3, Qt::Horizontal, "总数量");
		model->setHeaderData(4, Qt::Horizontal, "已入库数量");
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

QSqlError medicines::add_inr(QString mid, QString batch_num, int all_num,
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
		err = query.lastError();
		if (err.isValid()) {
			db.rollback();
			return err;
		}
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
		err = query.lastError();
		if (err.isValid()) {
			db.rollback();
			return err;
		}
		//更新采购记录状态
		query.prepare(
			"update purchase_record set goted = goted + ?, "
			"state = case when num = goted then 1 else 0 end "
			"where id = ?");
		query.addBindValue(all_num);
		query.addBindValue(pur_id);
		query.exec();
		err = query.lastError();
		if (err.isValid()) {
			db.rollback();
			return err;
		}
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
						"from out_record ,medicine "
						"where out_record.mid = medicine.mid "
						"and out_record.id = %1")
					.arg(id));
		}
		if (model->lastError().isValid()) {
			qDebug() << model->lastError();
			return nullptr;
		}
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
		err = query.lastError();
		if (err.isValid()) {
			db.rollback();
			return err;
		}
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
					"end as quality, "
					"medicine.approval_name_zh, "
					"purchase_record.num, "
					"purchase_record.goted "
					"from inventory,medicine, staff, purchase_record, "
					"in_record left join quality_record "
					"on in_record.quality_record = quality_record.id "
					"where in_record.id = %1 and "
					"in_record.mid = inventory.mid and "
					"in_record.batch_num = inventory.batch_num and "
					"in_record.mid = medicine.mid and "
					"in_record.staff = staff.id and "
					"in_record.purchase_record = purchase_record.id")
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
			"set in_record.state = 2, "
			"inventory.all_num = inventory.all_num + in_record.num, "
			"purchase_record.came = purchase_record.came + in_record.num, "
			"purchase_record.state = "
			"case "
			"when purchase_record.came + in_record.num =  purchase_record.num "
			"then 2 "
			"else purchase_record.state "
			"end "
			"where in_record.purchase_record = purchase_record.id and "
			"in_record.mid = inventory.mid and "
			"in_record.batch_num = inventory.batch_num and "
			"in_record.id = ?");
		query.addBindValue(id);
		query.exec();
		err = query.lastError();
		if (err.isValid()) {
			db.rollback();
			return err;
		}
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
			"set in_record.state = 3, purchase_record.state = 0, "
			"purchase_record.goted = purchase_record.goted - in_record.num "
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

QSqlError medicines::add_apr(QString mid, int num, QDate date,
							 QString destination, int staff)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		query.prepare(
			"insert into application_record "
			"( mid, num, date, destination, staff, state) "
			"values(?, ?, ?, ?, ?, ?)");
		query.addBindValue(mid);
		query.addBindValue(num);
		query.addBindValue(date);
		query.addBindValue(destination);
		query.addBindValue(staff);
		query.addBindValue(0);
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

QSqlQueryModel *medicines::get_apr_model()
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery("select * from apr_wait");
		model->setHeaderData(0, Qt::Horizontal, "申请单号");
		model->setHeaderData(1, Qt::Horizontal, "药品本位码");
		model->setHeaderData(2, Qt::Horizontal, "产品名");
		model->setHeaderData(3, Qt::Horizontal, "总量");
		model->setHeaderData(4, Qt::Horizontal, "已收到量");
		model->setHeaderData(5, Qt::Horizontal, "总库存量");
		if (model->lastError().isValid())
			return nullptr;
		qDebug() << "apr_model get";
		return model;
	}
	return nullptr;
}

QSqlQueryModel *medicines::searh_storage(QString mid, QString batch_num)
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		QString sql = QString(
						  "select "
						  "storage.wid, storage.num "
						  "from storage "
						  "where "
						  "storage.batch_num = '%1' and "
						  "storage.mid = '%2'")
						  .arg(batch_num, mid);
		qDebug() << sql;
		model->setQuery(sql);
		model->setHeaderData(0, Qt::Horizontal, "货架号");
		model->setHeaderData(1, Qt::Horizontal, "存量");
		if (model->lastError().isValid()) {
			qDebug() << model->lastError();
			return nullptr;
		}
		return model;
	}
	return nullptr;
}

QSqlQueryModel *medicines::searh_inv(QString mid)
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		QString sql = QString(
						  "select batch_num, all_num from inventory "
						  "where mid = %1")
						  .arg(mid);
		qDebug() << sql;
		model->setQuery(sql);
		model->setHeaderData(0, Qt::Horizontal, "生产批次");
		model->setHeaderData(1, Qt::Horizontal, "批次库存量");
		if (model->lastError().isValid()) {
			qDebug() << model->lastError();
			return nullptr;
		}
		return model;
	}
	return nullptr;
}

QSqlError medicines::add_otr(QString mid, QString batch_num, int all_num,
							 QDate date, int staff, int apr_id)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		//插入入库记录
		query.prepare(
			"insert into out_record "
			"( mid, batch_num, num, date, staff, application_record, state) "
			"values(?, ?, ?, ?, ?, ?, ?)");
		query.addBindValue(mid);
		query.addBindValue(batch_num);
		query.addBindValue(all_num);
		query.addBindValue(date);
		query.addBindValue(staff);
		query.addBindValue(apr_id);
		query.addBindValue(0);
		query.exec();
		err = query.lastError();
		if (err.isValid()) {
			db.rollback();
			qDebug() << err;
			return err;
		}
		//更新申请记录状态
		query.prepare(
			"update application_record "
			"set goted = goted + ?,	"
			"state = case when num = goted then 1 else 0 end "
			"where id = ?");
		query.addBindValue(all_num);
		query.addBindValue(apr_id);
		query.exec();
		err = query.lastError();
		if (err.isValid()) {
			db.rollback();
			qDebug() << err;
			return err;
		}
		db.commit();
	} else {
		err = db.lastError();
	}
	if (err.isValid()) {
		qDebug() << err;
	}
	return err;
}

QSqlQueryModel *medicines::get_otr_info(int id)
{
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery(
			QString("select "
					"out_record.state, "
					"application_record.id, "
					"out_record.mid, "
					"medicine.approval_name_zh, "
					"application_record.num, "
					"application_record.goted, "
					"out_record.batch_num, "
					"out_record.num, "
					"out_record.date, "
					"staff.name, "
					"quality_record.id, "
					"case "
					"when quality_record.quality = 0 then '合格' "
					"when quality_record.quality = 1 then '不合格' "
					"else '' "
					"end as quality "
					"from application_record,medicine,staff, "
					"out_record left outer join quality_record "
					"on out_record.quality_record = quality_record.id "
					"where out_record.mid = medicine.mid and "
					"out_record.staff = staff.id and "
					"out_record.application_record = application_record.id and "
					"out_record.id = %1")
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

QSqlError medicines::commit_otr(int id, QAbstractItemModel *model)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		query.prepare(
			"update out_record, application_record, inventory "
			"set out_record.state = 2, "
			"application_record.came  = application_record.came + "
			"out_record.num, "
			"application_record.state = "
			"case "
			"when application_record.came + out_record.num = "
			"application_record.num "
			"then 2 "
			"else application_record.state "
			"end, "
			"inventory.all_num = inventory.all_num - out_record.num "
			"where "
			"out_record.application_record = application_record.id and "
			"out_record.mid = inventory.mid and "
			"out_record.batch_num = inventory.batch_num and "
			"out_record.id = ?");
		query.addBindValue(id);
		query.exec();
		err = query.lastError();
		if (err.isValid()) {
			qDebug() << err;
			db.rollback();
			return err;
		}
		for (int i = 0; i != model->rowCount(); ++i) {
			int wid = model->data(model->index(i, 0)).toInt();
			int num = model->data(model->index(i, 1)).toInt();
			query.prepare(
				"update storage,out_record "
				"set storage.num = storage.num - ? "
				"where storage.mid = out_record.mid and "
				"storage.batch_num = out_record.batch_num and "
				"wid = ? and out_record.id = ?");
			query.addBindValue(num);
			query.addBindValue(wid);
			query.addBindValue(id);
			query.exec();
			err = query.lastError();
			if (err.isValid()) {
				qDebug() << err;
				db.rollback();
				return err;
			}
		}
		query.exec("delete from storage where num = 0");
		err = query.lastError();
		if (err.isValid()) {
			qDebug() << err;
			db.rollback();
			return err;
		}
		db.commit();
	} else {
		err = db.lastError();
	}
	if (err.isValid()) {
		qDebug() << err;
	}
	return err;
}

QSqlError medicines::abort_otr(int id)
{
	QSqlDatabase db = database_mngr::get_connection();
	QSqlError err;
	if (db.isOpen()) {
		db.transaction();
		QSqlQuery query;
		query.prepare(
			"update out_record,application_record "
			"set out_record.state = 3, "
			"application_record.goted = application_record.goted - "
			"out_record.num, "
			"application_record.state = 0 "
			"where out_record.application_record = application_record.id and "
			"out_record.id = ?");
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
