#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "commonsocket.h"
#include <QByteArray>

namespace DG{
	class MatrixStorage;
	class Resolution;
	class RequestController;
}

namespace DG{
class ClientSocket : public CommonSocket{
	Q_OBJECT
	private:
		RequestController* controller;
	private:
		MatrixStorage* storage;
		const quint8 divisionCols;
		const quint8 divisionRows;
		const quint8 rectCols;
		const quint8 rectRows;
	private:
		QByteArray passwordChecksum;
	public:
		ClientSocket(QObject* parent=0);
		virtual ~ClientSocket();
	private slots:
		void msgReceived();
	private:
		void prepare(DG::Resolution* resolution);
	private slots:
		void challanged(const QString& pass);
};
}
#endif // CLIENTSOCKET_H
