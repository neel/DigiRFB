#include "rect.h"
#include "util.h"
#include "resolution.h"
#include "QApplication"
#include <QtAlgorithms>
#include <QDesktopWidget>
#include <QDebug>
#include <winuser.h>
#include <windows.h>
#include <QThread>

#define KEYEVENTF_EXTENDEDKEY 0x0001
#define KEYEVENTF_KEYUP 0x0002
#define KEYEVENTF_UNICODE 0x0004
#define KEYEVENTF_SCANCODE 0x0008

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
    }else if(ev->type() == QEvent::MouseButtonDblClick){
		input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
		::SendInput(1,&input,sizeof(INPUT));
		//Should I Sleep Here ?
		input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
    }
	::SendInput(1,&input,sizeof(INPUT));

/*
	QApplication::postEvent(DG::Util::_desktopWidget, ev);
*/
}

void Util::fireEvent(QWheelEvent* ev){
	INPUT input = {0};
	input.type = INPUT_MOUSE;
	if(ev->orientation() == Qt::Horizontal){
		input.mi.dwFlags = MOUSEEVENTF_WHEEL;
	}else if(ev->orientation() == Qt::Vertical){
		//Not Handled
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
		//The above Commented Code will work on Vista and above
	}
	input.mi.mouseData = ev->delta();
	::SendInput(1,&input,sizeof(INPUT));
}

void Util::fireEvent(QKeyEvent* ev){
    //QApplication::postEvent(DG::Util::_desktopWidget, ev);
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    if(ev->type() == QEvent::KeyPress){
        input.ki.dwFlags = 0;
    }else if(ev->type() == QEvent::KeyRelease){
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    }
    input.ki.wVk = 0;
    int key = ev->key();
    switch (key) {
        case Qt::Key_Alt:
            input.ki.wVk = (ev->nativeScanCode() == VK_LMENU) ? VK_LMENU : VK_RMENU;
            break;
        case Qt::Key_Control:
            input.ki.wVk = (ev->nativeScanCode() == VK_LCONTROL) ? VK_LCONTROL : VK_RCONTROL;
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            input.ki.wVk = VK_RETURN;
            break;
        case Qt::Key_Backspace:
            input.ki.wVk = VK_BACK;
            break;
        case Qt::Key_Up:
            input.ki.wVk = VK_UP;
            break;
         case Qt::Key_Down:
            input.ki.wVk = VK_DOWN;
            break;
        case Qt::Key_Left:
            input.ki.wVk = VK_LEFT;
            break;
         case Qt::Key_Right:
            input.ki.wVk = VK_RIGHT;
            break;
        case Qt::Key_Home:
            input.ki.wVk = VK_HOME;
            break;
        case Qt::Key_End:
            input.ki.wVk = VK_END;
            break;
        case Qt::Key_Insert:
            input.ki.wVk = VK_INSERT;
            break;
        case Qt::Key_PageUp:
            input.ki.wVk = VK_PRIOR;
            break;
        case Qt::Key_PageDown:
            input.ki.wVk = VK_NEXT;
            break;
        case Qt::Key_Delete:
            input.ki.wVk = VK_DELETE;
            break;
        case Qt::Key_CapsLock:
            input.ki.wVk = VK_CAPITAL;
            break;
        case Qt::Key_NumLock:
            input.ki.wVk = VK_NUMLOCK;
            break;
        case Qt::Key_Escape:
            input.ki.wVk = VK_ESCAPE;
            break;
        case Qt::Key_Shift:
            input.ki.wVk = VK_SHIFT;
            break;
        default:
            QChar c(ev->text()[0]);
            input.ki.wScan = c.unicode();
            input.ki.dwFlags |= KEYEVENTF_UNICODE;
            break;
    }

    ::SendInput(1,&input,sizeof(INPUT));
}

WId DG::Util::winId;
QMutex DG::Util::mutex;
QWidget* DG::Util::_desktopWidget;

