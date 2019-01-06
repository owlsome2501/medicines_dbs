#ifndef MEDICINES_H
#define MEDICINES_H

#include "database_mngr.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class medicines
{
  public:
	medicines();
	static QSqlQueryModel *get_overview_model();
	static QSqlQueryModel *get_analysis_model();
};

#endif // MEDICINES_H
