#ifndef RECTAREA_H
#define RECTAREA_H

#include <QList>
#include <QMutex>

namespace DG{
	class MatrixStorageItem;
	class MatrixStorage;
}

namespace DG{
/**
	* Each RectArea will be handled by one thread
	* There will be multple instances of RectArea all of them will have reference
	* to MatrixStorage
	*/
class RectArea{
	private:
		QMutex mutex;
	private:
		MatrixStorage* _storage;
		QList<MatrixStorageItem*> _items;
	public:
		RectArea(MatrixStorage* storage);
		void assignItems(QList<MatrixStorageItem*> items);
		void update();
};
}
#endif // RECTAREA_H
