#include "database_mngr.h"

QSqlError database_mngr::connect()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("127.0.0.1");
	db.setDatabaseName("medicines");
	db.setUserName("root");
	db.setPassword("my-secret-pw");
	db.open();
	return db.lastError();
}

QSqlDatabase database_mngr::get_connection()
{
	return QSqlDatabase::database();
}
