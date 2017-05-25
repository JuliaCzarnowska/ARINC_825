#ifndef SOCKET_H
#define SOCKET_H

#include "a825.h"
#include "serialconfigbox.h"
#include "profile.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <QMap>
#include <QByteArray>
#include <QDataStream>

#define RX_BUFFSIZE             30
#define TX_BUFFSIZE             64
#define PKT_SIZE                15
#define MAX_CTRL_PKT_SIZE       2
//#define MAX_ARINC_MSG_COUNT     50

// function responses
#define OK                   0
#define BLEEH               -1
#define NO_NEW_MSG          -2

// values for Ctrl Messages
#define READY_TO_RECEIVE     ((unsigned char)0x01)

//opcodes
#define CAN_READ            ((unsigned char)0x01)
#define CTRL_MSG            ((unsigned char)0x02)

// frame types
#define DATA_FRAME      1
#define REMOTE_FRAME    2
typedef unsigned int CAN_ID;

// ARINC 825 message structure
typedef struct
{
    unsigned char   lcc;     // Logical Communication Channel
    unsigned char   srcfid;  // Source Function Code Identifier (only OTM)
    unsigned char   cltfid;  // Client Function Code Identifier (only PTP)
    unsigned char   fsb;     // Functional Status Bit (only OTM)
    unsigned char   smt;     // Service Message Type (only PTP)
    unsigned char   lcl;     // "Local" Bit
    unsigned char   pvt;     // "Private" Bit
    unsigned char   rci;     // Redundancy Channel Identifier
    unsigned char   sfid;    // Server FID (only PTP)
    unsigned char   sid;     // Server ID  (only PTP)
    unsigned int    doc;     // Data Object Code (only OTM)

} A825_ID;

typedef struct
{
    char            data[8];
    char            byte_count;
    char            frame_type;
//    unsigned short  msg_control;
    A825_ID         identifier;
//    unsigned short  can_status;
//    unsigned short  error_counter;
//    unsigned int    time_stamp_hi;
//    unsigned int    time_stamp_lo;

} A825_MSG;

typedef struct
{
    char            data[8];
    char            byte_count;
    char            frame_type;
//    unsigned short  msg_control;
    CAN_ID          identifier;
//    unsigned short  can_status;
//    unsigned short  error_counter;
//    unsigned int    time_stamp_hi;
//    unsigned int    time_stamp_lo;

} CAN_MSG;

class Socket : public QObject
{
    Q_OBJECT

private:
    QSerialPort *serial;
    QByteArray serialBuffer;
    SerialConfigBox::SerialSettings currentSettings;
    CAN_MSG *rxCan;     //CAN receive buffer pointer
    CAN_MSG *txCan;     //CAN transmit buffer pointer

    int rx_write_index;
    int rx_read_index;

// function prototypes
    int readRawMessage(CAN_MSG *msg);
    int readA825Message(A825_MSG *msg);
    CAN_ID composeA825Identifier(A825_ID *arincID);
    void decodeA825Identifier(CAN_ID canID, A825_ID *arincID);
    void sendControlMessage(unsigned char command);
    int writeRawMessage(CAN_MSG *msg);
signals:
    void serialConnectionState(bool success);
    void messageToDisplay(A825_MSG *msg);

public slots:
    void openSerialPort(SerialConfigBox::SerialSettings settings);
    void closeSerialPort();
    void handleReadyRead();
    void readyToReceive();
    void writeA825Message(A825_MSG *msg);

public:
    Socket();
    ~Socket();

};

#endif // SOCKET_H
