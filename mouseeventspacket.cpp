#include "mouseeventpacket.h"
#include "mouseeventspacket.h"
#include <Qdebug>

using namespace DG;
MouseEventsPacket::MouseEventsPacket():Packet(Packet::MouseEventPacket){

}

MouseEventsPacket::MouseEventsPacket(QList<DG::MouseEventPacket*> packets):Packet(Packet::MouseEventPacket), _packets(packets){

}

QDataStream& MouseEventsPacket::serialize(QDataStream& stream) const{
	qDebug() << "MouseEventsPacket::serialize " << "_packets.count()" << _packets.count();
	stream << _packets.count();
	foreach(DG::MouseEventPacket* packet, _packets){
		stream << *packet;
	}
	return stream;
}

QDataStream& MouseEventsPacket::unserialize(QDataStream& stream){
	quint32 size = 0;
	stream >> size;
	for(quint32 i=0;i<size;++i){
		DG::MouseEventPacket* packet = new DG::MouseEventPacket;
		stream >> *packet;
		_packets << packet;
	}
	return stream;
}

void MouseEventsPacket::reflect(){
	foreach(DG::MouseEventPacket* packet, _packets){
		packet->reflect();
		delete packet;
		packet = 0x0;
	}
	_packets.clear();
}

MouseEventsPacket::~MouseEventsPacket(){
	foreach(DG::MouseEventPacket* packet, _packets){
		if(packet != 0x0){
			delete packet;
			packet = 0x0;
		}
	}
	_packets.clear();
}

quint64 MouseEventsPacket::size() const{
	return sizeof(quint32)+(_packets.count()*DG::MouseEventPacket::size());
}

quint32 MouseEventsPacket::count() const{
	return _packets.size();
}
