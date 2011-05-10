#include "matrixstorageitem.h"
#include "matrixstorage.h"
#include "util.h"
#include "rect.h"
#include <QDebug>
#include "screenpacket.h"

using namespace DG;

MatrixStorageItem::MatrixStorageItem(MatrixStorage* storage, Rect* rect):_storage(storage), rect(rect){

}

MatrixStorageItem::~MatrixStorageItem(){

}

bool MatrixStorageItem::update(){
	QMutexLocker lock(&mutex);
	QImage currentScreen = Util::grabScreen(rect).toImage();
	//qDebug() << "MatrixStorageItem::update() Rect # " << rect->left << rect->top << rect->height << rect->width;
	if(!DG::Util::compare(currentScreen, _cache)){
		//currentPixmap.toImage().save("C:\\scan\\"+QString("%1x%2.jpg").arg(rect->left).arg(rect->top), "JPEG");
		_cache = currentScreen;
		qDebug() << "MatrixStorageItem::update() Unmatched" << rect->left << rect->top << "updated: " << updated << "queueSize: " << _storage->queueSize();
		//if(!updated){
			_storage->setUpdated(this);
		//}
	}else{
		qDebug() << "MatrixStorageItem::update() Matched" << rect->left << rect->top << "queueSize: " << _storage->queueSize();
		//updated = false;
	}
	return updated;
}

ScreenPacket* MatrixStorageItem::packet(int state) const{
	DG::ScreenPacket* screen = new DG::ScreenPacket(state);
	screen->setRect(*rect);
	screen->setImage(_cache);
	return screen;
}
