#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "analysis.h"
#include "application_record.h"
#include "overview.h"
#include "purchase_record.h"
#include "quality_record.h"
#include "staff_mngr.h"
#include <QAction>
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

  public slots:
	void sync();

  private slots:
	void on_tabclose(int index);
	void on_overview_triggered();
	void on_purchase_analysis_triggered();
	void on_purchase_record_triggered();

	void on_quality_record_triggered();

	void on_application_record_triggered();

  private:
	Ui::MainWindow *ui;
	QTabWidget *main_tab;
	QSharedPointer<staff_mngr> staff;
	QWidget *add_widget(QWidget *widget, QString title);
};

#endif // MAINWINDOW_H
