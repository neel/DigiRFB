#include "keyboardeventpacket.h"

using namespace DG;
KeyboardEventPacket::KeyboardEventPacket():DG::EventPacket(), DG::Packet(){

}

KeyboardEventPacket::KeyboardEventPacket(QEvent::Type type, const  QKeyEvent* keyEvent):DG::EventPacket(), DG::Packet(DG::Packet::KeyboardEventPacket){
	_type = type;
	_key = keyEvent->key();
	_modifiers = keyEvent->modifiers();
	_text = keyEvent->text();
	_autorep = keyEvent->isAutoRepeat();
	_count = keyEvent->count();
}

QEvent::Type KeyboardEventPacket::keyEventType() const{
	return _type;
}

QDataStream& KeyboardEventPacket::serialize(QDataStream& stream) const{
	stream << _type << _key << _modifiers << _text << _autorep << _count;
	return stream;
}

QDataStream& KeyboardEventPacket::unserialize(QDataStream& stream){
	int type_;
	int modifiers_;
	stream >> type_ >> _key >> modifiers_ >> _text >> _autorep >> _count;
	_type = (QEvent::Type)type_;
	_modifiers = (Qt::KeyboardModifiers)modifiers_;
	return stream;
}

void KeyboardEventPacket::reflect() const{

}

quint64 KeyboardEventPacket::size() const{
	return sizeof(*this)-sizeof(_text)+_text.size();
}
