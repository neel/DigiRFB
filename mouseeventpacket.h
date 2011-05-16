#ifndef MOUSEEVENTPACKET_H
#define MOUSEEVENTPACKET_H

#include "eventpacket.h"
#include <QDataStream>

namespace DG{
class MouseEventPacket : public DG::EventPacket{
	private:
		quint16 _x;
		quint16 _y;
	public:
		enum MouseEventType{
			MouseMove = 0x02,
			MouseClick = 0x04
		};
	private:
		MouseEventType _mouseEventType;
	public:
		MouseEventPacket(MouseEventType mouseEventType);
		MouseEventPacket(MouseEventType mouseEventType, quint16 x, quint16 y);
		MouseEventType mouseEventType() const;
	public:
		quint16 x() const;
		quint16 y() const;
	public:
		virtual QDataStream& serialize(QDataStream& stream) const;
		virtual QDataStream& unserialize(QDataStream& stream);
};
}
#endif // MOUSEEVENTPACKET_H
