#include "login_dialog.h"
#include "ui_login_dialog.h"

login_dialog::login_dialog(QWidget *parent)
	: QDialog(parent), ui(new Ui::login_dialog)
{
	ui->setupUi(this);
	QRegExp password_rgx("[a-zA-Z0-9]{16}");
	QValidator *password_v = new QRegExpValidator(password_rgx, this);
	ui->password->setValidator(password_v);
	QRegExp id_rgx("^[0-9]{6}");
	QValidator *id_v = new QRegExpValidator(id_rgx, this);
	ui->staff_id->setValidator(id_v);
}

login_dialog::~login_dialog() { delete ui; }

void login_dialog::login()
{
	int id = (ui->staff_id->text()).toInt();
	QString password = ui->password->text();
	if (staff_mngr::login(id, password)) {
		accept();
	} else {
		QMessageBox::warning(this, "错误", "用户名或者密码不正确",
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
