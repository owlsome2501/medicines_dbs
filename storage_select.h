#ifndef STORAGE_SELECT_H
#define STORAGE_SELECT_H

#include "medicines.h"
#include <QDialog>
#include <QMessageBox>
#include <QModelIndex>

namespace Ui
{
class storage_select;
}

class storage_select : public QDialog
{
	Q_OBJECT

  public:
	explicit storage_select(QString mid, QString batch_num,
							QWidget *parent = nullptr);
	~storage_select();
	int getWid() const;
	int getNum() const;

  private slots:
	void confirm(const QModelIndex &index);

  private:
	Ui::storage_select *ui;
	QString mid;
	QString batch_num;
	QSqlQueryModel *model;
	int wid;
	int num;
};

#endif // STORAGE_SELECT_H
