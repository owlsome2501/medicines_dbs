#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QListView"
#include "analysis.h"
#include "application_record.h"
#include "in_recorder.h"
#include "out_recorder.h"
#include "overview.h"
#include "purchase_record.h"
#include "quality_record.h"
#include "staff_mngr.h"
#include <QAction>
#include <QDebug>
#include <QMainWindow>
#include <QModelIndex>
#include <QTableView>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

  public slots:
	void sync();

  private slots:
	void on_tabclose(int index);
	void on_overview_triggered();
	void on_purchase_analysis_triggered();
	void on_purchase_record_triggered();
	void on_application_record_triggered();
	void on_in_record_triggered();
	void on_out_record_triggered();
	void watcher_enter(const QModelIndex &index);

  private:
	Ui::MainWindow *ui;
	QTabWidget *main_tab;
	QTableView *watcher;
	QSqlQueryModel *model;
	int timer;
	QWidget *add_widget(QWidget *widget, QString title);

  protected:
	void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
