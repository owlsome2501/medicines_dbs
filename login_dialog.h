#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include "staff_mngr.h"
#include <QDebug>
#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>

namespace Ui
{
class login_dialog;
}

class login_dialog : public QDialog
{
	Q_OBJECT

  public:
	explicit login_dialog(QWidget *parent = nullptr);
	~login_dialog();

  private slots:
	void login();

  private:
	Ui::login_dialog *ui;
	void keyPressEvent(QKeyEvent *evt);
};

#endif // LOGIN_DIALOG_H
