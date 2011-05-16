#include "mouseeventpacket.h"

using namespace DG;

MouseEventPacket::MouseEventPacket(MouseEventType mouseEventType):EventPacket(EventPacket::MouseEvent), _mouseEventType(mouseEventType){

}

MouseEventPacket::MouseEventPacket(MouseEventType mouseEventType, quint16 x, quint16 y):EventPacket(EventPacket::MouseEvent), _mouseEventType(mouseEventType), _x(x), _y(y){

}

MouseEventPacket::MouseEventType MouseEventPacket::mouseEventType() const{
	return _mouseEventType;
}

quint16 MouseEventPacket::x() const{
	return _x;
}

quint16 MouseEventPacket::y() const{
	return _y;
}

QDataStream& MouseEventPacket::serialize(QDataStream& stream) const{
	EventPacket::serialize(stream);
	stream << _mouseEventType << _x << _y;
	return stream;
}

QDataStream& MouseEventPacket::unserialize(QDataStream& stream){
	EventPacket::serialize(stream);
	int mouseEventType;
	stream >> mouseEventType >> _x >> _y;
	_mouseEventType = (MouseEventType)mouseEventType;
	return stream;
}
