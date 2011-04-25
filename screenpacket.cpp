#include "screenpacket.h"
#include <QByteArray>
#include <QDataStream>
#include <QGraphicsPixmapItem>

using namespace DG;

ScreenPacket::ScreenPacket(){

}

ScreenPacket::ScreenPacket(int state):Packet(Packet::ScreenPacket, state){

}

/**
	* operator=() called deep copy
	*/
void ScreenPacket::setRect(const Rect &rect){
	_rect = rect;
}

void ScreenPacket::setIndex(quint32 row, quint32 col){
	_row = row;
	_col = col;
}

void ScreenPacket::setPixmap(const QPixmap& pixmap){
	_pixmap = pixmap;
}

quint32 ScreenPacket::row() const{
	return _row;
}

quint32 ScreenPacket::col() const{
	return _col;
}

const DG::Rect& ScreenPacket::rect() const{
	return _rect;
}

const QPixmap& ScreenPacket::pixmap() const{
	return _pixmap;
}

QDataStream& ScreenPacket::serialize(QDataStream& stream) const{
	stream << _row << _col << _rect << _pixmap;
	return stream;
}

QDataStream& ScreenPacket::unserialize(QDataStream& stream){
	stream >> _row >> _col >> _rect >> _pixmap;
	return stream;
}

quint64 ScreenPacket::size() const{
	QByteArray buff;
	QDataStream stream(&buff, QIODevice::ReadWrite);
	stream.setVersion(QDataStream::Qt_4_7);
	stream << _pixmap;

	return ((sizeof(*this)-sizeof(_pixmap))+buff.size());
}

QGraphicsPixmapItem* ScreenPacket::graphicsPixmapItem() const{
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(_pixmap);
	item->setOffset(_rect.left, _rect.top);
	return item;
}
