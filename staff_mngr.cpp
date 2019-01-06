#include "staff_mngr.h"

int staff_mngr::id;
staff_mngr::Role staff_mngr::role;
QString staff_mngr::name;

bool staff_mngr::login(int _id, QString password)
{
	bool result = false;
	QSqlDatabase db = database_mngr::get_connection();
	if (db.isOpen()) {
		qDebug() << "connected";
		QSqlQuery query;
		query.prepare("select * from staff where id = ?");
		query.addBindValue(_id);
		query.exec();
		if (query.next()) {
			QString passwd_real = query.value(2).toString();
			if (password == passwd_real) {
				name = query.value(1).toString();
				role = static_cast<Role>(query.value(3).toInt());
				id = _id;
				result = true;
			}
		}
	} else
		qDebug() << "not opened";
	return result;
}

int staff_mngr::getId() { return id; }

QString staff_mngr::getName() { return name; }

staff_mngr::Role staff_mngr::getRole() { return role; }
