#include "ptp_msgcomposer.h"
#include "ui_ptp_msgcomposer.h"

PTP_MsgComposer::PTP_MsgComposer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PTP_MsgComposer)
{
    ui->setupUi(this);
}

PTP_MsgComposer::~PTP_MsgComposer()
{
    delete ui;
}
