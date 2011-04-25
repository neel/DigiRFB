#include "rectarea.h"
#include "matrixstorage.h"
#include "matrixstorageitem.h"

using namespace DG;

RectArea::RectArea(MatrixStorage* storage):_storage(storage){

}

void RectArea::assignItems(QList<MatrixStorageItem*> items){
	_items = items;
}

void RectArea::update(){
	foreach(MatrixStorageItem* item, _items){
		mutex.lock();
		item->update();
		mutex.unlock();
	}
}
