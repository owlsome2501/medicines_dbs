#ifndef DATABASE_MNGR_H
#define DATABASE_MNGR_H

#include <QSqlDatabase>
#include <QSqlError>

class database_mngr
{
  public:
	static QSqlError connect();
	static QSqlDatabase get_connection();
};

#endif // DATABASE_MNGR_H
