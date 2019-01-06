#ifndef OVERVIEW_H
#define OVERVIEW_H

#include "medicines.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QWidget>

namespace Ui
{
class overview;
}

class overview : public QWidget
{
	Q_OBJECT

  public:
	explicit overview(QWidget *parent = nullptr);
	~overview();

  private:
	Ui::overview *ui;
};

#endif // OVERVIEW_H
