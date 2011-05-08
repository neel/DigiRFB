#include "rect.h"
#include "util.h"
#include "screenpacket.h"

using namespace DG;

Rect::Rect(){

}

Rect::Rect(quint32 left=0, quint32 top=0, quint32 width=0, quint32 height=0):left(left),top(top),width(width),height(height){

}

Rect::Rect(const DG::Rect& rect){
	left = rect.left;
	top = rect.top;
	width = rect.width;
	height = rect.height;
}

quint32 Rect::pixels() const{
	return height*width;
}

bool Rect::valid() const{
	return pixels() != 0;
}

quint64 Rect::size() const{
	return pixels()*bytesPerPixel;
}

Rect& Rect::operator=(const Rect& rect){
	left = rect.left;
	top = rect.top;
	width = rect.width;
	height = rect.height;
	return *this;
}

ScreenPacket* Rect::packet(int state) const{
	qWarning("Should not be Called!!");
	/*
	DG::ScreenPacket* screen = new DG::ScreenPacket(state);
	screen->setRect(*this);
	screen->setImage(DG::Util::grabScreen(this));
	*/
	//return screen;
	return 0x0;
}

QDataStream& DG::operator<<(QDataStream& stream, const Rect& rect){
	stream << rect.left << rect.top << rect.width << rect.height;
	return stream;
}

QDataStream& DG::operator>>(QDataStream& stream, Rect& rect){
	stream >> rect.left >> rect.top >> rect.width >> rect.height;
	return stream;
}

QRect Rect::toQRect() const{
	return QRect(left, top, width, height);
}

quint8 Rect::bytesPerPixel = 4;
