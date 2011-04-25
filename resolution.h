#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <QByteArray>

namespace DG{
/**
	* Structure to hold the resolution Pair
	* It doesn't detect or set Screeb resolution
	* Just a Structure to store the resolution
	*/
class Resolution{
	static char sep;
	public:
		Resolution();
		Resolution(unsigned int resX, unsigned int resY);
	private:
		unsigned int _x;
		unsigned int _y;
	public:
		QByteArray pack() const;
		void unpack(QByteArray buff);
	public:
		static bool parsable(QByteArray buff);
		static QList<DG::Resolution*> parseSupportedResolutions(QByteArray buff, char sep);
		static QByteArray joinSupportedResolutions(QList<Resolution*> resList, char sep);
	public:
		unsigned int x() const;
		unsigned int y() const;
	public:
		bool compare(const DG::Resolution& resolution);
};
}
#endif // RESOLUTION_H
