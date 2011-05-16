#include "mousemoveeventpacket.h"
#include "util.h"
using namespace DG;
MouseMoveEventPacket::MouseMoveEventPacket():MouseEventPacket(MouseEventPacket::MouseMove){

}

MouseMoveEventPacket::MouseMoveEventPacket(quint16 x, quint16 y):MouseEventPacket(MouseEventPacket::MouseMove, x, y){

}

void MouseMoveEventPacket::reflect() const{

}
