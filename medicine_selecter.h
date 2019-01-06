#ifndef MEDICINE_SELECTER_H
#define MEDICINE_SELECTER_H

#include "medicines.h"
#include <QDialog>
#include <QKeyEvent>
#include <QModelIndex>

namespace Ui
{
class medicine_selecter;
}

class medicine_selecter : public QDialog
{
	Q_OBJECT

  public:
	explicit medicine_selecter(QWidget *parent = nullptr);
	~medicine_selecter();
	QString getMid() const;
	QString getAp_name() const;

  private slots:
	void on_search_clicked();
	void confirm(const QModelIndex &index);

  private:
	QString mid;
	QString ap_name;
	Ui::medicine_selecter *ui;
	QSqlQueryModel *model;
	void keyPressEvent(QKeyEvent *evt);
};

#endif // MEDICINE_SELECTER_H
