#ifndef MATRIXSTORAGEITEM_H
#define MATRIXSTORAGEITEM_H

#include <QPixmap>
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
		bool sent;
		bool updated;
		Rect* rect;
		QPixmap _cache;
	public:
		MatrixStorageItem(MatrixStorage* storage, Rect* rect);
		virtual ~MatrixStorageItem();
	public:
		bool update();
	public:
		ScreenPacket* packet(int state) const;
};
}
#endif // MATRIXSTORAGEITEM_H
