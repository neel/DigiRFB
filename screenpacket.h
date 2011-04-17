#ifndef SCREENPACKET_H
#define SCREENPACKET_H

#include "packet.h"
#include <QByteArray>

namespace DG{
class ScreenPacket : public Packet{
	private:
		quint32 _row;
		quint32 _col;
		quint32 _left;
		quint32 _top;
		quint32 _width;
		quint32 _height;
		QByteArray _buffer;
	public:
		ScreenPacket(int state);
		void setPosition(quint32 left, quint32 top);
		void setSize(quint32 width, quint32 height);
		void setIndex(quint32 row, quint32 col);
		void setBuffer(const QByteArray& buffer);
	public:
		quint32 row() const;
		quint32 col() const;
		quint32 left() const;
		quint32 top() const;
		quint32 width() const;
		quint32 height() const;
		const QByteArray& buffer() const;
	public:
		QDataStream& serialize(QDataStream& stream) const;
		QDataStream& unserialize(QDataStream& stream);
};
}
#endif // SCREENPACKET_H
