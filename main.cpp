#include <QtGui/QApplication>
#include "clientsocket.h"
#include <QHostAddress>

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	DG::ClientSocket* socket = new DG::ClientSocket;
	socket->connectToHost(QHostAddress::LocalHost, 5590);
	return a.exec();
}
