#ifndef UTIL_H
#define UTIL_H

#define _WIN32_WINNT 0x0404

#include <QList>
#include <QByteArray>
#include <windows.h>
#include <QPixmap>
#include <QMutex>
#include <QImage>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>

class QWidget;

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
		static WId winId;
		static QWidget* _desktopWidget;
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
		static bool compare(const QImage& l, const QImage& r);
	public:
		static void fireEvent(QMouseEvent* ev);
		static void fireEvent(QWheelEvent* ev);
		static void fireEvent(QKeyEvent* ev);
};
}
#endif // UTIL_H
