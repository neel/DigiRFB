#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

namespace DG{
class Server : public QTcpServer{
	Q_OBJECT
	public:
    explicit Server(QObject *parent = 0);
	protected:
		virtual void incomingConnection(int socketDescriptor);
	private slots:
		void addClient();
	public:
		void listen(qint64 port);
};
}

#endif // SERVER_H
