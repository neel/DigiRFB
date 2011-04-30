#include "requestcontroller.h"
#include "clientsocket.h"
#include "matrixstorage.h"
#include "screenpacket.h"
#include <QMutexLocker>
#include "updatethread.h"

using namespace DG;
RequestController::RequestController(DG::ClientSocket* socket, DG::MatrixStorage* storage): _socket(socket), _storage(storage), requestCount(0), maxQueueSize(64), minQueueSize(16){
	connect(_storage, SIGNAL(enqueued()), this, SLOT(rectAdded()));
	paused = false;
}

void RequestController::rectAdded(){
	qDebug() << "rectQueueSize: " << packetCount();
	_send();
	if(packetCount() >= maxQueueSize){
		pauseThreads();
	}
}

void RequestController::request(){
	++requestCount;
	_send();
	if(packetCount() <= minQueueSize){
		resumeThreads();
	}
}

int RequestController::packetCount() const{
	return _storage->queueSize();
}

void RequestController::_send(){
	QMutexLocker locker(&mutex);
	if(requestCount > 0 && packetCount() > 0){
		while(requestCount-- > 0){
			_socket->send(_storage->next(10));
		}
		requestCount = 0;
	}
}

void RequestController::addThread(DG::UpdateThread* thread){
	threads << thread;
}

void RequestController::pauseThreads(){
	QMutexLocker locker(&pauseMutex);
	if(!paused){
		foreach(DG::UpdateThread* thread, threads){
			thread->pause();
		}
		paused = true;
	}
}

void RequestController::resumeThreads(){
	QMutexLocker locker(&resumeMutex);
	if(paused){
		foreach(DG::UpdateThread* thread, threads){
			thread->resume();
		}
		paused = false;
	}
}

