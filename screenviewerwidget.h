#ifndef SCREENVIEWERWIDGET_H
#define SCREENVIEWERWIDGET_H

#include <QWidget>

namespace DG{
	class ScreenPacket;
}

namespace DG{
class ScreenViewerWidget : public QWidget{
	Q_OBJECT
	private:
		DG::ScreenPacket* _packet;
	public:
    explicit ScreenViewerWidget(QWidget *parent = 0);
		void drawScreen(DG::ScreenPacket* packet);
		void paintEvent(QPaintEvent* event);
};
}
#endif // SCREENVIEWERWIDGET_H
