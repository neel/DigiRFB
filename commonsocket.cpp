#include "commonsocket.h"

#include <QDebug>

using namespace DG;
#include "messagepacket.h"
#include "screenpacket.h"

CommonSocket::CommonSocket(QObject* parent): QTcpSocket(parent){
	headerSize = sizeof(DG::Packet::CommonHeader);
	payloadSize = 0;
	readerState = Header;
	sockStream.setDevice(this);
	sockStream.setVersion(QDataStream::Qt_4_7);
	connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChangedSlot(QAbstractSocket::SocketState)));
	connect(this, SIGNAL(readyRead()), this, SLOT(readAvailableSlot()));
}

void CommonSocket::stateChangedSlot(QAbstractSocket::SocketState socketState){
	if(socketState == QAbstractSocket::ConnectedState){
		state = Connected;
	}
	qDebug() << ">> Socket State Changed: " << socketState;
}

CommonSocket::~CommonSocket(){

}
/*
QByteArray CommonSocket::rcv(){
	return _conversationBuffer;
}
*/
DG::Packet* CommonSocket::rcv(){
	if(!packetQueue.isEmpty()){
		qDebug() << "!! packetQueue.size" << packetQueue.size();
		DG::Packet* packet = packetQueue.dequeue();
		if(packet->type() == Packet::MessagePacket){
			DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(packet);
			qDebug() << "<<" << m->message();
		}
		return packet;
	}
	return 0x0;
}
/*
quint64 CommonSocket::send(const QByteArray& bytes){
	sockStream << bytes.size();
	return writeData(bytes.data(), bytes.size());
}
*/
quint64 CommonSocket::send(DG::Packet* packet){
	sockStream << DG::Packet::CommonHeader(packet->size(), packet->type());
	sockStream << *packet;
	if(packet->type() == Packet::MessagePacket){
		DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(packet);
		qDebug() << ">>" << m->message();
	}else{
		DG::ScreenPacket* s = dynamic_cast<DG::ScreenPacket*>(packet);
		qDebug() << ">> screen [" << s->row() << s->col() << "]";
	}
	return packet->size();
}

CommonSocket::State CommonSocket::currentState(){
	return state;
}

void CommonSocket::readAvailableSlot(){
	while(bytesAvailable() >= currentReadSize()){
		qDebug() << "readerState " << (int)readerState << "bytesAvailable() " << bytesAvailable() << "currentReadSize() " << currentReadSize();
		if(readerState == Header){
			DG::Packet::CommonHeader* header = new DG::Packet::CommonHeader;
			sockStream >> *header;
			readerState = Payload;
			payloadSize = header->size;
			lastHeader = header;
			qDebug() << "Header: " << header->id << header->size;
		}else{
			DG::Packet* packet;
			if(lastHeader->packetType == Packet::MessagePacket){
				packet =  new MessagePacket;
			}else{
				packet = new ScreenPacket;
			}
			sockStream >> *packet;
			payloadSize = 0;
			packetQueue.append(packet);
			readerState = Header;
			qDebug() << "recieved packet of size " << packet->size() << "packetQueue.size() "  << packetQueue.size();
			emit msgWaiting();
		}
	}
}
