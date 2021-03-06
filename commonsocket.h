#ifndef COMMONSOCKET_H
#define COMMONSOCKET_H

#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QQueue>
#include "packet.h"
#include <QMutex>

namespace DG{
class CommonSocket : public QTcpSocket{
	Q_OBJECT
	private:
		QMutex sendMutex;
		QMutex rcvMutex;
		QMutex readMutex;
	private:
		enum ReadState{
			Header,
			Payload
		};
		ReadState readerState;
		quint8 headerSize;
        quint32 payloadSize;
		QDataStream sockStream;
	private:
        quint32 currentReadSize() const;
	protected:
		qint64 sentBytes;
		qint64 rcvdBytes;
	public:
		DG::Packet* rcv();
		quint64 send(DG::Packet* packet);
	public:
		CommonSocket(QObject* parent=0);
		virtual ~CommonSocket();
	private:
		DG::Packet::CommonHeader* lastHeader;
		QQueue<DG::Packet*> packetQueue;
	protected:
		DG::Packet::PacketType lastHeaderType() const;
	private slots:
		void stateChangedSlot(QAbstractSocket::SocketState socketState);
		void readAvailableSlot();
	protected:
		enum State{
			Connected = 1,
			Hi = 2,
			Hallo = 3,
			Welcome = 4,
			Challange = 5,
			Password = 6,
			Resolution = 7,
			ResolutionAccepted = 8,
			Prepared = 9,
			Start = 10,
			Working = 11,
			ACK = 12,
			Trap = 13
		};
	protected:
		State state;
	public:
		virtual State currentState();
	signals:
		void msgWaiting();
};
}
#endif // COMMONSOCKET_H
