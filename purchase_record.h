#ifndef PURCHASE_RECORD_H
#define PURCHASE_RECORD_H

#include <QWidget>

namespace Ui
{
class purchase_record;
}

class purchase_record : public QWidget
{
	Q_OBJECT

  public:
	explicit purchase_record(QWidget *parent = nullptr);
	~purchase_record();

  private slots:
	void on_select_mid_clicked();

  private:
	Ui::purchase_record *ui;
};

#endif // PURCHASE_RECORD_H
