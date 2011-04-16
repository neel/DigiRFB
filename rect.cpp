#include "rect.h"
#include <QDataStream>
#include <QDebug>

using namespace DG;

Rect::Rect(quint32 left=0, quint32 top=0, quint32 width=0, quint32 height=0):left(left),top(top),width(width),height(height){

}

QByteArray Rect::serialize() const{
	sMutex.lock();
	QByteArray buff;
	QDataStream stream(&buff, QIODevice::ReadWrite);
	stream.setVersion(QDataStream::Qt_4_7);
	stream << row << col << left << top;
	stream << height << width;
	stream << buffer.size();
	stream << buffer;
	sMutex.unlock();
	return buff;
}

void Rect::unserialize(const QByteArray& bytes){
	uMutex.lock();
	int size;
	buffer.clear();
	QDataStream stream(bytes);
	stream.setVersion(QDataStream::Qt_4_7);
	stream >> row >> col >> left >> top;
	stream >> height >> width;
	stream >> size;
	stream >> buffer;
	qDebug() << "Unserializing : " << row << col << left << top << width << height << size;
	uMutex.unlock();
}

Rect* Rect::parse(QByteArray rawBuff){
	qDebug() << "Parsing : " << rawBuff.toHex();
	DG::Rect* rect = new DG::Rect;
	rect->unserialize(rawBuff);
	return rect;
}

quint32 Rect::pixels() const{
	return height*width;
}

bool Rect::valid() const{
	return pixels() != 0;
}

quint64 Rect::size() const{
	return pixels()*bytesPerPixel;
}

quint8 Rect::bytesPerPixel = 4;
