#ifndef APPLICATION_RECORD_H
#define APPLICATION_RECORD_H

#include "medicine_selecter.h"
#include "medicines.h"
#include "staff_mngr.h"
#include <QDate>
#include <QIntValidator>
#include <QMessageBox>
#include <QWidget>

namespace Ui
{
class application_record;
}

class application_record : public QWidget
{
	Q_OBJECT

  public:
	explicit application_record(QWidget *parent = nullptr);
	~application_record();

  private slots:
	void on_select_mid_clicked();

	void on_commit_clicked();

  private:
	Ui::application_record *ui;
	QDate date;
};

#endif // APPLICATION_RECORD_H
