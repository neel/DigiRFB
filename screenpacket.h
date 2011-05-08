#ifndef SCREENPACKET_H
#define SCREENPACKET_H

#include "packet.h"
#include "rect.h"
#include <QByteArray>
#include <QPixmap>
#include <QImage>

class QGraphicsPixmapItem;

namespace DG{
class ScreenPacket : public Packet{
	private:
		quint32 _row;
		quint32 _col;
		Rect _rect;
		QByteArray _buffer;
	private:
		mutable bool _pixmapGenerated;
		mutable QPixmap _pixmap;
	public:
		ScreenPacket();
		ScreenPacket(int state);
		void setRect(const Rect& rect);
		void setIndex(quint32 row, quint32 col);
		void setImage(const QImage& image);
	public:
		quint32 row() const;
		quint32 col() const;
		const Rect& rect() const;
		QPixmap pixmap() const;
	public:
		QDataStream& serialize(QDataStream& stream) const;
		QDataStream& unserialize(QDataStream& stream);
	public:
		virtual quint64 size() const;
	public:
		QGraphicsPixmapItem* graphicsPixmapItem() const;
};
}
#endif // SCREENPACKET_H
