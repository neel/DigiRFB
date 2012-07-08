#include "serverconnectiondialog.h"
#include "ui_serverconnectiondialog.h"

ServerConnectionDialog::ServerConnectionDialog(QWidget *parent) :  QDialog(parent), ui(new Ui::ServerConnectionDialog){
    Qt::WindowFlags flags = Qt::Window | Qt::WindowSystemMenuHint
                                | Qt::WindowMinimizeButtonHint
                                | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    ui->setupUi(this);
    QObject::connect(ui->startBtn, SIGNAL(released()), this, SLOT(serverStartSlot()));
    QObject::connect(ui->quitBtn, SIGNAL(released()), this, SIGNAL(serverQuit()));
}

ServerConnectionDialog::~ServerConnectionDialog(){
    delete ui;
}

void ServerConnectionDialog::serverStartSlot(){
    emit serverStarted(ui->portEdit->value());
}
