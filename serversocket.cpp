#include "serversocket.h"
#include "packet.h"
#include "messagepacket.h"
#include "screenpacket.h"
#include "resolution.h"
#include "util.h"
#include <QList>
#include <QDebug>
#include <QGraphicsPixmapItem>

using namespace DG;

ServerSocket::ServerSocket(QObject* parent):CommonSocket(parent){

}

ServerSocket::~ServerSocket(){

}

void ServerSocket::clientConnected(){
	DG::MessagePacket* m = new DG::MessagePacket(0);
	m->setMessage("hi!");
	send(m);
	state = Connected;
}

void ServerSocket::msgReceived(){
	DG::Packet* p = rcv();
	switch(currentState()){
		case Connected:{
				DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(p);
				if(m->message().startsWith("hallo")){
					DG::MessagePacket* res = new DG::MessagePacket((int)Connected);
					res->setMessage("welcome HellaRex 1.0.0.0");
					send(res);
					state = Welcome;
				}
			}break;
		case Welcome:{
				DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(p);
				if(m->message().startsWith("challange")){
					DG::MessagePacket* res = new DG::MessagePacket((int)Welcome);
					res->setMessage("password|123456");
					send(res);
					state = Password;
				}
			}break;
		case Password:{
				DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(p);
				if(m->message().startsWith("res")){
					DG::MessagePacket* res = new DG::MessagePacket((int)Password);
					res->setMessage("res|1024x768");
					send(res);
					state = ResolutionAccepted;
				}
			}break;
		case ResolutionAccepted:{
				DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(p);
				if(m->message().startsWith("prepared")){
					DG::MessagePacket* res = new DG::MessagePacket((int)ResolutionAccepted);
					res->setMessage("start");
					send(res);
					state = Start;
				}
			}break;
		case Start:{
				state = Working;
			}
		case Working:{
				DG::ScreenPacket* s = dynamic_cast<DG::ScreenPacket*>(p);
				QGraphicsPixmapItem* item = s->graphicsPixmapItem();
				DG::MessagePacket* m = new DG::MessagePacket((int)Working);
				m->setMessage("ACK");
				send(m);
			}break;
	}
}
