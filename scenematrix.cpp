#include "scenematrix.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>

using namespace DG;
SceneMatrix::SceneMatrix(QGraphicsScene* scene): _scene(scene), _rows(0), _cols(0){

}

quint16 SceneMatrix::index(quint16 row, quint16 col) const{
	return row*_cols+col;
}

void SceneMatrix::setGridDimension(quint16 rows, quint16 cols){
	_rows = rows;
	_cols = cols;
	_list.reserve(sizeof(QGraphicsItem*)*_rows*_cols);
	qDebug() << "SceneMatrix::setGridDimension" << _rows << _cols;
	for(int i=0;i<(_rows*_cols);++i){
		_list << 0x0;
	}
}

void SceneMatrix::addItem(quint16 row, quint16 col, QGraphicsItem* item){
	if(row > _rows || col > _cols)
		return;
	quint16 _index = index(row, col);
	_scene->addItem(item);
	if(_list.count() > _index){
		QGraphicsItem* _existing = _list.at(_index);
		if(_existing){
			qDebug() << "SceneMatrix::addItem" << _existing << _existing->isObscured();
			//if(_existing->isObscured()){
				_scene->removeItem(_existing);
				delete _existing;
			//}
		}
	}
	qDebug() << "_list.count(): " << _list.count() << " index: " << _index << row << col;
	_list[_index] = item;
}
