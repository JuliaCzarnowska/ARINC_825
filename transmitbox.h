#ifndef TRANSMITBOX_H
#define TRANSMITBOX_H

#include <QWidget>
#include <arinc_msg_composer.h>

namespace Ui {
class TransmitBox;
}

class TransmitBox : public QWidget
{
    Q_OBJECT

public:
    explicit TransmitBox(QWidget *parent = 0);
    ~TransmitBox();

private:
    Ui::TransmitBox *ui;
    ARINC_MSG_composer* comp1;
};

#endif // TRANSMITBOX_H
