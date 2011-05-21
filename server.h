#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QThread>

class QGraphicsScene;

namespace DG{
class Server : public QTcpServer{
	Q_OBJECT
	private:
		QThread thread;
		QGraphicsScene* _scene;
	public:
		explicit Server(QGraphicsScene* scene, QObject *parent = 0);
	protected:
		virtual void incomingConnection(int socketDescriptor);
	private slots:
		void addClient();
	public:
		void listen(qint64 port);
};
}

#endif // SERVER_H
