#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>

class QTimer;

namespace DG{
	class RectArea;
}

namespace DG{
class UpdateThread : public QThread{
	Q_OBJECT
	private:
		QTimer* timer;
		DG::RectArea* _area;
	public:
		explicit UpdateThread(DG::RectArea* area, QObject *parent = 0);
		void run();
	public slots:
		void tick();
};
}
#endif // UPDATETHREAD_H
