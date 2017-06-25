#ifndef RECEIVEBOX_H
#define RECEIVEBOX_H

#include <QWidget>
#include <QBitArray>
#include <socket.h>
#include <profile.h>


namespace Ui {
class ReceiveBox;
}

class ReceiveBox : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveBox(QWidget *parent = 0);
    ~ReceiveBox();

    void setProfile(Profile * p);

public slots:
    void displayMessage(A825_MSG* msg);
private slots:
    void clearTable();
    void saveTable();

private:
    Ui::ReceiveBox *ui;
    Profile* profile;
    int count = 0;
    int i=0;
    void setColumnWidths();

    enum ReceiveTableHeaders
    {
        LCC,
        FID,
        DOC,
        FSB,
        LCL,
        PVT,
        RCI,
        PARAMETER,
        VALUE,
        UNIT
    };
};

#endif // RECEIVEBOX_H
