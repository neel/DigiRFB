#include "challangedialog.h"
#include "ui_challangedialog.h"
#include <QPushButton>

using namespace DG;
ChallangeDialog::ChallangeDialog(QWidget *parent): QDialog(parent), ui(new Ui::ChallangeDialog){
	ui->setupUi(this);
	QPushButton* okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
	if(okButton != 0x0){
		okButton->setText("Challange");
	}
	QObject::connect(this, SIGNAL(accepted()), this, SLOT(acceptedSlot()));
}

ChallangeDialog::~ChallangeDialog(){
	delete ui;
}

void ChallangeDialog::acceptedSlot(){
	QString text = ui->passBox->text();
	emit challanged(text);
}
