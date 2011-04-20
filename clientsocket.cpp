#include "clientsocket.h"
#include "packet.h"
#include "messagepacket.h"
#include "screenpacket.h"
#include "resolution.h"
#include "util.h"
#include <QList>
#include <QDebug>

using namespace DG;

ClientSocket::ClientSocket(QObject* parent):CommonSocket(parent){
	connect(this, SIGNAL(msgWaiting()), this, SLOT(msgReceived()));
}

ClientSocket::~ClientSocket(){

}

void ClientSocket::msgReceived(){
	DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(rcv());
	switch(currentState()){
		case Connected:{
				if(m->message().startsWith("hi")){
					DG::MessagePacket* res = new DG::MessagePacket((int)Connected);
					res->setMessage("hallo|SerialKey");
					send(res);
					state = Hallo;
				}
			}break;
		case Hallo:{
				if(m->message().startsWith("welcome")){
					DG::MessagePacket* res = new DG::MessagePacket((int)Hallo);
					res->setMessage("challange");
					send(res);
					state = Challange;
				}
			}break;
		case Challange:{
				if(m->message().startsWith("password")){
					QList<QByteArray> parts = m->message().split('|');
					QByteArray serverPass = parts[1];
					qDebug() << "$ Password recieved from Server: "+serverPass;
					//Compare Passwords
					DG::MessagePacket* res = new DG::MessagePacket((int)Challange);
					QByteArray currentResdolution = Util::currentResolution()->pack();
					QByteArray supportedResolutions = Resolution::joinSupportedResolutions(Util::SupportedResolutions(), ',');
					res->setMessage("res "+currentResdolution+"|"+supportedResolutions);
					send(res);
					state = Resolution;
				}
			}break;
		case Resolution:{
				if(m->message().startsWith("res")){
					QList<QByteArray> parts = m->message().split('|');
					QByteArray serverResStr = parts[1];
					qDebug() << "$ Resolution recieved from Server: "+serverResStr;
					DG::Resolution* resolution = new Resolution;
					resolution->unpack(serverResStr.trimmed());
					//set Resolution
					DG::MessagePacket* res = new DG::MessagePacket((int)Resolution);
					res->setMessage("prepared");
					send(res);
					state = Prepared;
				}
			}break;
		case Prepared:{
				if(m->message().startsWith("start")){
					//Start The Threads
					//Send Initial Screen Packet from The Queue
				}
				state = Working;
			}break;
		case Working:{
				if(m->message().startsWith("ACK")){
					//Send Next ScreenPacket in the Queue
				}
			}break;
	}
}
