#ifndef EVENTPACKET_H
#define EVENTPACKET_H

#include "packet.h"

namespace DG{
class EventPacket : public Packet{
	public:
		EventPacket(Packet::PacketType type);
	public:
		virtual void reflect() const = 0;
};
}

#endif // EVENTPACKET_H
