#include "requestcontroller.h"
#include "clientsocket.h"
#include "matrixstorage.h"
#include "screenpacket.h"

using namespace DG;
RequestController::RequestController(DG::ClientSocket* socket, DG::MatrixStorage* storage): _socket(socket), _storage(storage){
	connect(_storage, SIGNAL(enqueued()), this, SLOT(rectAdded()));
}

void RequestController::rectAdded(){
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
	if(requestCount > 0 && packetCount() > 0){
		while(requestCount-- > 0){
			_socket->send(_storage->next(10));
		}
	}
}
