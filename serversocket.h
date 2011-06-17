#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "commonsocket.h"

class QGraphicsScene;

namespace DG{
	class Resolution;
	class SceneMatrix;
	class ConfirmPasswordDialog;
	class MouseEventsPacket;
}

namespace DG{
class ServerSocket : public CommonSocket{
	Q_OBJECT
	private:
		DG::ConfirmPasswordDialog* dlg;
	private:
		QGraphicsScene* _scene;
		SceneMatrix* _matrix;
	public:
		ServerSocket(QGraphicsScene* scene, QObject* parent=0);
		virtual ~ServerSocket();
	public:
		void clientConnected();
	private slots:
		void msgReceived();
	private:
		void prepare(const DG::Resolution* resolution);
	private slots:
		void confirmed(const QString& pass);
	public slots:
		void mouseEventPacketsWaiting(DG::MouseEventsPacket* packet);
};
}
#endif // SERVERSOCKET_H
