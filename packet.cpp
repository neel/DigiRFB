#include "packet.h"

using namespace DG;

Packet::Packet(int state):_state(state){

}

Packet::CommonHeader::CommonHeader(quint32 sz){
	id = _id++;
	time = QTime::currentTime();
	size = sz;
}

QDataStream& operator<<(QDataStream& stream, const DG::Packet::CommonHeader& header){
	stream << header.id;
	stream << header.size;
	stream << header.time;
	stream << header.checksum;
	return stream;
}

QDataStream& operator>>(QDataStream& stream, const DG::Packet::CommonHeader& header){
	stream >> header.id;
	stream >> header.size;
	stream >> header.time;
	stream >> header.checksum;
	return stream;
}

QDataStream& operator<<(QDataStream& stream, const DG::Packet& packet){
	stream << packet._state;
	return packet.serialize(stream);
}

QDataStream& operator>>(QDataStream& stream, const DG::Packet& packet){
	stream >> packet._state;
	return packet.unserialize(stream);
}

quint32 Packet::CommonHeader::_id = 0;
