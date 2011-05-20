#include "clientsocket.h"
#include "packet.h"
#include "messagepacket.h"
#include "screenpacket.h"
#include "resolution.h"
#include "util.h"
#include "matrixstorage.h"
#include "matrixstorageitem.h"
#include "rectarea.h"
#include "updatethread.h"
#include <QList>
#include <QDebug>
#include "requestcontroller.h"
#include <QThreadPool>
#include "eventpacket.h"
#include "mouseeventpacket.h"

using namespace DG;

ClientSocket::ClientSocket(QObject* parent):CommonSocket(parent), storage(0x0),
divisionCols(1), divisionRows(1), rectCols(1), rectRows(16){
	connect(this, SIGNAL(msgWaiting()), this, SLOT(msgReceived()));
}

ClientSocket::~ClientSocket(){

}

void ClientSocket::msgReceived(){
	DG::Packet* p = rcv();
	DG::MessagePacket* m = dynamic_cast<DG::MessagePacket*>(p);
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
					QList<QByteArray> parts = m->message().split(' ');
					QByteArray serverResStr = parts[1];
					qDebug() << "$ Resolution recieved from Server: "+serverResStr;
					DG::Resolution* resolution = new DG::Resolution;
					resolution->unpack(serverResStr.trimmed());
					prepare(resolution);
					//set Resolution
					DG::MessagePacket* res = new DG::MessagePacket((int)Resolution);
					res->setMessage("prepared "+QByteArray::number(divisionRows*rectRows)+"|"+QByteArray::number(divisionCols*rectCols));
					send(res);
					state = Prepared;
				}
			}break;
		case Prepared:{
				if(m->message().startsWith("start")){
					//Send Initial Screen Packet from The Queue
					//send(storage->next((int)Prepared));
					controller->request();
				}
				state = Working;
			}break;
		case Working:{
				if(p->type() == Packet::MouseEventPacket){
						MouseEventPacket* mouseEvent = dynamic_cast<MouseEventPacket*>(p);
						Q_ASSERT(mouseEvent != 0x0);
						mouseEvent->reflect();
				}else if(p->type() == Packet::MessagePacket){
					if(m->message().startsWith("ACK")){
						//Send Next ScreenPacket in the Queue
						//send(storage->next((int)Working));
						controller->request();
					}
				}
			}break;
	}
}

void ClientSocket::prepare(DG::Resolution* resolution){
	Util::_init();
	storage = new DG::MatrixStorage(resolution, divisionRows*rectRows, divisionCols*rectCols);
	controller = new DG::RequestController(this, storage);
	for(int i=0;i<divisionRows;++i){
		for(int j=0;j<divisionCols;++j){
			QList<DG::MatrixStorageItem*> list;
			DG::RectArea* rectArea = new DG::RectArea(storage);

			for(int k=i*rectRows;k<(i+1)*rectRows;++k){
				for(int l=j*rectCols;l<(j+1)*rectCols;++l){
					list << storage->item(k, l);
				}
			}

			rectArea->assignItems(list);
			DG::UpdateThread* thread = new DG::UpdateThread(rectArea);
			qDebug() << "Rect Area" << i << j << thread;
			controller->addThread(thread);
			//thread->start();
			QThreadPool::globalInstance()->setMaxThreadCount(8);
			QThreadPool::globalInstance()->start(thread);
		}
	}
	controller->allThreadsAdded();
}
