#ifndef PURCHASE_RECORD_H
#define PURCHASE_RECORD_H

#include <QWidget>

#include "medicine_selecter.h"
#include "staff_mngr.h"
#include <QDate>
#include <QDialog>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>

namespace Ui
{
class purchase_record;
}

class purchase_record : public QWidget
{
	Q_OBJECT

  public:
	explicit purchase_record(QWidget *parent = nullptr);
	~purchase_record();

  private slots:
	void on_select_mid_clicked();

	void on_commit_clicked();

  private:
	Ui::purchase_record *ui;
	QDate date;
};

#endif // PURCHASE_RECORD_H
