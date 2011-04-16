#include "commonsocket.h"

CommonSocket::CommonSocket(QObject* parent): QTcpSocket(parent), unreadyBytes(0){

}

QByteArray CommonSocket::rcv(){

}

qint64 CommonSocket::send(const QByteArray& bytes){

}

State CommonSocket::currentState(){

}

void CommonSocket::readAvailableSlot(){
	while (bytesAvailable() > 0){

	}
}
