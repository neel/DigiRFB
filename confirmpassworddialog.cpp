#include "confirmpassworddialog.h"
#include "ui_confirmpassworddialog.h"

using namespace DG;

ConfirmPasswordDialog::ConfirmPasswordDialog(QWidget *parent): QDialog(parent), ui(new Ui::ConfirmPasswordDialog){
	ui->setupUi(this);
	QObject::connect(this, SIGNAL(accepted()), this, SLOT(acceptedSlot()));
}

ConfirmPasswordDialog::~ConfirmPasswordDialog(){
	delete ui;
}

void ConfirmPasswordDialog::acceptedSlot(){
	QString text = ui->passBox->text();
	emit confirmed(text);
}
