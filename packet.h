#ifndef PACKET_H
#define PACKET_H

#include <QDataStream>
#include <QTime>

namespace DG{
class Packet{
	public:
		struct CommonHeader{
			private:
				static quint32 _id;
			public:
				quint32 id;
				QTime time;
				quint32 size;
			public:
				CommonHeader(quint32 sz);
		};
	private:
		int _state;
	public:
		Packet(int state);
		virtual QDataStream& serialize(QDataStream& stream) const = 0;
		virtual QDataStream& unserialize(QDataStream& stream) = 0;
	public:
		inline int state() const{return _state;}
};

QDataStream& operator<<(QDataStream&, const DG::Packet::CommonHeader& header);
QDataStream& operator>>(QDataStream&, const DG::Packet::CommonHeader& header);
QDataStream& operator<<(QDataStream&, const DG::Packet& packet);
QDataStream& operator>>(QDataStream&, const DG::Packet& packet);
}
#endif // PACKET_H
