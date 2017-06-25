#include "transmitbox.h"
#include "ui_transmitbox.h"

TransmitBox::TransmitBox(QWidget *parent, Profile *prof) :
    QWidget(parent),
    ui(new Ui::TransmitBox)
{
    ui->setupUi(this);
    profile = prof;
    comp1 = new OTM_MsgComposer(this, profile);
    comp2 = new PTP_MsgComposer(this, profile);
    ui->otmLayout->insertWidget(0, comp1);
    ui->ptpLayout->insertWidget(0, comp2);

    connect(ui->sendOtmButton, SIGNAL(clicked(bool)), this, SLOT(sendClickedHandle()));
    connect(ui->sendPtpButton, SIGNAL(clicked(bool)), this, SLOT(sendPTPClickedHandle()));
}

TransmitBox::~TransmitBox()
{
    delete ui;
}

void TransmitBox::sendClickedHandle()
{
    A825_MSG *msg = new A825_MSG;
    comp1->setArincMsg(msg);
    emit messageToSend(msg);
}

void TransmitBox::sendPTPClickedHandle()
{
    A825_MSG *msg = new A825_MSG;
    comp2->setArincMsg(msg);
    emit messageToSend(msg);
}
