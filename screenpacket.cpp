#include "screenpacket.h"

using namespace DG;

ScreenPacket::ScreenPacket(){

}

ScreenPacket::ScreenPacket(int state):Packet(Packet::ScreenPacket, state){

}

void ScreenPacket::setPosition(quint32 left, quint32 top){
	_left = left;
	_top = top;
}

void ScreenPacket::setSize(quint32 width, quint32 height){
	_width = width;
	_height = height;
}

void ScreenPacket::setIndex(quint32 row, quint32 col){
	_row = row;
	_col = col;
}

void ScreenPacket::setBuffer(const QByteArray& buffer){
	_buffer = buffer;
}

quint32 ScreenPacket::row() const{
	return _row;
}

quint32 ScreenPacket::col() const{
	return _col;
}

quint32 ScreenPacket::left() const{
	return _left;
}

quint32 ScreenPacket::top() const{
	return _top;
}

quint32 ScreenPacket::width() const{
	return _width;
}

quint32 ScreenPacket::height() const{
	return _height;
}

const QByteArray& ScreenPacket::buffer() const{
	return _buffer;
}

QDataStream& ScreenPacket::serialize(QDataStream& stream) const{
	stream << _row << _col << _left << _top << _width << _height << _buffer;
	return stream;
}

QDataStream& ScreenPacket::unserialize(QDataStream& stream){
	stream >> _row >> _col >> _left >> _top >> _width >> _height >> _buffer;
	return stream;
}

quint64 ScreenPacket::size() const{
	return (sizeof(*this)-sizeof(_buffer)+_buffer.size());
}
