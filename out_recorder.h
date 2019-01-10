#ifndef OUT_RECORDER_H
#define OUT_RECORDER_H

#include "apr_selecter.h"
#include "inv_selecter.h"
#include "staff_mngr.h"
#include "storage_select.h"
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
class out_recorder;
}

class out_recorder : public QWidget
{
	Q_OBJECT

  public:
	explicit out_recorder(QWidget *parent = nullptr, int otr = -1);
	~out_recorder();

  signals:
	void commited();

  private slots:
	void on_select_apr_clicked();
	void update_commit_btn();
	void on_select_inv_clicked();
	void on_insert_clicked();
	void on_rollback_clicked();
	void on_req_qur_clicked();
	void on_select_storage_clicked();
	void on_commit_clicked();
	void on_abort_clicked();

  private:
	int otr;
	Ui::out_recorder *ui;
	QDate date;
	QTableWidget *out_list;
	int num_limit;
	int num_out_sum;
};

#endif // OUT_RECORDER_H
