#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>

namespace DG{
	class ServerSocket;
}
class QGraphicsSceneMouseEvent;

namespace DG{
class Canvas : public QGraphicsScene{
	Q_OBJECT
	private:
		ServerSocket* _socket;
	public:
		explicit Canvas(QObject* parent = 0);
	public:
		virtual void	mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
		virtual void	mouseMoveEvent(QGraphicsSceneMouseEvent* event);
		virtual void	mousePressEvent(QGraphicsSceneMouseEvent* event);
		virtual void	mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	public:
		void setSocket(ServerSocket* socket);
};
}

#endif // CANVAS_H
