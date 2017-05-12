#include "socket.h"
#include <QDebug>
#include <QThread>

Socket::Socket()
{
    rx_write_index = 0;
    rx_read_index = 0;
    rx_can = new CAN_MSG[RX_BUFFSIZE];
    tx_can = new CAN_MSG[TX_BUFFSIZE];
    serial = new QSerialPort();
    connect(serial, &QSerialPort::readyRead, this, startListening);

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

// function reads all available bytes from serial port and puts raw messages in rx_can buffer
int Socket::readRawMessage(CAN_MSG *msg)
{
    static char rx_buf[MAX_PKT_SIZE];
    static CAN_MSG tmp_msg;
    unsigned int id[4];
    int resp, count;
    int bytes = serial->read((char*) &rx_buf, MAX_PKT_SIZE);

    while(bytes > 0)
    {
        count = rx_buf[0];
        tmp_msg.byte_count = count;
        if(rx_buf[9] == 1)
            qDebug() << "lalalala";
        for(int i = 0; i < count; i++){
            tmp_msg.data[i] = rx_buf[i+1];
        }
        tmp_msg.frame_type = rx_buf[1+count];
        id[0] = (unsigned int) ((rx_buf[2+count] << 24) & 0x1F000000);
        id[1] = (unsigned int) ((rx_buf[3+count] << 16) & 0xFF0000);
        id[2] = (unsigned int) ((rx_buf[4+count] << 8) & 0xFF00);
        id[3] = (unsigned int) (rx_buf[2+count] & 0xFF);
        tmp_msg.identifier = id[0]|id[1]|id[2]|id[3];
        //inserting received message into rx_can circullar buffer
        rx_can[rx_write_index] = tmp_msg;
        if(rx_write_index >= (RX_BUFFSIZE - 1))
            rx_write_index = 0;
        else
            rx_write_index += 1;
        //checking for another message
        bytes = serial->read((char*) &rx_buf, MAX_PKT_SIZE);
    }

// returning next RAW message from rx_can
    if(rx_write_index != rx_read_index){
        *msg = rx_can[rx_read_index];
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
    CAN_MSG raw;
    int resp, i;
    unsigned char *raw_ptr, *out_ptr;

    // getting next RAW CAN Message from rx_can buffer
    resp = readRawMessage((CAN_MSG *) &raw);

    if(resp == OK){
        raw_ptr = (unsigned char *) &(raw.data[0]);
        out_ptr = (unsigned char *) &(msg->data[0]);

        for(i = 0; i < raw.byte_count; i++)
            out_ptr[i] = raw_ptr[i];

        decodeA825Identifier((CAN_ID) raw.identifier, &(msg->identifier));
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
}

void Socket::startListening()
{
    A825_MSG* msg;
    int resp;

    resp = readA825Message(msg);
    while(resp != NO_NEW_MSG)
    {
        emit messageToDisplay(msg);
        resp = readA825Message(msg);
    }
}

void Socket::readyToReceive()
{
    sendControlMessage(READY_TO_RECEIVE);
}

