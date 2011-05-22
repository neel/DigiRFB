#include <QtGui/QApplication>
#include "clientsocket.h"
#include <QHostAddress>

#include "resolution.h"
#include "util.h"
#include <QPixmap>
#include <QImage>
#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "server.h"
#include "clientsocket.h"

#include "screenviewerwidget.h"
#include "canvas.h"
#include <QThread>
#include "eventdespatcer.h"

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	DG::Util::_init();
/*
	DG::ClientSocket* socket = new DG::ClientSocket;
	socket->connectToHost("192.168.0.3", 5590);
*/

/*
	QByteArray currentResdolution = DG::Util::currentResolution()->pack();
	QByteArray supportedResolutions = DG::Resolution::joinSupportedResolutions(DG::Util::SupportedResolutions(), ',');
	qDebug() << currentResdolution;
	qDebug() << supportedResolutions;
*/

/*
	QGraphicsScene scene;
	scene.setSceneRect(0, 0, 1024, 768);
	QGraphicsView view(&scene);
	//view.setSceneRect(0, 0, 100, 100);
	scene.addText("Hallo World");
	scene.addEllipse(20, 20, 600, 300);
	view.show();
*/

	DG::Canvas scene;
	QGraphicsView view(&scene);
	view.setMouseTracking(true);
	DG::Server* server = new DG::Server(&scene);
	server->listen(5590);
	view.show();

/*
	DG::ScreenViewerWidget* widget = new DG::ScreenViewerWidget;
	QScrollArea* scroller = new QScrollArea;
	scroller->setWidget(widget);
	DG::Server* server = new DG::Server(widget);
	server->listen(5590);
	scroller->show();
*/

	return a.exec();
}
