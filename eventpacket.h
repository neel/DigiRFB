#ifndef EVENTPACKET_H
#define EVENTPACKET_H

#include "packet.h"

namespace DG{
class EventPacket : public Packet{
	public:
		enum EventType{
			KeyboardEvent = 0x02,
			MouseEvent = 0x04
		};
	private:
		EventType _eventType;
	public:
		EventPacket();
		EventPacket(EventType type, int state);
		EventPacket(EventType type);
	public:
		virtual QDataStream& serialize(QDataStream& stream) const;
		virtual QDataStream& unserialize(QDataStream& stream);
	public:
		virtual void reflect() const;
	public:
		virtual quint64 size() const;
	public:
		EventType eventType() const;
};
}

#endif // EVENTPACKET_H
