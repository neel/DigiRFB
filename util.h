#ifndef UTIL_H
#define UTIL_H

#include <QList>
#include <QByteArray>
#include "windows.h"
#include "rect.h"

class Resolution;

namespace DG;
/**
	* Does the System dependent Jobs
	*/
class Util{
	public:
		static Resolution* currentResolution();
		static QList<Resolution*> SupportedResolutions();
		static bool setResolution(Resolution* res);
		static quint64 grabScreen(DG::Rect* rect);
		static bool setScreen(DG::Rect* rect, HWND hwnd);
};

#endif // UTIL_H
