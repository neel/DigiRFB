#ifndef REQUESTCONTROLLER_H
#define REQUESTCONTROLLER_H

#include <QObject>
#include <QMutex>

namespace DG{
	class ClientSocket;
	class MatrixStorage;
}

namespace DG{
class RequestController: public QObject{
	Q_OBJECT
	private:
		QMutex mutex;
	private:
		DG::ClientSocket* _socket;
		DG::MatrixStorage* _storage;
	public:
		RequestController(DG::ClientSocket* socket, DG::MatrixStorage* storage);
	private:
		qint64 requestCount;
	public:
		void request();
	private slots:
		void rectAdded();
	private:
		int packetCount() const;
		void _send();
};
}
#endif // REQUESTCONTROLLER_H
