#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>

namespace DG{
	class ServerSocket;
	class EventDespatcher;
}
class QGraphicsSceneMouseEvent;

namespace DG{
class Canvas : public QGraphicsScene{
	Q_OBJECT
	private:
		ServerSocket* _socket;
		EventDespatcher* _despatcher;
	public:
		explicit Canvas(QObject* parent = 0);
		void setDespatcher(EventDespatcher* despatcher);
	public:
		virtual void	mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
		virtual void	mouseMoveEvent(QGraphicsSceneMouseEvent* event);
		virtual void	mousePressEvent(QGraphicsSceneMouseEvent* event);
		virtual void	mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
		virtual void 	keyPressEvent(QKeyEvent * keyEvent);
		virtual void 	keyReleaseEvent(QKeyEvent * keyEvent);
	public:
		void setSocket(ServerSocket* socket);
};
}

#endif // CANVAS_H
