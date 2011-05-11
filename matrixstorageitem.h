#ifndef MATRIXSTORAGEITEM_H
#define MATRIXSTORAGEITEM_H

#include <QImage>
#include <QMutex>
#include <QMutexLocker>

namespace DG{
	class MatrixStorage;
	class Rect;
	class ScreenPacket;
}

namespace DG{
struct MatrixStorageItem{
	private:
		QMutex mutex;
	private:
		MatrixStorage* _storage;
	public:
		quint16 _row;
		quint16 _col;
		bool sent;
		bool updated;
		Rect* rect;
		QImage _cache;
	public:
		MatrixStorageItem(MatrixStorage* storage, Rect* rect);
		virtual ~MatrixStorageItem();
	public:
		bool update();
	public:
		void setIndex(quint16 row, quint16 col);
		ScreenPacket* packet(int state) const;
};
}
#endif // MATRIXSTORAGEITEM_H
