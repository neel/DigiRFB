#include "screenpacket.h"
#include <QByteArray>
#include <QDataStream>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <QImageWriter>
#include <QImageReader>
#include <QBuffer>
#include <QPainter>
#include <QFont>
#include <QDateTime>

using namespace DG;

ScreenPacket::ScreenPacket():_pixmapGenerated(false){

}

ScreenPacket::ScreenPacket(int state):Packet(Packet::ScreenPacket, state), _pixmapGenerated(false){

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
	QImage image = pixmap.toImage();
	QPainter painter;
	painter.begin(&image);
	painter.fillRect(0, 0, 30, image.height()-10, Qt::white);
	painter.setPen(Qt::red);
	painter.setFont(QFont("Courier new", 12));
	painter.drawText(5, 10, QString::number(QTime::currentTime().second()));
	painter.end();
	QBuffer buffer;
	buffer.setBuffer(&_buffer);
	buffer.open(QBuffer::WriteOnly);
	buffer.seek(0);
	QImageWriter writer(&buffer, "jpeg");
	writer.setQuality(32);
	writer.setCompression(1);
	_pixmapGenerated = writer.write(image);
	_buffer = qCompress(_buffer, 9);
	//_pixmap = pixmap;
	_pixmap = QPixmap::fromImage(image);
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

QPixmap ScreenPacket::pixmap() const{
	if(_pixmapGenerated)
		return _pixmap;
	QBuffer buffer;
	buffer.setBuffer(const_cast<QByteArray*>(&_buffer));
	buffer.open(QBuffer::ReadOnly);
	QImageReader reader(&buffer, "jpeg");
	_pixmap = QPixmap::fromImage(reader.read());
	_pixmapGenerated = true;
	return _pixmap;
}

QDataStream& ScreenPacket::serialize(QDataStream& stream) const{
	stream << _row << _col << _rect << _buffer;
	return stream;
}

QDataStream& ScreenPacket::unserialize(QDataStream& stream){
	stream >> _row >> _col >> _rect >> _buffer;
	return stream;
}

quint64 ScreenPacket::size() const{
	//return 0;
	return sizeof(quint32)*2+sizeof(quint32)*4+sizeof(quint32)+_buffer.size();
	//Seeing the Output It looks like I should add another 8
}

QGraphicsPixmapItem* ScreenPacket::graphicsPixmapItem() const{
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap());
	item->setOffset(_rect.left, _rect.top);
	return item;
}
