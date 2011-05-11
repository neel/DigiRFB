#include "serversocket.h"
#include "packet.h"
#include "messagepacket.h"
#include "screenpacket.h"
#include "resolution.h"
#include "util.h"
#include <QList>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "scenematrix.h"

using namespace DG;

ServerSocket::ServerSocket(QGraphicsScene* scene, QObject* parent):CommonSocket(parent), _scene(scene){
	connect(this, SIGNAL(msgWaiting()), this, SLOT(msgReceived()));
	_matrix = new SceneMatrix(_scene);
}

ServerSocket::~ServerSocket(){

}

void ServerSocket::clientConnected(){
	DG::MessagePacket* m = new DG::MessagePacket(0);
	m->setMessage("hi! HellaRexer");
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
					QList<QByteArray> parts = m->message().trimmed().split('|');
					QList<QByteArray> _currentParts = parts[0].split(' ');
					DG::Resolution* resolution = new DG::Resolution;
					resolution->unpack(_currentParts[1]);
					QList<DG::Resolution*> supportedResolutions = Resolution::parseSupportedResolutions(parts[1], ',');
					prepare(resolution);
					DG::MessagePacket* res = new DG::MessagePacket((int)Password);
					res->setMessage("res "+resolution->pack());
					send(res);
					state = ResolutionAccepted;
				}
			}break;
		case ResolutionAccepted:{
				DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(p);
				if(m->message().startsWith("prepared")){
					QList<QByteArray> parts = m->message().trimmed().split(' ');
					QList<QByteArray> _dimParts = parts[1].split('|');
					quint16 rows = _dimParts[0].toInt();
					quint16 cols = _dimParts[1].toInt();
					_matrix->setGridDimension(rows, cols);
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
				//_scene->addItem(item);
				_matrix->addItem(s->row(), s->col(), item);
				DG::MessagePacket* m = new DG::MessagePacket((int)Working);
				m->setMessage("ACK");
				send(m);
			}break;
	}
	delete p;
}

void ServerSocket::prepare(const DG::Resolution* resolution){
	_scene->setSceneRect(0, 0, resolution->x(), resolution->y());
}
