#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ARINC 825 Communicator");

    socket = new Socket();
    //creating widgets
    serialCfg = new SerialConfigBox(this);
    receiveBox = new ReceiveBox(this);

    //building ui
    QGridLayout *mainLayout = new QGridLayout;
    ui->centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(serialCfg,0,0,-1,1);
    mainLayout->addWidget(receiveBox, 1, 1, 1, 1);

    connect(serialCfg, SIGNAL(applySerial(SerialConfigBox::SerialSettings)),
            socket, SLOT(openSerialPort(SerialConfigBox::SerialSettings)));
    connect(serialCfg, SIGNAL(closeSerialSignal()), socket, SLOT(closeSerialPort()));
    connect(socket, SIGNAL(serialConnectionState(bool)),
            serialCfg, SLOT(setConnectionButtons(bool)));
    connect(socket, SIGNAL(messageToDisplay(A825_MSG*)),
            receiveBox, SLOT(displayMessage(A825_MSG*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
