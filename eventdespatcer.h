#ifndef EVENTDESPATCER_H
#define EVENTDESPATCER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QMutex>

namespace DG{
	class MouseEventPacket;
	class ServerSocket;
	class KeyboardEventPacket;
}


namespace DG{
class EventDespatcher : public QObject{
	Q_OBJECT
	private:
		QMutex mutex;
		QTimer timer;
		QList<MouseEventPacket*> packets;
		DG::ServerSocket* _socket;
	public:
		explicit EventDespatcher(DG::ServerSocket* socket, QObject *parent = 0);
	private slots:
		void despatch();
	public:
		void addMouseEvent(MouseEventPacket* packet);
		void addKeyboardEvent(KeyboardEventPacket* packet);
};
}
#endif // EVENTDESPATCER_H
