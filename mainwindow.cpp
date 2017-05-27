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
    profile = new Profile();

    //creating widgets
    serialCfg = new SerialConfigBox(this);
    receiveBox = new ReceiveBox(this);
    transmitBox = new TransmitBox(this, profile);
    arincCfg = new A825ConfigBox(this);

    receiveBox->setProfile(profile);

    organizeUI();
    establishConnections();
}

MainWindow::~MainWindow()
{
    delete socket;
    delete serialCfg;
    delete receiveBox;
    delete ui;
}

void MainWindow::establishConnections()
{
    connect(serialCfg, SIGNAL(applySerial(SerialConfigBox::SerialSettings)),
            socket, SLOT(openSerialPort(SerialConfigBox::SerialSettings)));
    connect(serialCfg, SIGNAL(closeSerialSignal()), socket, SLOT(closeSerialPort()));
    connect(socket, SIGNAL(serialConnectionState(bool)),
            serialCfg, SLOT(setConnectionButtons(bool)));
    connect(socket, SIGNAL(messageToDisplay(A825_MSG*)),
            receiveBox, SLOT(displayMessage(A825_MSG*)));
    connect(transmitBox, SIGNAL(messageToSend(A825_MSG*)),
            socket, SLOT(writeA825Message(A825_MSG*)));
    connect(arincCfg, SIGNAL(newProfileChoice(QString)), profile, SLOT(loadProfile(QString)));
    connect(profile, SIGNAL(profileChanged()), transmitBox->comp1, SLOT(fillParameters()));
    connect(profile, SIGNAL(profileChanged()), transmitBox->comp2, SLOT(fillParameters()));
}

void MainWindow::organizeUI()
{
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *configurationLayout = new QVBoxLayout;
    QVBoxLayout *communicationLayout = new QVBoxLayout;
    ui->centralWidget->setLayout(mainLayout);
    mainLayout->addLayout(configurationLayout, 0, 0, 1, 1);
    mainLayout->addLayout(communicationLayout, 0, 1, 1, 1);

    configurationLayout->addWidget(serialCfg);
    configurationLayout->addWidget(arincCfg);
    communicationLayout->addWidget(transmitBox);
    communicationLayout->addWidget(receiveBox);
}
