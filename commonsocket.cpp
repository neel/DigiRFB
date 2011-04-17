#include "commonsocket.h"

using namespace DG;
#include "packet.h"

CommonSocket::CommonSocket(QObject* parent): QTcpSocket(parent){
	headerSize = sizeof(DG::Packet::CommonHeader);
	payloadSize = 0;
	readerState = Header;
	sockStream.setDevice(this);
	sockStream.setVersion(QDataStream::Qt_4_7);
}

CommonSocket::~CommonSocket(){

}

QByteArray CommonSocket::rcv(){
	return _conversationBuffer;
}

qint64 CommonSocket::send(const QByteArray& bytes){
	sockStream << bytes.size();
	return writeData(bytes.data(), bytes.size());
}

CommonSocket::State CommonSocket::currentState(){
	return state;
}

void CommonSocket::readAvailableSlot(){
	while(bytesAvailable() >= currentReadSize()){
		if(readerState == Header){
			sockStream >> payloadSize;
			readerState = Payload;
			_conversationBuffer.clear();
		}else{
			_conversationBuffer.append(read(currentReadSize()));
			readerState = Header;
			payloadSize = 0;
			emit msgWaiting();
		}
	}
}
