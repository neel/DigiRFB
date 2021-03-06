#ifndef MOUSEEVENTPACKET_H
#define MOUSEEVENTPACKET_H

#include "eventpacket.h"
#include <QDataStream>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QPoint>

namespace DG{
class MouseEventPacket : public DG::EventPacket{
	private:
		QEvent::Type _type;
		QPoint _point;
		Qt::MouseButton _button;
		Qt::MouseButtons _buttons;
		Qt::KeyboardModifiers _modifires;
		Qt::Orientation _orient;//WheelEvent
		int _delta;//WheelEvent
	public:
		MouseEventPacket();
		MouseEventPacket(QEvent::Type type, const QGraphicsSceneMouseEvent* ev);
		MouseEventPacket(QEvent::Type type, const QGraphicsSceneWheelEvent* ev);
		QEvent::Type mouseEventType() const;
	public:
		const QPoint& point() const;
	public:
		friend QDataStream& operator<<(QDataStream&, const MouseEventPacket& packet);
		friend QDataStream& operator>>(QDataStream&, MouseEventPacket& packet);
	public:
		void reflect() const;
		static quint64 size();
};
}
#endif // MOUSEEVENTPACKET_H
