#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "commonsocket.h"

namespace DG{
class ClientSocket : public CommonSocket{
	Q_OBJECT
	public:
		ClientSocket(QObject* parent=0);
		virtual ~ClientSocket();
	private slots:
		void msgReceived();
};
}
#endif // CLIENTSOCKET_H
