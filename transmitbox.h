#ifndef TRANSMITBOX_H
#define TRANSMITBOX_H

#include <QWidget>
#include <otm_msgcomposer.h>
#include <ptp_msgcomposer.h>
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
    OTM_MsgComposer* comp1;
    PTP_MsgComposer* comp2;
};

#endif // TRANSMITBOX_H
