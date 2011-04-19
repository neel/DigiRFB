#include "commonsocket.h"

using namespace DG;
#include "messagepacket.h"
#include "screenpacket.h"

CommonSocket::CommonSocket(QObject* parent): QTcpSocket(parent){
	headerSize = sizeof(DG::Packet::CommonHeader);
	payloadSize = 0;
	readerState = Header;
	sockStream.setDevice(this);
	sockStream.setVersion(QDataStream::Qt_4_7);
}

CommonSocket::~CommonSocket(){

}
/*
QByteArray CommonSocket::rcv(){
	return _conversationBuffer;
}
*/
DG::Packet* CommonSocket::rcv(){
	return packetQueue.dequeue();
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
	return packet->size();
}

CommonSocket::State CommonSocket::currentState(){
	return state;
}

void CommonSocket::readAvailableSlot(){
	while(bytesAvailable() >= currentReadSize()){
		if(readerState == Header){
			DG::Packet::CommonHeader* header = new DG::Packet::CommonHeader;
			sockStream >> *header;
			readerState = Payload;
			payloadSize = header->size;
			lastHeader = header;
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
			emit msgWaiting();
		}
	}
}
