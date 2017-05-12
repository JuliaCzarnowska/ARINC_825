#ifndef SERIALCONFIGBOX_H
#define SERIALCONFIGBOX_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class SerialConfigBox;
}

class SerialConfigBox : public QWidget
{
    Q_OBJECT

public:
    struct SerialSettings {
        QString name;
        QSerialPort::BaudRate baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    };

    explicit SerialConfigBox(QWidget *parent = 0);
    ~SerialConfigBox();

    SerialSettings getSerialSettings();

signals:
    void applySerial(SerialConfigBox::SerialSettings settings);
    void closeSerialSignal();

private slots:
    void scanForPorts();
    void connectSerial();
    void closeSerialSlot();
    void setConnectionButtons(bool success);

private:
    void fillParameters();

private:
    Ui::SerialConfigBox *ui;

};

#endif // SERIALCONFIGBOX_H
