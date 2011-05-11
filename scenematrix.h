#ifndef SCENEMATRIX_H
#define SCENEMATRIX_H

#include <QList>

class QGraphicsScene;
class QGraphicsItem;

namespace DG{
class SceneMatrix{
	private:
		QGraphicsScene* _scene;
		quint16 _rows;
		quint16 _cols;
	private:
		QList<QGraphicsItem*> _list;
	public:
		SceneMatrix(QGraphicsScene* scene);
	private:
		quint16 index(quint16 row, quint16 col) const;
	public:
		void setGridDimension(quint16 rows, quint16 cols);
		void addItem(quint16 row, quint16 col, QGraphicsItem* item);
};
}
#endif // SCENEMATRIX_H
