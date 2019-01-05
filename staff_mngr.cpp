#include "staff_mngr.h"

staff_mngr::staff_mngr() {}

bool staff_mngr::login(int id, QString password)
{
	bool result = false;
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		qDebug() << "connected";
		QSqlQuery query;
		query.prepare("select * from staff where id = ?");
		query.addBindValue(id);
		query.exec();
		if (query.next()) {
			QString passwd_real = query.value(2).toString();
			if (password == passwd_real) {
				name = query.value(1).toString();
				role = static_cast<Role>(query.value(3).toInt());
				result = true;
			}
		}
	} else
		qDebug() << "not opened";
	return result;
}

QString staff_mngr::getName() const { return name; }

staff_mngr::Role staff_mngr::getRole() const { return role; }
