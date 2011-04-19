#include "messagepacket.h"

using namespace DG;

MessagePacket::MessagePacket(){

}

MessagePacket::MessagePacket(int state):Packet(Packet::MessagePacket, state){

}

void MessagePacket::setMessage(QByteArray msg){
	_msg = msg;
}

QByteArray MessagePacket::message() const{
	return _msg;
}

QDataStream& MessagePacket::serialize(QDataStream& stream) const{
	stream << _msg;
	return stream;
}

QDataStream& MessagePacket::unserialize(QDataStream& stream){
	stream >> _msg;
	return stream;
}

quint64 MessagePacket::size() const{
	return sizeof(*this)-sizeof(_msg)+_msg.size();
}
