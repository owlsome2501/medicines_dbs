#ifndef OVERVIEW_H
#define OVERVIEW_H

#include "mate_handler.h"
#include "medicines.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QWidget>

namespace Ui
{
class overview;
}

class overview : public mate_handler
{
	Q_OBJECT

  public:
	explicit overview(mate_handler *parent = nullptr);
	~overview();

  private:
	Ui::overview *ui;
};

#endif // OVERVIEW_H
