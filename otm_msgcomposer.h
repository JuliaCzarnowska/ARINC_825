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
    explicit OTM_MsgComposer(QWidget *parent = 0, Profile* prof = nullptr);
    ~OTM_MsgComposer();

    void setArincMsg(A825_MSG* msg);

private slots:
    void fidChangedHandle();
    void fillParameters();

private:
    Ui::OTM_MsgComposer *ui;
    Profile *profile;

};

#endif // OTM_MSGCOMPOSER_H
