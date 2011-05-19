#include <QWidget>
#include "canvas.h"
#include <QGraphicsSceneMouseEvent>
#include "mouseeventpacket.h"
#include "serversocket.h"
#include <QDebug>

using namespace DG;

Canvas::Canvas(QObject *parent):QGraphicsScene(parent){

}

void Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mouseDoubleClickEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonDblClick, event);
	//_socket->send(packet);
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mouseMoveEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseMove, event);
	//_socket->send(packet);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mousePressEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonPress, event);
	_socket->send(packet);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mouseReleaseEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonRelease, event);
	//_socket->send(packet);
}

void Canvas::setSocket(ServerSocket* socket){
	_socket = socket;
}
