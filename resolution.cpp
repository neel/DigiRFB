#include "resolution.h"
#include <QList>
#include <QRegExp>

using namespace DG;

Resolution::Resolution(unsigned int resX=0, unsigned int resY=0):_x(resX), _y(resY){

}

unsigned int Resolution::x() const{
	return _x;
}
unsigned int Resolution::y() const{
	return _y;
}

QByteArray Resolution::pack() const{
	QByteArray buff = QByteArray::number(_x)+Resolution::sep+QByteArray::number(_y);
	return buff;
}

void Resolution::unpack(QByteArray buff){
	QList<QByteArray> parts = buff.trimmed().split(Resolution::sep);
	_x = parts[0].toInt();
	_y = parts[1].toInt();
}

QList<Resolution*> Resolution::parseSupportedResolutions(QByteArray buff, char sep=','){
	QList<QByteArray> resList = buff.trimmed().split(sep);
	QList<Resolution*> list;
	foreach(QByteArray res, resList){
		if(Resolution::parsable(res)){
			Resolution* resolution = new Resolution;
			resolution->unpack(res);
			list << resolution;
		}
	}
	return list;
}

QByteArray Resolution::joinSupportedResolutions(QList<Resolution*> resList, char sep){
	QByteArray buff;
	int c = 0;
	foreach(Resolution* res, resList){
		buff += res->pack();
		if(c != 0)
			buff += ',';
		++c;
	}
	return buff;
}

bool Resolution::parsable(QByteArray buff){
	static QRegExp regx(QString("\\d+%1\\d+").arg(Resolution::sep));
	return regx.exactMatch(buff);
}

char Resolution::sep = 'x';
