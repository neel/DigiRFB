#ifndef RECT_H
#define RECT_H

#include <QByteArray>
#include <QMutex>

namespace DG;

class Rect{
	private:
		QMutex sMutex;
		QMutex uMutex;
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
};

#endif // RECT_H
