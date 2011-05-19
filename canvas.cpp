#include <QWidget>
#include "canvas.h"
#include <QGraphicsSceneMouseEvent>
#include "mouseeventpacket.h"
#include "serversocket.h"

using namespace DG;

Canvas::Canvas(QObject *parent):QGraphicsScene(parent){

}

void Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonDblClick, event);
	_socket->send(packet);
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseMove, event);
	_socket->send(packet);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event){
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonPress, event);
	_socket->send(packet);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonRelease, event);
	_socket->send(packet);
}

void Canvas::setSocket(ServerSocket* socket){
	_socket = socket;
}
