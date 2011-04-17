#ifndef MESSAGEPACKET_H
#define MESSAGEPACKET_H

#include "packet.h"
#include <QByteArray>

namespace DG{
class MessagePacket: public Packet{
	private:
		QByteArray _msg;
	public:
		MessagePacket(int state);
		void setMessage(QByteArray msg);
		QByteArray message() const;
	public:
		QDataStream& serialize(QDataStream& stream) const;
		QDataStream& unserialize(QDataStream& stream);
};
}
#endif // MESSAGEPACKET_H
