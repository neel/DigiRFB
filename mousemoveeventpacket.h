#ifndef MOUSEMOVEEVENTPACKET_H
#define MOUSEMOVEEVENTPACKET_H

#include "mouseeventpacket.h"

namespace DG{
class MouseMoveEventPacket : public DG::MouseEventPacket{
	public:
    MouseMoveEventPacket();
		MouseMoveEventPacket(quint16 x, quint16 y);
	public:
		virtual void reflect() const;
};
}
#endif // MOUSEMOVEEVENTPACKET_H
