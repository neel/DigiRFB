#include "rect.h"
#include "util.h"
#include "resolution.h"
#include "QApplication"
#include <QtAlgorithms>
#include <QDesktopWidget>
#include <QDebug>

using namespace DG;

DISPLAY_DEVICE Util::GetPrimaryDevice(){
	int index=0;
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);

	while(EnumDisplayDevices(NULL, index++, &dd, 0)){
			if (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) return dd;
	}
	return dd;
}

Resolution* Util::currentResolution(){
	QRect screenRect = QApplication::desktop()->screenGeometry();
	Resolution* resolution = new Resolution(screenRect.width(), screenRect.height());
	return resolution;
}

QList<Resolution*> Util::SupportedResolutions(){
	DEVMODE dm;
	/*ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);*/
	int index = 0;
	QList<Resolution*> supportedResolutions;
	while(0 != EnumDisplaySettings(NULL, index++, &dm)){
		Resolution* resolution = new Resolution(dm.dmPelsWidth, dm.dmPelsHeight);
		bool matched = false;
		foreach(DG::Resolution* r, supportedResolutions){
			if(resolution->compare(*r)){
				delete resolution;
				resolution = 0x0;
				matched = true;
				break;
			}
		}
		if(!matched && resolution != 0x0){
			supportedResolutions << resolution;
		}
	}
	return supportedResolutions;
}

bool Util::setResolution(Resolution* res){
	long PelsWidth = res->x();
	long PelsHeight = res->y();
	DISPLAY_DEVICE dd = GetPrimaryDevice();
	DEVMODE dm;
	dm.dmSize = sizeof(DEVMODE);
	if (!EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm)){
			return false;
	}
	dm.dmPelsWidth = PelsWidth;
	dm.dmPelsHeight = PelsHeight;
	dm.dmFields = (DM_PELSWIDTH | DM_PELSHEIGHT);
	if (ChangeDisplaySettings(&dm, CDS_TEST) !=DISP_CHANGE_SUCCESSFUL){
			return false;
	}
	return (ChangeDisplaySettings(&dm, 0)==DISP_CHANGE_SUCCESSFUL);
}

QPixmap Util::grabScreen(const DG::Rect* rect){
	mutex.lock();
	QPixmap pixmap = QPixmap::grabWindow(Util::winId,rect->left, rect->top, rect->width, rect->height);
	mutex.unlock();
	return pixmap;

}

void Util::_init(){
	QDesktopWidget* desktopWidget = new QDesktopWidget;
	DG::Util::_desktopWidget = desktopWidget;
	Util::winId = desktopWidget->screen(desktopWidget->primaryScreen())->winId();
}

bool Util::compare(const QImage& l, const QImage& r){
	return l == r;
}

void Util::fireEvent(QMouseEvent* ev){
	QApplication::postEvent(DG::Util::_desktopWidget, ev);
}

WId DG::Util::winId;
QMutex DG::Util::mutex;
QDesktopWidget* DG::Util::_desktopWidget;

