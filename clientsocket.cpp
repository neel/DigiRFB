#include "clientsocket.h"
#include "packet.h"
#include "messagepacket.h"
#include "screenpacket.h"
#include "resolution.h"
#include "util.h"

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
					res->setMessage("hallo");
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
					DG::MessagePacket* res = new DG::MessagePacket((int)Resolution);
					res->setMessage("prepared");
					send(res);
					state = Prepared;
				}
			}break;
		case Prepared:{
				if(m->message().startsWith("start")){
					//Start The Threads
					//Senbd Initial Screen Packet
				}
				state = Working;
			}break;
		case Working:{
				if(m->message().startsWith("ACK")){

				}
			}break;
	}
}
