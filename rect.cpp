#include "rect.h"
#include <QDataStream>

Rect::Rect(quint32 left, quint32 top, quint32 width, quint32 height):left(left),top(top),width(width),height(height){

}

QByteArray Rect::serialize() const{
	sMutex.lock();
	QByteArray buff;
	QDataStream stream(&buff, QIODevice::ReadWrite);
	stream.setVersion(QDataStream::Qt_4_7);
	stream << row << col << left << top;
	stream << height << width;
	stream >> buffer.size();
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
