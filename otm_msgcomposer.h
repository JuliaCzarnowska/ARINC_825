#ifndef OTM_MSGCOMPOSER_H
#define OTM_MSGCOMPOSER_H

#include <QWidget>
#include <socket.h>
#include <profile.h>

namespace Ui {
class OTM_MsgComposer;
}

class OTM_MsgComposer : public QWidget
{
    Q_OBJECT

public:
    explicit OTM_MsgComposer(QWidget *parent = 0);
    ~OTM_MsgComposer();

    void fillParameters(Profile* prof);

private slots:
    void sendClickedHandle();
    void fidChangedHandle();

private:
    Ui::OTM_MsgComposer *ui;
    Profile *profile;
    void setArincMsg(A825_MSG* msg);
};

#endif // OTM_MSGCOMPOSER_H
