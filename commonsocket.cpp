#include "commonsocket.h"
#include <QMutexLocker>
#include <QDebug>

using namespace DG;
#include "messagepacket.h"
#include "screenpacket.h"
#include "mouseeventspacket.h"
#include "keyboardeventpacket.h"
#include <QTemporaryFile>
#include <QDataStream>

CommonSocket::CommonSocket(QObject* parent): QTcpSocket(parent){
	headerSize = sizeof(DG::Packet::CommonHeader);
	payloadSize = 0;
	readerState = Header;
	sockStream.setDevice(this);
	sockStream.setVersion(QDataStream::Qt_4_7);
	connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChangedSlot(QAbstractSocket::SocketState)));
	connect(this, SIGNAL(readyRead()), this, SLOT(readAvailableSlot()));
}

quint32 CommonSocket::currentReadSize() const{
    return readerState == Header ? headerSize : payloadSize;
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
	qDebug() << "Mutex" << &rcvMutex;
	QMutexLocker locker(&rcvMutex);
	if(!packetQueue.isEmpty()){
		//qDebug() << "!! packetQueue.size" << packetQueue.size();
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
	qDebug() << "Mutex" << &sendMutex;
	QMutexLocker locker(&sendMutex);
	DG::Packet::CommonHeader header = DG::Packet::CommonHeader(packet->size(), packet->type());
	sockStream << header;
	qDebug() << "Sending Header: " << header.id << header.size;
	sockStream << *packet;
	if(packet->type() == Packet::MessagePacket){
		DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(packet);
		qDebug() << ">>" << m->message();
	}else if(packet->type() == Packet::ScreenPacket){
		DG::ScreenPacket* s = dynamic_cast<DG::ScreenPacket*>(packet);
		qDebug() << ">> screen [" << s->rect().left << s->rect().top << "]";
	}else if(packet->type() == Packet::MouseEventPacket){
		DG::MouseEventsPacket* ms = dynamic_cast<DG::MouseEventsPacket*>(packet);
		qDebug() << ">> Mouse Events " << ms->count();
	}
	return packet->size();
}

CommonSocket::State CommonSocket::currentState(){
	return state;
}

void CommonSocket::readAvailableSlot(){
	qDebug() << "Mutex" << &readMutex;
	QMutexLocker locker(&readMutex);
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
			DG::Packet* packet = 0x0;
			if(lastHeader->packetType == Packet::MessagePacket){
				packet =  new MessagePacket;
			}else if(lastHeader->packetType == Packet::ScreenPacket){
				packet = new ScreenPacket;
			}else if(lastHeader->packetType == Packet::MouseEventPacket){
				packet = new MouseEventsPacket;
			}else if(lastHeader->packetType == Packet::KeyboardEventPacket){
				packet = new KeyboardEventPacket;
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

DG::Packet::PacketType CommonSocket::lastHeaderType() const{
	return lastHeader->packetType;
}
