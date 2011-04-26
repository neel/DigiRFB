#ifndef UTIL_H
#define UTIL_H

#include <QList>
#include <QByteArray>
#include "windows.h"
#include <QPixmap>
#include <QMutex>

class QDesktopWidget;

namespace DG{
	class Rect;
	class Resolution;
}

namespace DG{
/**
	* Does the System dependent Jobs
	*/
class Util{
	private:
		static QDesktopWidget* desktop;
		static QWidget* desktopWidget;
	public:
		static void _init();
	private:
		static DISPLAY_DEVICE GetPrimaryDevice();
		static QMutex mutex;
	public:
		static Resolution* currentResolution();
		static QList<Resolution*> SupportedResolutions();
		static bool setResolution(Resolution* res);
		static QPixmap grabScreen(const DG::Rect* rect);
		/*static bool setScreen(DG::Rect* rect, HWND hwnd, const QPixmap& pixmap);*/
};
}
#endif // UTIL_H
