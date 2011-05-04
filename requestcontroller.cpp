#include "requestcontroller.h"
#include "clientsocket.h"
#include "matrixstorage.h"
#include "screenpacket.h"
#include <QMutexLocker>
#include "updatethread.h"

using namespace DG;
RequestController::RequestController(DG::ClientSocket* socket, DG::MatrixStorage* storage): _socket(socket), _storage(storage), requestCount(0){
	connect(_storage, SIGNAL(enqueued()), this, SLOT(rectAdded()));
}

void RequestController::rectAdded(){
	qDebug() << "rectQueueSize: " << packetCount();
	_send();
}

void RequestController::request(){
	++requestCount;
	_send();
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

const quint8 RequestController::minQueueSize = 16;
const quint8 RequestController::maxQueueSize = 64;
