#ifndef MEDICINES_H
#define MEDICINES_H

#include "database_mngr.h"
#include <QAbstractItemModel>
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class medicines
{
  public:
	medicines();
	static QSqlQueryModel *get_overview_model();
	static QSqlQueryModel *get_analysis_model();
	static QSqlQueryModel *search_medichine(QString mid, QString ap_name,
											QString ap_num);
	static QSqlError add_pur(QString mid, int num, double price,
							 QString supplier, QDate date, int staff);
	static QSqlQueryModel *get_pur_model();
	static QSqlQueryModel *get_io_wait_mngr_model();
	static QSqlError add_inr(QString mid, int batch_num, int all_num,
							 QDate date, int staff, int pur_id,
							 QDate production_date);
	static QSqlQueryModel *get_qc_wait_model();
	static QSqlQueryModel *get_io_info_for_qc(int type, int id);
	static QSqlError add_qur(int type, int io_id, int quality, QString detail,
							 int staff, QDate date);
	static QSqlQueryModel *get_inr_info(int id);
	static QSqlError commit_inr(int id, QAbstractItemModel *model);
	static QSqlError abort_inr(int id);
};

#endif // MEDICINES_H
