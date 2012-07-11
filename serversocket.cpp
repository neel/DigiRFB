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
#include "confirmpassworddialog.h"
#include <QCryptographicHash>
#include "mouseeventspacket.h"
#include <iostream>
#include <QApplication>

using namespace DG;

ServerSocket::ServerSocket(QGraphicsScene* scene, QObject* parent):CommonSocket(parent), _scene(scene), dlg(0x0){
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
					dlg = new DG::ConfirmPasswordDialog;
					connect(dlg, SIGNAL(confirmed(QString)), this, SLOT(confirmed(QString)));
					dlg->show();
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
				}else if(m->message().startsWith("denied")){
					if(dlg != 0x0){
						dlg->show();
					}
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
                if(lastHeaderType() == DG::Packet::ScreenPacket){
					DG::ScreenPacket* s = dynamic_cast<DG::ScreenPacket*>(p);
					QGraphicsPixmapItem* item = s->graphicsPixmapItem();
                    if(!s->dumpPixmap()){
                        QApplication::beep();
                    }
					//_scene->addItem(item);
					_matrix->addItem(s->row(), s->col(), item);
					DG::MessagePacket* m = new DG::MessagePacket((int)Working);
					m->setMessage("ACK");
					send(m);
				}else if(lastHeaderType() == DG::Packet::MessagePacket){

				}
			}break;
	}
	delete p;
}

void ServerSocket::prepare(const DG::Resolution* resolution){
	_scene->setSceneRect(0, 0, resolution->x(), resolution->y());
}

void ServerSocket::confirmed(const QString& pass){
	DG::MessagePacket* res = new DG::MessagePacket((int)Welcome);
	QString passwordChecksum = QCryptographicHash::hash(pass.toAscii(), QCryptographicHash::Md5);
	QString passStr = "password|"+passwordChecksum;
	res->setMessage(passStr.toAscii());
	send(res);
	state = Password;
}

void ServerSocket::mouseEventPacketsWaiting(DG::MouseEventsPacket* packet){
	send(packet);
	/*DG::MessagePacket* m = new DG::MessagePacket((int)Working);
	m->setMessage("MOUSE");
	send(m);*/
}
