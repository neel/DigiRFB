#include "rectarea.h"
#include "matrixstorage.h"
#include "matrixstorageitem.h"
#include <QDebug>

using namespace DG;

RectArea::RectArea(MatrixStorage* storage):_storage(storage){

}

void RectArea::assignItems(QList<MatrixStorageItem*> items){
	_items = items;
	//qDebug() << "RectArea::assignItems: " << _items.count();
}

void RectArea::update(){
	foreach(MatrixStorageItem* item, _items){
		mutex.lock();
		item->update();
		mutex.unlock();
	}
}

MatrixStorage* RectArea::storage() const{
	return _storage;
}
