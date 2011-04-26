#include "matrixstorageitem.h"
#include "matrixstorage.h"
#include "util.h"
#include "rect.h"
#include <QDebug>

using namespace DG;

MatrixStorageItem::MatrixStorageItem(MatrixStorage* storage, Rect* rect):_storage(storage), rect(rect){

}

MatrixStorageItem::~MatrixStorageItem(){

}

bool MatrixStorageItem::update(){
	QMutexLocker lock(&mutex);
	QPixmap currentPixmap = Util::grabScreen(rect);
	qDebug() << "Rect # " << rect->left << rect->top << rect->height << rect->width;
	if(currentPixmap.toImage() != _cache.toImage()){
		_cache = currentPixmap;
		qDebug() << "\t\t" << "Unmatched" << updated;
		if(!updated){
			_storage->setUpdated(this);
		}
	}else{
		updated = false;
	}
	return updated;
}
