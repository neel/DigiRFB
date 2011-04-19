#ifndef COMMONSOCKET_H
#define COMMONSOCKET_H

#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QQueue>
#include "packet.h"

namespace DG{
class CommonSocket : public QTcpSocket{
	Q_OBJECT
	private:
		enum ReadState{
			Header,
			Payload
		};
		ReadState readerState;
		quint8 headerSize;
		quint16 payloadSize;
		QDataStream sockStream;
	private:
		inline quint16 currentReadSize() const{return Header ? headerSize : payloadSize;}
	protected:
		qint64 sentBytes;
		qint64 rcvdBytes;
	protected:
		//QByteArray rcv();
		DG::Packet* rcv();
		//quint64 send(const QByteArray& bytes);
		quint64 send(DG::Packet* packet);
	public:
		CommonSocket(QObject* parent=0);
		virtual ~CommonSocket();
	private:
		//QByteArray _conversationBuffer;
		DG::Packet::CommonHeader* lastHeader;
		QQueue<DG::Packet*> packetQueue;
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
}
#endif // COMMONSOCKET_H
