#ifndef INV_SELECTER_H
#define INV_SELECTER_H

#include "medicines.h"
#include <QDialog>
#include <QMessageBox>
#include <QModelIndex>

namespace Ui
{
class inv_selecter;
}

class inv_selecter : public QDialog
{
	Q_OBJECT

  public:
	explicit inv_selecter(QString mid, QWidget *parent = nullptr);
	~inv_selecter();
	QString getBatch_num() const;
	int getNum() const;

  private slots:
	void confirm(const QModelIndex &index);

  private:
	Ui::inv_selecter *ui;
	QString mid;
	QSqlQueryModel *model;
	QString batch_num;
	int num;
};

#endif // INV_SELECTER_H
