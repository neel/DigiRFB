#include "mouseeventpacket.h"
#include "util.h"

using namespace DG;

MouseEventPacket::MouseEventPacket():EventPacket(EventPacket::MouseEvent){

}

MouseEventPacket::MouseEventPacket(QEvent::Type type, const QGraphicsSceneMouseEvent* ev):EventPacket(EventPacket::MouseEvent){
	_type = type;
	_point = ev->scenePos().toPoint();
	_button = ev->button();
	_buttons = ev->buttons();
	_modifires = ev->modifiers();
}

QEvent::Type MouseEventPacket::mouseEventType() const{
	return _type;
}

const QPoint& MouseEventPacket::point() const{
	return _point;
}

QDataStream& MouseEventPacket::serialize(QDataStream& stream) const{
	EventPacket::serialize(stream);
	stream << _type << _point << _button << _buttons << _modifires;
	return stream;
}

QDataStream& MouseEventPacket::unserialize(QDataStream& stream){
	EventPacket::serialize(stream);
	int type;
	int button;
	int buttons;
	int modifires;
	stream >> type >> _point >> button >> buttons >> modifires;
	_type = (QEvent::Type)type;
	_button = (Qt::MouseButton)button;
	_buttons = (Qt::MouseButtons)buttons;
	_modifires = (Qt::KeyboardModifiers)modifires;
	return stream;
}

void MouseEventPacket::reflect() const{
	QMouseEvent* event = new QMouseEvent(_type, _point, _point, _button, _buttons, _modifires);
	DG::Util::fireEvent(event);
}

quint64 MouseEventPacket::size() const{
	return EventPacket::size()+sizeof(int)*4+sizeof(qint32)*2;
}
