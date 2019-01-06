#ifndef IN_RECORDER_H
#define IN_RECORDER_H

#include "pur_selecter.h"
#include "staff_mngr.h"
#include <QDate>
#include <QDebug>
#include <QWidget>

namespace Ui
{
class in_recorder;
}

class in_recorder : public QWidget
{
	Q_OBJECT

  public:
	explicit in_recorder(QWidget *parent = nullptr);
	~in_recorder();

  private slots:
	void on_select_pur_clicked();

  private:
	Ui::in_recorder *ui;
	QDate date;
};

#endif // IN_RECORDER_H
