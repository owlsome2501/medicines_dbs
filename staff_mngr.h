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
	staff_mngr();
	bool login(int id, QString password);

	QString getName() const;
	Role getRole() const;

  private:
	QString name;
	Role role;
};

#endif // STAFF_MNGR_H
