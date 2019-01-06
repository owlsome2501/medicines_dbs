#ifndef MEDICINES_H
#define MEDICINES_H

#include "database_mngr.h"
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
};

#endif // MEDICINES_H
