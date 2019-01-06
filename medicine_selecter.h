#ifndef MEDICINE_SELECTER_H
#define MEDICINE_SELECTER_H

#include <QDialog>
#include <QKeyEvent>

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

  private:
	Ui::medicine_selecter *ui;
	void keyPressEvent(QKeyEvent *evt);
};

#endif // MEDICINE_SELECTER_H
