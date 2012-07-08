#ifndef SERVERCONNECTIONDIALOG_H
#define SERVERCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ServerConnectionDialog;
}

class ServerConnectionDialog : public QDialog{
    Q_OBJECT    
public:
    explicit ServerConnectionDialog(QWidget *parent = 0);
    ~ServerConnectionDialog();
private:
    Ui::ServerConnectionDialog *ui;
signals:
    void serverStarted(int);
    void serverQuit();
private slots:
    void serverStartSlot();
};

#endif // SERVERCONNECTIONDIALOG_H
