#include "serverinterface.h"
#include <QApplication>

ServerInterface::ServerInterface(QObject *parent) : QObject(parent){
    view.setScene(&scene);
    view.setMouseTracking(true);
    server = new DG::Server(&scene);
    dialog = new ServerConnectionDialog;
    QObject::connect(dialog, SIGNAL(serverStarted(int)), this, SLOT(startServer(int)));
    QObject::connect(dialog, SIGNAL(serverQuit()), this, SLOT(quitSlot()));
    dialog->show();
}

void ServerInterface::startServer(int port){
    server->listen(5590);
    view.show();
}

void ServerInterface::quitSlot(){
    server->close();
    QApplication::quit();
}
