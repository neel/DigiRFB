#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "commonsocket.h"

namespace DG{
	class MatrixStorage;
	class Resolution;
}

namespace DG{
class ClientSocket : public CommonSocket{
	Q_OBJECT
	private:
		MatrixStorage* storage;
		const quint8 divisionRows;
		const quint8 divisionCols;
		const quint8 rectRows;
		const quint8 rectCols;
	public:
		ClientSocket(QObject* parent=0);
		virtual ~ClientSocket();
	private slots:
		void msgReceived();
	private:
		void prepare(DG::Resolution* resolution);
};
}
#endif // CLIENTSOCKET_H
