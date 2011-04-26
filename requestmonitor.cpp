#include "requestmonitor.h"
#include "packet.h"
#include "clientsocket.h"
#include "matrixstorage.h"

using namespace DG;

void RequestMonitor::setResource(DG::ClientSocket* _socket, DG::MatrixStorage* _storage){
	socket = _socket;
	storage = _storage;
}

RequestMonitor& RequestMonitor::instance(DG::ClientSocket* socket, DG::MatrixStorage* storage){
	if(!RequestMonitor::_instantiated){
		monitor = new RequestMonitor;
		monitor->setResource(socket, storage);
	}
	return *monitor;
}

void RequestMonitor::rectAdded(){
	++rectCount;
	_send();
}

void RequestMonitor::request(){
	++reqCount;
	_send();
}

void RequestMonitor::_send(){
	if(reqCount > 0 && rectCount > 0){
		for(int i=0;i<reqCount;++i){
			socket->send(dynamic_cast<DG::Packet*>(storage->next(10)));
		}
	}
}
