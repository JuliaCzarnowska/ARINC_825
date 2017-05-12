#ifndef TRANSMITBOX_H
#define TRANSMITBOX_H

#include <QWidget>

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
};

#endif // TRANSMITBOX_H
