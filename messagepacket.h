#ifndef MESSAGEPACKET_H
#define MESSAGEPACKET_H

#include "packet.h"
#include <QByteArray>

namespace DG{
class MessagePacket: public Packet{
	private:
		QByteArray _msg;
	public:
		MessagePacket();
		MessagePacket(int state);
		void setMessage(QByteArray msg);
		QByteArray message() const;
	public:
		QDataStream& serialize(QDataStream& stream) const;
		QDataStream& unserialize(QDataStream& stream);
	public:
		virtual quint64 size() const;
};
}
#endif // MESSAGEPACKET_H
