#ifndef PUR_SELECTER_H
#define PUR_SELECTER_H

#include "medicines.h"
#include <QDialog>
#include <QMessageBox>
#include <QModelIndex>

namespace Ui
{
class pur_selecter;
}

class pur_selecter : public QDialog
{
	Q_OBJECT

  public:
	explicit pur_selecter(QWidget *parent = nullptr);
	~pur_selecter();
	int getPur_id() const;
	QString getMid() const;
	QString getAp_name() const;

  private slots:
	void confirm(const QModelIndex &index);

  private:
	Ui::pur_selecter *ui;
	QSqlQueryModel *model;
	int pur_id;
	QString mid;
	QString ap_name;
};

#endif // PUR_SELECTER_H
