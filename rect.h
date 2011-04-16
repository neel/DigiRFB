#ifndef RECT_H
#define RECT_H

#include <QByteArray>
#include <QMutex>

namespace DG{

class Rect{
	private:
		static quint8 bytesPerPixel;
	private:
		mutable QMutex sMutex;
		mutable QMutex uMutex;
	public:
		Rect(quint32 left, quint32 top, quint32 width, quint32 height);
	public:
		quint32 left;
		quint32 top;
		quint32 width;
		quint32 height;
		quint32 row;
		quint32 col;
		QByteArray buffer;
	public:
		void unserialize(const QByteArray& bytes);
		QByteArray serialize() const;
	public:
		static Rect* parse(QByteArray rawBuff);
	public:
		bool valid() const;
		quint32 pixels() const;
		quint64 size() const;
};
}
#endif // RECT_H
