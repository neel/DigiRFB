#ifndef PACKET_H
#define PACKET_H

#include <QDataStream>
#include <QTime>

namespace DG{
class Packet{
	public:
		enum PacketType{
			MessagePacket = 0x02,
			ScreenPacket = 0x04
		};
	public:
		struct CommonHeader{
			private:
				static quint32 _id;
			public:
				quint32 id;
				QTime time;
				quint32 size;
				DG::Packet::PacketType packetType;
			public:
				CommonHeader();
				CommonHeader(quint32 sz, PacketType type);
				friend QDataStream& operator<<(QDataStream&, const Packet::CommonHeader& header);
				friend QDataStream& operator>>(QDataStream&, Packet::CommonHeader& header);
		};
		PacketType type() const;
	private:
		int _state;
	private:
		PacketType _type;
	public:
		Packet();
		Packet(PacketType type, int state);
		virtual QDataStream& serialize(QDataStream& stream) const = 0;
		virtual QDataStream& unserialize(QDataStream& stream) = 0;
	public:
		inline int state() const{return _state;}
		virtual quint64 size() const = 0;
		friend QDataStream& operator<<(QDataStream&, const Packet& packet);
		friend QDataStream& operator>>(QDataStream&, Packet& packet);
};
}
#endif // PACKET_H
