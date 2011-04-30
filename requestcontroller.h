#ifndef REQUESTCONTROLLER_H
#define REQUESTCONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QList>

namespace DG{
	class ClientSocket;
	class MatrixStorage;
	class UpdateThread;
}

namespace DG{
class RequestController: public QObject{
	Q_OBJECT
	private:
		const quint8 maxQueueSize;
		const quint8 minQueueSize;
	private:
		QList<UpdateThread*> threads;
	private:
		QMutex mutex;
		QMutex pauseMutex;
		QMutex resumeMutex;
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
	public:
		void addThread(DG::UpdateThread* thread);
		void pauseThreads();
		void resumeThreads();
};
}
#endif // REQUESTCONTROLLER_H
