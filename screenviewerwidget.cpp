#include "screenviewerwidget.h"
#include <QPainter>
#include <QDebug>
#include "screenpacket.h"

using namespace DG;
ScreenViewerWidget::ScreenViewerWidget(QWidget *parent): QWidget(parent), _packet(0x0){

}

void ScreenViewerWidget::drawScreen(DG::ScreenPacket* packet){
	_packet = packet;
	update();
}

void ScreenViewerWidget::paintEvent(QPaintEvent* event){
	if(!_packet){
		return QWidget::paintEvent(event);
	}else{
		QPainter painter;
		painter.begin(this);
		painter.drawPixmap(_packet->rect().toQRect(), _packet->pixmap());
		painter.end();
	}
}
