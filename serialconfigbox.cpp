#include "serialconfigbox.h"
#include "ui_serialconfigbox.h"
#include "receivebox.h"

#include <QDebug>
#include <QThread>

SerialConfigBox::SerialConfigBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialConfigBox)
{
    ui->setupUi(this);
    ui->disconnectButton->setEnabled(false);
    fillParameters();

    connect(ui->scanButton, SIGNAL(clicked(bool)), this, SLOT(scanForPorts()));
    connect(ui->connectButton, SIGNAL(clicked(bool)), this, SLOT(connectSerial()));
    connect(ui->disconnectButton, SIGNAL(clicked(bool)), this, SLOT(closeSerialSlot()));
}

SerialConfigBox::~SerialConfigBox()
{
    delete ui;
}

void SerialConfigBox::scanForPorts()
{
    ui->COMComboBox->clear();
    //getting available ports and filling COM ComboBox
    const QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo & info : availablePorts)
        ui->COMComboBox->addItem(info.portName());
}

void SerialConfigBox::fillParameters()
{
    scanForPorts();

    ui->baudrateComboBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudrateComboBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudrateComboBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudrateComboBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudrateComboBox->addItem(tr("Custom"));

    ui->dataBitsComboBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsComboBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsComboBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsComboBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsComboBox->setCurrentIndex(3);

    ui->parityComboBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityComboBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityComboBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityComboBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityComboBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsComboBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsComboBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlComboBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->flowControlComboBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlComboBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

SerialConfigBox::SerialSettings SerialConfigBox::getSerialSettings()
{
    SerialConfigBox::SerialSettings set = SerialConfigBox::SerialSettings();
    set.name = ui->COMComboBox->currentText();
    set.baudRate = static_cast<QSerialPort::BaudRate>(ui->baudrateComboBox->currentText().toInt());
    set.dataBits = static_cast<QSerialPort::DataBits>(ui->dataBitsComboBox->currentText().toInt());
    set.parity = static_cast<QSerialPort::Parity>(ui->parityComboBox->currentText().toInt());
    set.stopBits = static_cast<QSerialPort::StopBits>(ui->stopBitsComboBox->currentText().toInt());
    set.flowControl = static_cast<QSerialPort::FlowControl>(ui->flowControlComboBox->currentText().toInt());
    return set;
}

void SerialConfigBox::connectSerial()
{
    emit applySerial(getSerialSettings());
}

void SerialConfigBox::closeSerialSlot()
{
    emit closeSerialSignal();
}

void SerialConfigBox::setConnectionButtons(bool success)
{
    ui->connectButton->setDisabled(success);
    ui->disconnectButton->setEnabled(success);
}
