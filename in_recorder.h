#ifndef IN_RECORDER_H
#define IN_RECORDER_H

#include "pur_selecter.h"
#include "staff_mngr.h"
#include <QDate>
#include <QDebug>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>

namespace Ui
{
class in_recorder;
}

class in_recorder : public QWidget
{
	Q_OBJECT

  public:
	explicit in_recorder(QWidget *parent = nullptr, int inr = -1);
	~in_recorder();

  signals:
	void commited();

  private slots:
	void on_select_pur_clicked();
	void on_req_qur_clicked();
	void on_insert_clicked();
	void on_rollback_clicked();
	void update_commit_btn();
	void on_commit_clicked();

	void on_abort_clicked();

  private:
	Ui::in_recorder *ui;
	int inr;
	QDate date;
	QTableWidget *storage;
	int storage_num_sum;
};

#endif // IN_RECORDER_H
