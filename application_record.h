#ifndef APPLICATION_RECORD_H
#define APPLICATION_RECORD_H

#include <QWidget>

namespace Ui {
class application_record;
}

class application_record : public QWidget
{
	Q_OBJECT

	public:
	explicit application_record(QWidget *parent = nullptr);
	~application_record();

	private:
	Ui::application_record *ui;
};

#endif // APPLICATION_RECORD_H
