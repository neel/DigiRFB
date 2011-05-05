#include "matrixstorage.h"
#include "screenpacket.h"
#include "rect.h"
#include "matrixstorageitem.h"
#include "resolution.h"
#include <QMutexLocker>
#include <QDebug>

using namespace DG;

MatrixStorage::MatrixStorage(const DG::Resolution* resolution, quint16 rows, quint16 cols): _rows(rows), _cols(cols){
	items.reserve(rows*cols*sizeof(MatrixStorageItem*));
	quint32 rectHeight = resolution->x()/cols;
	quint32 rectWidth = resolution->y()/rows;
	for(int i=0;i<rows;++i){
		for(int j=0;j<cols;++j){
			qDebug() << "Rect Created :" << i*rectHeight << j*rectWidth << rectWidth << rectHeight;
			Rect* rect = new Rect(i*rectHeight, j*rectWidth, rectWidth, rectHeight);
			MatrixStorageItem* item = new MatrixStorageItem(this, rect);
			items[index(i, j)] = item;
		}
	}
}

MatrixStorage::~MatrixStorage(){
	qDeleteAll(items);
	items.clear();
}

quint32 MatrixStorage::index(quint16 row, quint16 col) const{
	return row*_cols+col;
}

const ScreenPacket* MatrixStorage::packet(quint16 row, quint16 col, int state) const{
	return item(row, col)->packet(state);
}

MatrixStorageItem* MatrixStorage::item(quint16 row, quint16 col) const{
	return items[index(row, col)];
}

void MatrixStorage::setUpdated(MatrixStorageItem* item){
	QMutexLocker lock(&mutex);
	qDebug() << "Updating " << item->rect->left << item->rect->top;
	if(!item->updated){
		item->updated = true;
		item->sent = false;
		queue.enqueue(item);
		emit enqueued();
	}
}

int MatrixStorage::queueSize() const{
	return queue.size();
}

ScreenPacket* MatrixStorage::next(int state){
	QMutexLocker lock(&nMutex);
	qDebug() << "queue.size(): " << queue.size();
	//return queue.dequeue()->rect->packet(state);
	return queue.dequeue()->packet(state);
}
