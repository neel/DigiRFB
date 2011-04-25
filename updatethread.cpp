#include "updatethread.h"
#include "rectarea.h"
#include <QTimer>

using namespace DG;
UpdateThread::UpdateThread(DG::RectArea* area, QObject *parent):QThread(parent), _area(area){

}

void UpdateThread::run(){
	timer = new QTimer();
	timer->setSingleShot(false);
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer->start(1000);
	exec();
}

void UpdateThread::tick(){
	_area->update();
}
