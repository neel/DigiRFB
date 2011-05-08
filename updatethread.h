#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QRunnable>
#include <QMutex>

namespace DG{
	class RectArea;
}

namespace DG{
class UpdateThread : public QRunnable{
	private:
		QMutex mutex;
	private:
		DG::RectArea* _area;
		DG::UpdateThread* _next;
	public:
		explicit UpdateThread(DG::RectArea* area);
		void run();
	public:
		void setNext(DG::UpdateThread* thread);
};
}
#endif // UPDATETHREAD_H
