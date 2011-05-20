#include "eventpacket.h"

using namespace DG;

EventPacket::EventPacket():Packet(Packet::EventPacket){

}

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

quint64 EventPacket::size() const{
	return sizeof(*this);
}

DG::EventPacket::EventType EventPacket::eventType() const{
	return _eventType;
}

void EventPacket::reflect() const{

}

