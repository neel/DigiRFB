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
#include "mouseeventspacket.h"
#include "keyboardeventpacket.h"
#include "challangedialog.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QThread>

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

					DG::ChallangeDialog* dlg = new DG::ChallangeDialog;
					dlg->setModal(true);
					connect(dlg, SIGNAL(challanged(QString)), this, SLOT(challanged(QString)));
					int dlgres = dlg->exec();
/*
					QMessageBox msgBox;
					 msgBox.setText("The document has been modified.");
					 msgBox.setInformativeText("Do you want to save your changes?");
					 msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
					 msgBox.setDefaultButton(QMessageBox::Save);

					 int ret = msgBox.exec();
*/
					/*
					DG::MessagePacket* res = new DG::MessagePacket((int)Hallo);
					res->setMessage("challange");
					send(res);
					state = Challange;
					*/
				}
			}break;
		case Challange:{
				if(m->message().startsWith("password")){
					QList<QByteArray> parts = m->message().split('|');
					QByteArray serverPass = parts[1];
					qDebug() << "$ Password recieved from Server: "+serverPass;
					//Compare Passwords
					if(serverPass.trimmed() == passwordChecksum){
						DG::MessagePacket* res = new DG::MessagePacket((int)Challange);
						QByteArray currentResdolution = Util::currentResolution()->pack();
						QByteArray supportedResolutions = Resolution::joinSupportedResolutions(Util::SupportedResolutions(), ',');
						res->setMessage("res "+currentResdolution+"|"+supportedResolutions);
						send(res);
						state = Resolution;
					}else{
						//ask to Retry
						DG::MessagePacket* res = new DG::MessagePacket((int)Challange);
						res->setMessage("denied");
						send(res);
					}
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
						MouseEventsPacket* mouseEvents = dynamic_cast<MouseEventsPacket*>(p);
						qDebug() << ":: Rcvd MouseEvent";
						Q_ASSERT(mouseEvents != 0x0);
						mouseEvents->reflect();
						DG::MessagePacket* res = new DG::MessagePacket((int)Working);
						res->setMessage("ACK M");
						send(res);
				}else if(p->type() == Packet::MessagePacket){
					qDebug() << ":: Rcvd Message " << m->message();
					if(m->message().startsWith("ACK")){
						controller->acknowledged();
						//Send Next ScreenPacket in the Queue
						//send(storage->next((int)Working));
						controller->request();
					}
				}else if(p->type() == Packet::KeyboardEventPacket){
					KeyboardEventPacket* keyboardEvent = dynamic_cast<KeyboardEventPacket*>(p);
					qDebug() << ":: Rcvd KeyEvent";
					Q_ASSERT(keyboardEvent != 0x0);
					keyboardEvent->reflect();
					DG::MessagePacket* res = new DG::MessagePacket((int)Working);
					res->setMessage("ACK K");
					send(res);
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

void ClientSocket::challanged(const QString& pass){
	passwordChecksum = QCryptographicHash::hash(pass.toAscii(), QCryptographicHash::Md5);
	DG::MessagePacket* res = new DG::MessagePacket((int)Hallo);
	res->setMessage("challange");
	send(res);
	state = Challange;
}
