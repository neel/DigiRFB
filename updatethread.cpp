#include "updatethread.h"
#include "rectarea.h"
#include <QTimer>
#include <QDebug>
#include <QMutexLocker>
#include "matrixstorage.h"
#include "requestcontroller.h"
#include <QThreadPool>
#include <assert.h>

using namespace DG;
UpdateThread::UpdateThread(DG::RectArea* area): _area(area){
	setAutoDelete(false);
}

void UpdateThread::run(){
	QMutexLocker locker(&mutex);
	//qDebug() << this << "UpdateThread::run()";
	if(_area->storage()->queueSize() < RequestController::maxQueueSize)
		_area->update();
	else
		qDebug() << "_area->storage()->queueSize() Overflow Production Paused" << _area->storage()->queueSize() << RequestController::maxQueueSize;
	qDebug() << "Starting " << _next;
	QThreadPool::globalInstance()->start(this);
}

void UpdateThread::setNext(DG::UpdateThread* thread){
	assert(thread != 0x0);
	_next = thread;
}

