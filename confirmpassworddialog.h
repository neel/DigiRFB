#ifndef CONFIRMPASSWORDDIALOG_H
#define CONFIRMPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
    class ConfirmPasswordDialog;
}

namespace DG{
class ConfirmPasswordDialog : public QDialog{
	Q_OBJECT
	public:
		explicit ConfirmPasswordDialog(QWidget *parent = 0);
		~ConfirmPasswordDialog();
	private:
		Ui::ConfirmPasswordDialog *ui;
	signals:
		void confirmed(const QString& password);
	private slots:
		void acceptedSlot();
};
}
#endif // CONFIRMPASSWORDDIALOG_H
