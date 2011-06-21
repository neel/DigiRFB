#include "mouseeventpacket.h"
#include "util.h"
#include "packet.h"

using namespace DG;

MouseEventPacket::MouseEventPacket():EventPacket(){

}

MouseEventPacket::MouseEventPacket(QEvent::Type type, const QGraphicsSceneMouseEvent* ev):EventPacket(){
	_type = type;
	_point = ev->scenePos().toPoint();
	_button = ev->button();
	_buttons = ev->buttons();
	_modifires = ev->modifiers();
}

MouseEventPacket::MouseEventPacket(QEvent::Type type, const QGraphicsSceneWheelEvent* ev):EventPacket(){
	_type = type;
	_point = ev->scenePos().toPoint();
	_buttons = ev->buttons();
	_modifires = ev->modifiers();
	_delta = ev->delta();
	_orient = ev->orientation();
}

QEvent::Type MouseEventPacket::mouseEventType() const{
	return _type;
}

const QPoint& MouseEventPacket::point() const{
	return _point;
}

void MouseEventPacket::reflect() const{
	if(_type == QEvent::Wheel){
		QWheelEvent* event = new QWheelEvent(_point, _delta, _buttons, _modifires, _orient);
		DG::Util::fireEvent(event);
	}else{
		QMouseEvent* event = new QMouseEvent(_type, _point, _point, _button, _buttons, _modifires);
		DG::Util::fireEvent(event);
	}
}

quint64 MouseEventPacket::size(){
	return (sizeof(int)*4)+(sizeof(qint32)*2);
}

QDataStream& DG::operator<<(QDataStream& stream, const MouseEventPacket& packet){
	stream << packet._type << packet._point << packet._button << packet._buttons << packet._modifires << packet._orient;
	return stream;
}

QDataStream& DG::operator>>(QDataStream& stream, MouseEventPacket& packet){
	int type;
	int button;
	int buttons;
	int modifires;
	int orient;
	stream >> type >> packet._point >> button >> buttons >> modifires >> orient;
	packet._type = (QEvent::Type)type;
	packet._button = (Qt::MouseButton)button;
	packet._buttons = (Qt::MouseButtons)buttons;
	packet._modifires = (Qt::KeyboardModifiers)modifires;
	packet._orient = (Qt::Orientation)orient;
	return stream;
}
