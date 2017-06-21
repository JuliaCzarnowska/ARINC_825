#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serialconfigbox.h>
#include <receivebox.h>
#include <transmitbox.h>
#include <socket.h>
#include <profile.h>
#include <a825configbox.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Socket *socket;
    SerialConfigBox *serialCfg;
    ReceiveBox *receiveBox;
    TransmitBox *transmitBox;
    A825ConfigBox *arincCfg;
    Profile *profile;

    void establishConnections();
    void organizeUI();
};

#endif // MAINWINDOW_H
