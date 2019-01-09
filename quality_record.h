#ifndef QUALITY_RECORD_H
#define QUALITY_RECORD_H

#include "medicines.h"
#include "staff_mngr.h"
#include <QDate>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QWidget>

namespace Ui
{
class quality_record;
}

class quality_record : public QWidget
{
	Q_OBJECT

  public:
	explicit quality_record(int type, int io_id, QWidget *parent = nullptr);
	~quality_record();

  signals:
	void commited();

  private slots:
	void on_commit_clicked();

  private:
	Ui::quality_record *ui;
	QDate date;
	int type;
	int io_id;
};

#endif // QUALITY_RECORD_H
