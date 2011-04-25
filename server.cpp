#include "server.h"
#include "serversocket.h"

using namespace DG;

Server::Server(QObject *parent):QTcpServer(parent){

}

void Server::incomingConnection(int socketDescriptor){
	ServerSocket* socket = new ServerSocket();
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
