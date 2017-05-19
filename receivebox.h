#ifndef RECEIVEBOX_H
#define RECEIVEBOX_H

#include <QWidget>
#include <QBitArray>
#include <socket.h>

namespace Ui {
class ReceiveBox;
}

class ReceiveBox : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveBox(QWidget *parent = 0);
    ~ReceiveBox();

public slots:
    void displayMessage(A825_MSG* msg);
    void clearTable();

private:
    Ui::ReceiveBox *ui;
    QString rxData;
    int count = 0;

    enum ReceiveTableHeaders
    {
        LCC,
        FID,
        FSB,
        DOC,
        LCL,
        PVT,
        RCI,
        PARAMETER,
        VALUE,
        UNIT
    };

public:

};

#endif // RECEIVEBOX_H
