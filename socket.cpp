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
    connect(serial, &QSerialPort::readyRead, this, handleReadyRead);

}

Socket::~Socket()
{
    delete serial;
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

void Socket::sendControlMessage(unsigned char command)
{
    QByteArray* ctrlMsg = new QByteArray();
    ctrlMsg->append(CTRL_MSG);
    ctrlMsg->append(command);
    ctrlMsg->append(QByteArray(13, 0));
    const char * data = ctrlMsg->data();
    int resp = serial->write(data, MAX_CTRL_PKT_SIZE);
    if(resp == -1)
        qDebug() << "lipa";
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
//    sendControlMessage(READY_TO_RECEIVE);
}

void Socket::writeA825Message(A825_MSG *msg)
{
    CAN_MSG *raw = new CAN_MSG;
    int i;
    raw->byte_count = msg->byte_count;
    raw->frame_type = msg->frame_type;
    for(i = 0; i < raw->byte_count; i++)
        raw->data[i] = msg->data[i];

    raw->identifier = composeA825Identifier(&(msg->identifier));
    writeRawMessage(raw);
}

int Socket::writeRawMessage(CAN_MSG *msg)
{
    int resp;
    QByteArray* canMsg = new QByteArray();
    // int -> QByteArray
    QByteArray id;
    QDataStream stream(&id, QIODevice::WriteOnly);
    stream <<msg->identifier;

    canMsg->append(CAN_READ);
    canMsg->append(msg->byte_count);
    canMsg->append(QByteArray(msg->data, 8));
    canMsg->append(DATA_FRAME);
    canMsg->append(id);


    const char * data = canMsg->data();
    resp = serial->write(data, PKT_SIZE);
    qDebug() << resp;
    return resp;
}

CAN_ID Socket::composeA825Identifier(A825_ID *arincID)
{
    unsigned int id[8];
    CAN_ID canID;

    id[0] = (unsigned int) ((arincID->lcc << 26) & 0x1c000000);
    id[3] = (unsigned int) ((arincID->lcl << 17) & 0x00020000);
    id[4] = ((unsigned int) (arincID->pvt << 16) & 0x00010000);

    if(arincID->lcc == NSC || arincID->lcc == TMC)
    {
        id[1] = (unsigned int) ((arincID->cltfid << 19) & 0x03f80000);
        id[2] = (unsigned int) ((arincID->smt << 18) & 0x00040000);
        id[5] = (unsigned int) ((arincID->sfid << 9) & 0x0000fe00);
        id[6] = (unsigned int) ((arincID->sid  << 2) & 0x000001fc);
        id[7] = (unsigned int) (arincID->rci & 0x00000003);

    }else{
        id[1] = (unsigned int) ((arincID->srcfid << 19) & 0x03f80000);
        id[2] = (unsigned int) ((arincID->fsb << 18) & 0x00040000);
        id[5] = (unsigned int) ((arincID->doc << 2) & 0x0000fffc);
        id[6] = (unsigned int) (arincID->rci & 0x00000003);
        id[7] = 0;
    }
    return canID = id[0]|id[1]|id[2]|id[3]|id[4]|id[5]|id[6]|id[7];

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
