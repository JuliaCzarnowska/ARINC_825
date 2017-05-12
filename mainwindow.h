#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serialconfigbox.h>
#include <receivebox.h>
#include <socket.h>

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
    A825_MSG* rcvMessage;
    A825_MSG* traMessage;

    Ui::MainWindow *ui;
    Socket *socket;
    SerialConfigBox *serialCfg;
    ReceiveBox *receiveBox;
};

#endif // MAINWINDOW_H
