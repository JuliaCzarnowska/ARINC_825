#ifndef TRANSMITBOX_H
#define TRANSMITBOX_H

#include <QWidget>
#include <arinc_msg_composer.h>
#include <profile.h>

namespace Ui {
class TransmitBox;
}

class TransmitBox : public QWidget
{
    Q_OBJECT

public:
    explicit TransmitBox(QWidget *parent = 0);
    ~TransmitBox();

    void setProfile(Profile * p);

private:
    Ui::TransmitBox *ui;
    Profile* profile;
    ARINC_MSG_composer* comp1;
};

#endif // TRANSMITBOX_H
