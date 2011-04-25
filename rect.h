#ifndef RECT_H
#define RECT_H

#include <QDataStream>
#include <QMutex>

namespace DG{
	class ScreenPacket;
}

namespace DG{
class Rect{
	private:
		static quint8 bytesPerPixel;
	private:
		mutable QMutex sMutex;
		mutable QMutex uMutex;
	public:
		Rect();
		Rect(quint32 left, quint32 top, quint32 width, quint32 height);
		Rect(const DG::Rect& rect);
	public:
		quint32 left;
		quint32 top;
		quint32 width;
		quint32 height;
	public:
		bool valid() const;
		quint32 pixels() const;
		quint64 size() const;
	public:
		Rect& operator=(const Rect& rect);
	public:
		ScreenPacket* packet(int state) const;
	public:
		friend QDataStream& operator<<(QDataStream&, const Rect& rect);
		friend QDataStream& operator>>(QDataStream&, Rect& rect);
};
}
#endif // RECT_H
