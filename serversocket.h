#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "commonsocket.h"

namespace DG{
class ServerSocket : public CommonSocket{
	Q_OBJECT
	public:
		ServerSocket(QObject* parent=0);
		virtual ~ServerSocket();
	public:
		void clientConnected();
	private slots:
		void msgReceived();
};
}
#endif // SERVERSOCKET_H
