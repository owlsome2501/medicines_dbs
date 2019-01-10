#ifndef APR_SELECTER_H
#define APR_SELECTER_H

#include "medicines.h"
#include <QDialog>
#include <QMessageBox>
#include <QModelIndex>

namespace Ui
{
class apr_selecter;
}

class apr_selecter : public QDialog
{
	Q_OBJECT

  public:
	explicit apr_selecter(QWidget *parent = nullptr);
	~apr_selecter();
	int getApr_id() const;
	QString getMid() const;
	QString getAp_name() const;
	int getAll_num() const;
	int getGoted() const;
	int getAll_inv_num() const;

  private slots:
	void confirm(const QModelIndex &index);

  private:
	Ui::apr_selecter *ui;
	QSqlQueryModel *model;
	int apr_id;
	QString mid;
	QString ap_name;
	int all_num;
	int goted;
	int all_inv_num;
};

#endif // APR_SELECTER_H
