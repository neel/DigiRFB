#ifndef CHALLANGEDIALOG_H
#define CHALLANGEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class ChallangeDialog;
}

namespace DG{
class ChallangeDialog : public QDialog{
	Q_OBJECT
	public:
		explicit ChallangeDialog(QWidget *parent = 0);
		~ChallangeDialog();
	private:
		Ui::ChallangeDialog *ui;
	signals:
		void challanged(const QString& password);
	private slots:
		void acceptedSlot();
};
}
#endif // CHALLANGEDIALOG_H
