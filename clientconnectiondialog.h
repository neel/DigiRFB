#ifndef CLIENTCONNECTIONDIALOG_H
#define CLIENTCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
    class ClientConnectionDialog;
}

class ClientConnectionDialog : public QDialog{
    Q_OBJECT
    
  public:
    explicit ClientConnectionDialog(QWidget *parent = 0);
    ~ClientConnectionDialog();
    
  private:
    Ui::ClientConnectionDialog *ui;
  private slots:
    void acceptedSlot();
  signals:
    void connectionRequested(const QString& host, int port);
};

#endif // CLIENTCONNECTIONDIALOG_H
