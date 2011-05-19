#ifndef MOUSEEVENTPACKET_H
#define MOUSEEVENTPACKET_H

#include "eventpacket.h"
#include <QDataStream>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

namespace DG{
class MouseEventPacket : public DG::EventPacket{
	private:
		QEvent::Type _type;
		QPoint _point;
		Qt::MouseButton _button;
		Qt::MouseButtons _buttons;
		Qt::KeyboardModifiers _modifires;
	public:
		MouseEventPacket();
		MouseEventPacket(QEvent::Type type, const QGraphicsSceneMouseEvent* ev);
		QEvent::Type mouseEventType() const;
	public:
		const QPoint& point() const;
	public:
		virtual QDataStream& serialize(QDataStream& stream) const;
		virtual QDataStream& unserialize(QDataStream& stream);
	public:
		void reflect() const;
		virtual quint64 size() const;
};
}
#endif // MOUSEEVENTPACKET_H
