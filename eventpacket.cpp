#include "eventpacket.h"

using namespace DG;
EventPacket::EventPacket(EventType type, int state):Packet(Packet::EventPacket, state), _eventType(type){

}

EventPacket::EventPacket(EventType type):Packet(Packet::EventPacket, 11), _eventType(type){

}

QDataStream& EventPacket::serialize(QDataStream& stream) const{
	stream << _eventType;
	return stream;
}

QDataStream& EventPacket::unserialize(QDataStream& stream){
	int eType;
	stream >> eType;
	_eventType = (EventType)eType;
	return stream;
}
