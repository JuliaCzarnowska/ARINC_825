#include "socket.h"
#include <QDebug>
#include <QThread>

Socket::Socket()
{
    rx_write_index = 0;
    rx_read_index = 0;
    rxCan = new CAN_MSG[RX_BUFFSIZE];
    txCan = new CAN_MSG[TX_BUFFSIZE];
    serial = new QSerialPort();
    myProfile = new Profile();
    connect(serial, &QSerialPort::readyRead, this, handleReadyRead);

}

Socket::~Socket()
{
    delete serial;
    delete myProfile;
}

//SERIAL PORT CONNECTION FUNCTIONS
void Socket::openSerialPort(SerialConfigBox::SerialSettings settings)
{

    serial->setPortName(settings.name);
    serial->setBaudRate(settings.baudRate);
    serial->setDataBits(settings.dataBits);
    serial->setParity(settings.parity);
    serial->setStopBits(settings.stopBits);
    serial->setFlowControl(settings.flowControl);
    //add signals connection successful and unsuccessful
    if(serial->open(QIODevice::ReadWrite)){
        emit serialConnectionState(true);
        readyToReceive();
    }else{
        emit serialConnectionState(false);
    }
}

void Socket::closeSerialPort()
{
    if(serial->isOpen())
        serial->close();
    emit serialConnectionState(false);
}

// function reads all available bytes from serial port and puts raw messages in rxCan buffer
int Socket::readRawMessage(CAN_MSG *msg)
{
    unsigned int id[4];
    int resp, count;

    while(serialBuffer.size() >= PKT_SIZE)
    {
        CAN_MSG* tmpMsg = new CAN_MSG;
        count = serialBuffer[0];
        tmpMsg->byte_count = count;
        for(int i = 0; i < count; i++){
            tmpMsg->data[i] = serialBuffer[i+1];
        }
        tmpMsg->frame_type = serialBuffer[1+count];
        id[0] = (unsigned int) ((serialBuffer[2+count] << 24) & 0x1F000000);
        id[1] = (unsigned int) ((serialBuffer[3+count] << 16) & 0xFF0000);
        id[2] = (unsigned int) ((serialBuffer[4+count] << 8) & 0xFF00);
        id[3] = (unsigned int) (serialBuffer[5+count] & 0xFF);
        tmpMsg->identifier = id[0]|id[1]|id[2]|id[3];
        //TODO check if its a proper message
        serialBuffer.remove(0,15);
        //inserting received message into rxCan circullar buffer
        rxCan[rx_write_index] = *tmpMsg;
        if(rx_write_index >= (RX_BUFFSIZE - 1))
            rx_write_index = 0;
        else
            rx_write_index += 1;
    }

// returning next RAW message from rxCan
    if(rx_write_index != rx_read_index){
        *msg = rxCan[rx_read_index];
        if(rx_read_index >= (RX_BUFFSIZE -1))
            rx_read_index = 0;
        else
            rx_read_index += 1;
        resp = OK;
    }else{
        resp = NO_NEW_MSG;
    }
    return resp;
}

// function returns next ARINC 825 message
int Socket::readA825Message(A825_MSG* msg)
{
    CAN_MSG *raw = new CAN_MSG;
    int resp, i;

    // getting next RAW CAN Message from rxCan buffer
    resp = readRawMessage(raw);

    if(resp == OK){
        for(i = 0; i < raw->byte_count; i++)
            msg->data[i] = raw->data[i];

        decodeA825Identifier((CAN_ID) raw->identifier, &(msg->identifier));
    }
    return resp;
}

void Socket::decodeA825Identifier(CAN_ID canID, A825_ID *arincID)
{
    arincID->lcc = (unsigned char) ((canID >> 26) & 0x7);
    arincID->srcfid = (unsigned char) ((canID >> 19) & 0x7f);
    arincID->cltfid = (unsigned char) ((canID >> 19) & 0x7f);
    arincID->fsb = (unsigned char) ((canID >> 18) & 0x1);
    arincID->smt = (unsigned char) ((canID >> 18) & 0x1);
    arincID->lcl = (unsigned char) ((canID >> 17) & 0x1);
    arincID->pvt = (unsigned char) ((canID >> 16) & 0x1);
    arincID->rci = (unsigned char) (canID & 0x3);
    arincID->sfid = (unsigned char) ((canID >> 9) & 0x7f);
    arincID->sid = (unsigned char) ((canID >> 2) & 0x7f);
    arincID->doc = (unsigned char) ((canID >> 2) & 0x3fff);
}

void Socket::sendControlMessage(unsigned char command)
{
    QByteArray* ctrlMsg = new QByteArray();
    ctrlMsg->append(CTRL_MSG);
    ctrlMsg->append(command);
    const char * data = ctrlMsg->data();
    int resp = serial->write(data, MAX_CTRL_PKT_SIZE);
    if(resp == -1)
        qDebug() << "lipa";
    delete ctrlMsg;
}

void Socket::handleReadyRead()
{
    serialBuffer.append(serial->readAll());
    int resp = serialBuffer.size();
    while(serialBuffer.size() >= PKT_SIZE)
    {
        A825_MSG* msg = new A825_MSG();
        resp = readA825Message(msg);
        while(resp != NO_NEW_MSG)
        {
            qDebug() << "nowa wiadomość!!";
            emit messageToDisplay(msg);
            resp = readA825Message(msg);
        }
    }
}

void Socket::readyToReceive()
{
    sendControlMessage(READY_TO_RECEIVE);
}

