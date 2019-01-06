#ifndef STAFF_MNGR_H
#define STAFF_MNGR_H

#include "database_mngr.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

class staff_mngr
{
  public:
	enum struct Role : int { ADMIN, MANAGER, INSPECTOR, APPLICANT };

  public:
	static bool login(int id, QString password);

	static QString getName();
	static Role getRole();
	static int getId();

  private:
	static QString name;
	static int id;
	static Role role;
};

#endif // STAFF_MNGR_H
