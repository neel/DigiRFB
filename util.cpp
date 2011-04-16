#include "util.h"
#include "resolution.h"
#include "QApplication"
#include <QtAlgorithms>
#include <QDesktopWidget>

using namespace DG;

Resolution* Util::currentResolution(){
	QRect screenRect = QApplication::desktop()->screenGeometry();
	Resolution* resolution = new Resolution(screenRect.width(), screenRect.height());
	return resolution;
}

QList<Resolution*> Util::SupportedResolutions(){
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	quint8 index = 0;
	QList<Resolution*> supportedResolutions;
	if(0 != EnumDisplaySettings(0x0, index++, &dm)){
		Resolution* resolution = new Resolution(dm.dmPelsWidth, dm.dmPelsHeight);
		supportedResolutions << resolution;
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

int Util::grabScreen(DG::Rect* rect){
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

	int result = qstrncmp(buff,rect->buffer, rect->size());
	if(result != 0)
		rect->buffer.setRawData(buff, rect->size());
	return result;
}

bool Util::setScreen(DG::Rect* rect, HWND hwnd){
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
