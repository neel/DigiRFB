#include "messagepacket.h"

using namespace DG;

MessagePacket::MessagePacket(int state):Packet(state){

}

void MessagePacket::setMessage(QByteArray msg){
	_msg = msg;
}

QByteArray message() const{
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
