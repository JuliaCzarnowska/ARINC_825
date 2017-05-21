#ifndef PTP_MSGCOMPOSER_H
#define PTP_MSGCOMPOSER_H

#include <QWidget>

namespace Ui {
class PTP_MsgComposer;
}

class PTP_MsgComposer : public QWidget
{
    Q_OBJECT

public:
    explicit PTP_MsgComposer(QWidget *parent = 0);
    ~PTP_MsgComposer();

private:
    Ui::PTP_MsgComposer *ui;
};

#endif // PTP_MSGCOMPOSER_H
