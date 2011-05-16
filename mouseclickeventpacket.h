#ifndef MOUSECLICKEVENTPACKET_H
#define MOUSECLICKEVENTPACKET_H

#include "mouseeventpacket.h"

namespace DG{
class MouseClickEventPacket : public DG::MouseEventPacket{
	private:
		enum MouseClickType{
			LeftClick = 0x02,
			RightClick = 0x04,
			MiddleClick = 0x08
		};
	public:
		MouseClickEventPacket();
};
}
#endif // MOUSECLICKEVENTPACKET_H
