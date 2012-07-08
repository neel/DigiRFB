#ifndef CLIENTCONECTOR_H
#define CLIENTCONECTOR_H

#include <QObject>
#include "clientconnectiondialog.h"
#include "clientsocket.h"

class ClientConector : public QObject{
    Q_OBJECT
private:
    ClientConnectionDialog* dialog;
    DG::ClientSocket* _socket;
public:
    explicit ClientConector(QObject *parent = 0);
    virtual ~ClientConector();
signals:
    
public slots:
    void connectSlot(const QString& host, int port);
public:
    void initiate();
    
};

#endif // CLIENTCONECTOR_H
