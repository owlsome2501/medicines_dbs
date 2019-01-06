#ifndef MATE_HANDLER_H
#define MATE_HANDLER_H

#include <QWidget>

class mate_handler : public QWidget
{
	Q_OBJECT

  public:
	mate_handler(QWidget *parent = nullptr);

  public slots:
	void sync();
};

#endif // MATE_HANDLER_H
