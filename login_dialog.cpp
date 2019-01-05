#include "login_dialog.h"
#include "ui_login_dialog.h"

login_dialog::login_dialog(QWidget *parent)
	: QDialog(parent), staff(staff_mngr_ptr(new staff_mngr)),
	  ui(new Ui::login_dialog)
{
	ui->setupUi(this);
}

login_dialog::~login_dialog() { delete ui; }

void login_dialog::login()
{
	int id = (ui->staff_id->text()).toInt();
	QString password = ui->password->text();
	if (staff->login(id, password)) {
		accept();
	} else {
		QMessageBox::warning(this, "Waring", "user name or password error!",
							 QMessageBox::Yes);
	}
}

void login_dialog::keyPressEvent(QKeyEvent *evt)
{
	if (evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return)
		return;
	else
		QDialog::keyPressEvent(evt);
}
