#ifndef IN_RECORDER_H
#define IN_RECORDER_H

#include "pur_selecter.h"
#include "staff_mngr.h"
#include <QDate>
#include <QDebug>
#include <QIntValidator>
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

  private slots:
	void on_select_pur_clicked();

	void on_req_qur_clicked();

  private:
	Ui::in_recorder *ui;
	int inr;
	QDate date;
};

#endif // IN_RECORDER_H
