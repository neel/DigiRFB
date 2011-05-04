#include "updatethread.h"
#include "rectarea.h"
#include <QTimer>
#include <QDebug>
#include <QMutexLocker>
#include "matrixstorage.h"
#include "requestcontroller.h"

using namespace DG;
UpdateThread::UpdateThread(DG::RectArea* area, QObject *parent):QThread(parent), _area(area){

}

void UpdateThread::run(){
	timer = new QTimer();
	timer->setSingleShot(false);
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer->start(1000);
	exec();
}

void UpdateThread::tick(){
	QMutexLocker locker(&mutex);
	qDebug() << currentThread() << "tick";
	if(_area->storage()->queueSize() < RequestController::maxQueueSize)
		_area->update();
}

