#ifndef COMMONSOCKET_H
#define COMMONSOCKET_H

#include <QTcpSocket>

class CommonSocket : public QTcpSocket{
	Q_OBJECT
	private:
		const char SeparatorToken;
		quint8 unreadyBytes;
	protected:
		qint64 sentBytes;
		qint64 rcvdBytes;
	protected:
		QByteArray rcv();
		qint64 send(const QByteArray& bytes);
	public:
		CommonSocket(QObject* parent=0);
		virtual ~DGRDPSocket();
	private:
		QByteArray _conversationBuffer;
	private slots:
		void readAvailableSlot();
	protected:
		enum State{
			Connected = 1,
			Hi = 2,
			Hallo = 3,
			Welcome = 4,
			Challange = 5,
			Password = 6,
			Accepted = 7,
			Resolution = 8,
			ResolutionAccepted = 9,
			Prepared = 10,
			Start = 11,
			Working = 12,
			ACK = 13,
			Trap = 14
		};
	protected:
		State state;
	public:
		virtual State currentState();
	signals:
		void msgWaiting();
};

#endif // COMMONSOCKET_H
