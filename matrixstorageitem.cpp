#include "matrixstorageitem.h"
#include "matrixstorage.h"
#include "util.h"

using namespace DG;

MatrixStorageItem::MatrixStorageItem(MatrixStorage* storage, Rect* rect):_storage(storage), rect(rect){

}

MatrixStorageItem::~MatrixStorageItem(){

}

bool MatrixStorageItem::update(){
	QMutexLocker lock(&mutex);
	QPixmap currentPixmap = Util::grabScreen(rect);
	if(currentPixmap.toImage() != _cache.toImage()){
		_cache = currentPixmap;
		if(!updated){
			_storage->setUpdated(this);
		}
	}else{
		updated = false;
	}
	return updated;
}
