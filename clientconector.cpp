#include "clientconector.h"
#include <QDebug>

ClientConector::ClientConector(QObject *parent): QObject(parent), dialog(0x0){
    dialog = new ClientConnectionDialog();
    _socket = new DG::ClientSocket;
    QObject::connect(dialog, SIGNAL(connectionRequested(QString,int)), this, SLOT(connectSlot(QString,int)));
}
void ClientConector::initiate(){
    dialog->show();
 }
void ClientConector::connectSlot(const QString& host, int port){
    _socket->connectToHost(host, port);
    qDebug() << "Connecting with " << host << port;
}
ClientConector::~ClientConector(){
    delete dialog;
    delete _socket;
}
