#include "eventdespatcer.h"
#include "serversocket.h"
#include "mouseeventpacket.h"
#include "mouseeventspacket.h"
#include "keyboardeventpacket.h"
#include <QMutexLocker>

using namespace DG;
EventDespatcher::EventDespatcher(DG::ServerSocket* socket, QObject *parent):QObject(parent), _socket(socket){
	packets.clear();
	timer.setInterval(1000);
	connect(&timer, SIGNAL(timeout()), this, SLOT(despatch()));
	timer.start();
}

void EventDespatcher::despatch(){
	QMutexLocker locker(&mutex);
	if(packets.size() > 0){
		DG::MouseEventsPacket* packet = new DG::MouseEventsPacket(packets);
		_socket->send(packet);
		//emit mouseEventsPacketReady(packet);
		packets.clear();
	}
}

void EventDespatcher::addMouseEvent(MouseEventPacket* packet){
	QMutexLocker locker(&mutex);
	packets << packet;
}

void EventDespatcher::addKeyboardEvent(KeyboardEventPacket* packet){
	QMutexLocker locker(&mutex);
	_socket->send(packet);
}
