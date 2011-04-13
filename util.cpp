#include "util.h"
#include "resolution.h"
#include "QApplication"

using namespace DG;

Resolution* Util::ScreenResolution(){
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
	//TODO Not Implemented Yet
}

quint64 Util::grabScreen(DG::Rect* rect){
	HDC hdc=GetWindowDC(NULL);
	HWND win=WindowFromDC(hdc);

	HDC cdc=CreateCompatibleDC(hdc);
	HBITMAP temp=CreateCompatibleBitmap(hdc,rect->width,rect->height);
	PAINTSTRUCT ps;

	hdc=BeginPaint(win,&ps);
	HBITMAP oldb=(HBITMAP)SelectObject(cdc,temp);
	BitBlt(cdc,0,0,width,height,hdc,rect->top,rect->left,SRCCOPY);//Is it Top, left ? or left, top ??
	SelectObject(cdc,oldb);
	EndPaint(win,&ps);

	char* buff;
	buff = new char[size()];
	GetBitmapBits(temp,size(),buff);
	QByteArray returnBuff(buff, size());
	rect->buffer = returnBuff;
}

bool Util::setScreen(DG::Rect* rect, HWND hwnd){
	//TODO Not Implemented Yet
	RECT wRect;
	wRect.left = rect->left;
	wRect.top = rect->top;
	wRect.right = rect->left+rect->width;
	wRect.bottom = rect->top+rect->height;
	InvalidateRect(hwnd, &wRect, false);
}
