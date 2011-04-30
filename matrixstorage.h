#ifndef MATRIXSTORAGE_H
#define MATRIXSTORAGE_H

#include <QQueue>
#include <QHash>
#include <QPixmap>
#include <QMutex>

namespace DG{
	class Resolution;
	class ScreenPacket;
	class Rect;
	class MatrixStorageItem;
	class UpdateThread;
}

namespace DG{
/**
	* Should be Sigleton
	*/
class MatrixStorage: public QObject{
	Q_OBJECT
	private:
		QMutex mutex;
		QMutex nMutex;
	private:
		QQueue<MatrixStorageItem*> queue;
	private:
		quint16 _rows;
		quint16 _cols;
		QHash<quint32, MatrixStorageItem*> items;
	public:
		MatrixStorage(const DG::Resolution* resolution, quint16 rows, quint16 cols);
		virtual ~MatrixStorage();
	public:
		const ScreenPacket* packet(quint16 row, quint16 col, int state) const;
		MatrixStorageItem* item(quint16 row, quint16 col) const;
	private:
		quint32 index(quint16 row, quint16 col) const;
	public:
		void setUpdated(MatrixStorageItem* item);
	public:
		int queueSize() const;
		ScreenPacket* next(int state);
	signals:
		void enqueued();
};
}
#endif // MATRIXSTORAGE_H
