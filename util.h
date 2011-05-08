#ifndef UTIL_H
#define UTIL_H

#include <QList>
#include <QByteArray>
#include "windows.h"
#include <QPixmap>
#include <QMutex>
#include <QImage>

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
		static WId winId;
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
};
}
#endif // UTIL_H
