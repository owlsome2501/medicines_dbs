#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "staff_mngr.h"
#include <QDebug>
#include <QMainWindow>
#include <QSharedPointer>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	explicit MainWindow(QSharedPointer<staff_mngr> staff,
						QWidget *parent = nullptr);
	~MainWindow();

  private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
