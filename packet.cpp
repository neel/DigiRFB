#include "packet.h"

using namespace DG;

Packet::Packet(){

}

Packet::Packet(PacketType type, int state):_state(state), _type(type){

}

Packet::PacketType Packet::type() const{
	return _type;
}

Packet::CommonHeader::CommonHeader(){
    id = _id++;
    time = QTime::currentTime();
    size = 0;
}

Packet::CommonHeader::CommonHeader(quint32 sz, PacketType type){
	id = _id++;
	time = QTime::currentTime();
	size = sz;
	packetType = type;
}

QDataStream& DG::operator<<(QDataStream& stream, const Packet::CommonHeader& header){
	stream << header.id;
	stream << header.size;
	stream << header.time;
	stream << header.packetType;
	return stream;
}

QDataStream& DG::operator>>(QDataStream& stream, Packet::CommonHeader& header){
	int packetType;
	stream >> header.id;
	stream >> header.size;
	stream >> header.time;
	stream >> packetType;
	header.packetType = (DG::Packet::PacketType)packetType;
	return stream;
}

QDataStream& DG::operator<<(QDataStream& stream, const Packet& packet){
	stream << packet._state << packet._type;
	return packet.serialize(stream);
}

QDataStream& DG::operator>>(QDataStream& stream, Packet& packet){
	int _type;
	stream >> packet._state >> _type;
	packet._type = (DG::Packet::PacketType)_type;
	return packet.unserialize(stream);
}

quint64 Packet::CommonHeader::_id = 0;

