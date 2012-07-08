#include "clientconnectiondialog.h"
#include "ui_clientconnectiondialog.h"

ClientConnectionDialog::ClientConnectionDialog(QWidget *parent): QDialog(parent), ui(new Ui::ClientConnectionDialog){
    ui->setupUi(this);
    QObject:connect(this, SIGNAL(accepted()), this, SLOT(acceptedSlot()));
}

ClientConnectionDialog::~ClientConnectionDialog(){
    delete ui;
}

void ClientConnectionDialog::acceptedSlot(){
    QString host = ui->hostEdit->text();
    int port = ui->portEdit->value();
    emit connectionRequested(host, port);
}

