#include <QWidget>
#include "canvas.h"
#include <QGraphicsSceneMouseEvent>
#include "mouseeventpacket.h"
#include "serversocket.h"
#include <QDebug>
#include "eventdespatcer.h"

using namespace DG;

Canvas::Canvas(QObject *parent):QGraphicsScene(parent){

}

void Canvas::setDespatcher(EventDespatcher* despatcher){
	_despatcher = despatcher;
}

void Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mouseDoubleClickEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonDblClick, event);
	_despatcher->addMouseEvent(packet);
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mouseMoveEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseMove, event);
	_despatcher->addMouseEvent(packet);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mousePressEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonPress, event);
	_despatcher->addMouseEvent(packet);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
	qDebug() << "Canvas::mouseReleaseEvent";
	MouseEventPacket* packet = new MouseEventPacket(QEvent::MouseButtonRelease, event);
	_despatcher->addMouseEvent(packet);
}

void Canvas::setSocket(ServerSocket* socket){
	_socket = socket;
}
