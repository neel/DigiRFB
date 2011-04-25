#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class QGraphicsScene;

namespace DG{
class Server : public QTcpServer{
	Q_OBJECT
	private:
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
