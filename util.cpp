#include "rect.h"
#include "util.h"
#include "resolution.h"
#include "QApplication"
#include <QtAlgorithms>
#include <QDesktopWidget>
#include <QDebug>
#include <winuser.h>

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
	DG::Util::_desktopWidget = desktopWidget->screen(desktopWidget->primaryScreen());
	Util::winId = desktopWidget->screen(desktopWidget->primaryScreen())->winId();
}

bool Util::compare(const QImage& l, const QImage& r){
	return l == r;
}

void Util::fireEvent(QMouseEvent* ev){
/*
	DWORD dwFlags;
	DWORD dx;
	DWORD dy;
	DWORD dwData;
	ULONG_PTR dwExtraInfo;
	qDebug() << "Util::fireEvent (" << ev->x() << ev->y() << ") " << dx << dy;

	if(ev->type() == QEvent::MouseButtonPress){
		if(ev->button() == Qt::LeftButton){
			dwFlags  = MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE;
		}else if(ev->button() == Qt::RightButton){
			dwFlags  = MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_ABSOLUTE;
		}
	}else if(ev->type() == QEvent::MouseButtonRelease){
		if(ev->button() == Qt::LeftButton){
			dwFlags  = MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE;
		}else if(ev->button() == Qt::RightButton){
			dwFlags  = MOUSEEVENTF_RIGHTUP|MOUSEEVENTF_ABSOLUTE;
		}
	}else if(ev->type() == QEvent::MouseMove){
		dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
		dx = ev->x();
		dy = ev->y();
	}
	mouse_event(dwFlags, dx, dy, dwData, dwExtraInfo);
*/

	INPUT input = {0};
	input.type = INPUT_MOUSE;
	if(ev->type() == QEvent::MouseButtonPress){
		if(ev->button() == Qt::LeftButton){
			input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
		}else if(ev->button() == Qt::RightButton){
			input.mi.dwFlags  = MOUSEEVENTF_RIGHTDOWN;
		}
	}else if(ev->type() == QEvent::MouseButtonRelease){
		if(ev->button() == Qt::LeftButton){
			input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
		}else if(ev->button() == Qt::RightButton){
			input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
		}
	}else if(ev->type() == QEvent::MouseMove){
		input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
		input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
		double fScreenWidth	= GetSystemMetrics( SM_CXSCREEN )-1;
		double fScreenHeight	= GetSystemMetrics( SM_CYSCREEN )-1;
		double fx		         = ev->globalX() * (65535.0f/fScreenWidth);
		double fy		         = ev->globalY() * (65535.0f/fScreenHeight);
		input.mi.dx = fx;
		input.mi.dy = fy;
	}
	::SendInput(1,&input,sizeof(INPUT));

/*
	QApplication::postEvent(DG::Util::_desktopWidget, ev);
*/
}

void Util::fireEvent(QKeyEvent* ev){

}

WId DG::Util::winId;
QMutex DG::Util::mutex;
QWidget* DG::Util::_desktopWidget;

