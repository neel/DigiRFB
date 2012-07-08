#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include <QObject>
#include "canvas.h"
#include <QGraphicsView>
#include "server.h"
#include "serverconnectiondialog.h"

class ServerInterface : public QObject{
    Q_OBJECT
private:
    DG::Canvas scene;
    QGraphicsView view;
    DG::Server* server;
    ServerConnectionDialog* dialog;
public:
    explicit ServerInterface(QObject *parent = 0);
    
signals:
    
public slots:
    void startServer(int port);
    void quitSlot();
};

#endif // SERVERINTERFACE_H
