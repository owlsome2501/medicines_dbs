#ifndef OUT_RECORDER_H
#define OUT_RECORDER_H

#include <QWidget>

namespace Ui
{
class out_recorder;
}

class out_recorder : public QWidget
{
	Q_OBJECT

  public:
	explicit out_recorder(QWidget *parent = nullptr, int otr = -1);
	~out_recorder();

  private:
	int otr;
	Ui::out_recorder *ui;
};

#endif // OUT_RECORDER_H
