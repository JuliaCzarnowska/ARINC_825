#ifndef PTP_MSGCOMPOSER_H
#define PTP_MSGCOMPOSER_H

#include <QWidget>
#include <socket.h>
#include <profile.h>

namespace Ui {
class PTP_MsgComposer;
}

class PTP_MsgComposer : public QWidget
{
    Q_OBJECT

public:
    explicit PTP_MsgComposer(QWidget *parent = 0, Profile* prof = nullptr);
    ~PTP_MsgComposer();

    void setArincMsg(A825_MSG* msg);

private:
    Ui::PTP_MsgComposer *ui;
    Profile *profile;

private slots:
    void fillParameters();
};

#endif // PTP_MSGCOMPOSER_H
