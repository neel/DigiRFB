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
			qDebug() << index-1 << dm.dmPelsWidth << dm.dmPelsHeight;
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
/*
	HDC hdc=GetWindowDC(NULL);
	HWND win=WindowFromDC(hdc);

	HDC cdc=CreateCompatibleDC(hdc);
	HBITMAP temp=CreateCompatibleBitmap(hdc,rect->width,rect->height);
	PAINTSTRUCT ps;

	hdc=BeginPaint(win,&ps);
	HBITMAP oldb=(HBITMAP)SelectObject(cdc,temp);
	BitBlt(cdc,0,0,rect->width,rect->height,hdc,rect->top,rect->left,SRCCOPY);
	SelectObject(cdc,oldb);
	EndPaint(win,&ps);

	char* buff;
	buff = new char[rect->size()];
	GetBitmapBits(temp,rect->size(),buff);

	QPixmap pixmap = QPixmap::fromWinHBITMAP(temp);
*/
	QPixmap pixmap = QPixmap::grabWidget(desktopWidget,rect->toQRect());
	mutex.unlock();
	return pixmap;

}
/*
bool Util::setScreen(DG::Rect* rect, HWND hwnd, const QPixmap& pixmap){
	HDC hdc = GetWindowDC(hwnd);
	HBITMAP scrn = CreateCompatibleBitmap(hdc,rect->width,rect->height);
	SetBitmapBits(scrn, rect->size(), rect->buffer.data());

	BITMAP bm;
	PAINTSTRUCT ps;
	HDC whdc = BeginPaint(hwnd, &ps);
	HDC hdcMem = CreateCompatibleDC(whdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, scrn);
	GetObject(scrn, sizeof(bm), &bm);
	BitBlt(whdc, rect->left, rect->top, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	EndPaint(hwnd, &ps);

	RECT wRect;
	wRect.left = rect->left;
	wRect.top = rect->top;
	wRect.right = rect->left+rect->width;
	wRect.bottom = rect->top+rect->height;
	InvalidateRect(hwnd, &wRect, false);

	return true;
}
*/

Util::_init::_init(){
	Util::desktop = new QDesktopWidget;
	Util::desktopWidget = Util::desktop->screen(Util::desktop->primaryScreen());
}

QDesktopWidget* DG::Util::desktop;
QWidget* DG::Util::desktopWidget;
QMutex DG::Util::mutex;
DG::Util::_init DG::Util::init;
