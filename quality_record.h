#ifndef QUALITY_RECORD_H
#define QUALITY_RECORD_H

#include <QWidget>

namespace Ui {
class quality_record;
}

class quality_record : public QWidget
{
	Q_OBJECT

	public:
	explicit quality_record(QWidget *parent = nullptr);
	~quality_record();

	private:
	Ui::quality_record *ui;
};

#endif // QUALITY_RECORD_H
