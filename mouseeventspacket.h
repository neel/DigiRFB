#ifndef MOUSEEVENTSPACKET_H
#define MOUSEEVENTSPACKET_H

#include "packet.h"
#include <QList>

namespace DG{
	class MouseEventPacket;
}

namespace DG{
class MouseEventsPacket : public Packet{
	private:
		QList<DG::MouseEventPacket*> _packets;
	public:
		MouseEventsPacket();
		MouseEventsPacket(QList<DG::MouseEventPacket*> packets);
		~MouseEventsPacket();
	public:
		virtual QDataStream& serialize(QDataStream& stream) const;
		virtual QDataStream& unserialize(QDataStream& stream);
	public:
		void reflect();
		virtual quint64 size() const;
};
}
#endif // MOUSEEVENTSPACKET_H
