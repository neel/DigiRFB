#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "commonsocket.h"

class QGraphicsScene;

namespace DG{
	class Resolution;
}

namespace DG{
class ServerSocket : public CommonSocket{
	Q_OBJECT
	private:
		QGraphicsScene* _scene;
	public:
		ServerSocket(QGraphicsScene* scene, QObject* parent=0);
		virtual ~ServerSocket();
	public:
		void clientConnected();
	private slots:
		void msgReceived();
	private:
		void prepare(const DG::Resolution* resolution);
};
}
#endif // SERVERSOCKET_H
