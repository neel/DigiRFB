#include "requestcontroller.h"
#include "clientsocket.h"
#include "matrixstorage.h"
#include "screenpacket.h"
#include <QMutexLocker>
#include "updatethread.h"
#include <QApplication>
#include <QDebug>

using namespace DG;
RequestController::RequestController(DG::ClientSocket* socket, DG::MatrixStorage* storage): _socket(socket), _storage(storage), requestCount(0), packetC(0), ackC(0){
	connect(_storage, SIGNAL(enqueued()), this, SLOT(rectAdded()));
}

void RequestController::rectAdded(){
	qDebug() << "rectQueueSize: " << packetCount();
	_send();
}

void RequestController::request(){
	++requestCount;
	qDebug() << "Requested " << requestCount;
	if(requestCount >= 0)
		_send();
}

int RequestController::packetCount() const{
	return _storage->queueSize();
}

void RequestController::_send(){	
	QMutexLocker locker(&mutex);
	qDebug() << "requestCount" << requestCount << "packetCount(): " << packetCount();
	if(requestCount > 0 && packetCount() > 0){
		qDebug() << "requestCount" << requestCount;
		while(requestCount-- > 0){
			DG::ScreenPacket* packet = _storage->next(10);
			//packet->pixmap().toImage().save("C:\\scan\\"+QString("%1x%2.jpg").arg(packet->rect().left).arg(packet->rect().top), "JPEG");
			_socket->send(packet);
			packetSent();
			delete packet;
			//QApplication::beep();
		}
		requestCount = 0;
	}

	if(requestCount >= 0){
		qDebug() << "packetCount(): " << packetCount();
		if(packetCount() >= RequestController::maxQueueSize){
			while(packetCount() >= RequestController::minQueueSize){
				DG::ScreenPacket* packet = _storage->next(10);
				//packet->pixmap().toImage().save("C:\\scan\\"+QString("%1x%2.jpg").arg(packet->rect().left).arg(packet->rect().top), "JPEG");
				_socket->send(packet);
				delete packet;
				QApplication::beep();
				--requestCount;
				qDebug() << "Forcing " << requestCount;
			}
		}
	}

}

void RequestController::addThread(DG::UpdateThread* thread){
	threads << thread;
	if(threads.count() > 1){
		threads.at(threads.count()-2)->setNext(thread);
		qDebug() << "RequestController::addThread()" << threads.at(threads.count()-2) << thread;
	}
}

void RequestController::allThreadsAdded(){
	threads.at(threads.count()-1)->setNext(threads.at(0));
}

void RequestController::packetSent(){
	++packetC;
}

void RequestController::acknowledged(){
	++ackC;
}

const quint8 RequestController::minQueueSize = 4;
const quint8 RequestController::maxQueueSize = 8;
