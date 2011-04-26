#include "server.h"
#include "serversocket.h"
#include <QGraphicsScene>

using namespace DG;

Server::Server(QGraphicsScene* scene, QObject *parent):QTcpServer(parent), _scene(scene){
	setMaxPendingConnections(1);
	connect(this, SIGNAL(newConnection()), this, SLOT(addClient()));
}

void Server::incomingConnection(int socketDescriptor){
	ServerSocket* socket = new ServerSocket(_scene);
	qDebug() << "Server::incomingConnection";
	if(socket->setSocketDescriptor(socketDescriptor)){
		QTcpServer::addPendingConnection(socket);
		//emit newConnection();
	}else{
		delete socket;
	}
}

void Server::addClient(){
	ServerSocket* socket = dynamic_cast<ServerSocket*>(nextPendingConnection());
	qDebug() << ">> New Client " << socket->localAddress() << socket->peerAddress();
	socket->clientConnected();
}

void Server::listen(qint64 port){
	QTcpServer::listen(QHostAddress::Any, port);
}
