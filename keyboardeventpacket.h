#ifndef KEYBOARDEVENTPACKET_H
#define KEYBOARDEVENTPACKET_H

#include "eventpacket.h"
#include <QKeyEvent>
#include "packet.h"

namespace DG{
class KeyboardEventPacket : public DG::EventPacket, public DG::Packet{
	private:
		QEvent::Type _type;
		int _key;
		Qt::KeyboardModifiers _modifiers;
		QString _text;
		bool _autorep;
		ushort _count;
	public:
    KeyboardEventPacket();
		KeyboardEventPacket(QEvent::Type type, const QKeyEvent* keyEvent);
		QEvent::Type keyEventType() const;
	public:
		virtual QDataStream& serialize(QDataStream& stream) const;
		virtual QDataStream& unserialize(QDataStream& stream);
	public:
		void reflect() const;
		quint64 size() const;
};
}
#endif // KEYBOARDEVENTPACKET_H
