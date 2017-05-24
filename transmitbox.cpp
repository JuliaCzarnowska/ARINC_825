#include "transmitbox.h"
#include "ui_transmitbox.h"

TransmitBox::TransmitBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransmitBox)
{
    ui->setupUi(this);
    comp1 = new OTM_MsgComposer(this);
    comp2 = new PTP_MsgComposer(this);
    ui->otmLayout->addWidget(comp1, Qt::AlignLeft);
    ui->transmitLayout->addWidget(comp2);

    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(sendClickedHandle()));
}

TransmitBox::~TransmitBox()
{
    delete ui;
}

void TransmitBox::setProfile(Profile *p)
{
    profile = p;
    comp1->fillParameters(p);
}

void TransmitBox::sendClickedHandle()
{
    A825_MSG *msg = new A825_MSG;
    comp1->setArincMsg(msg);
    emit messageToSend(msg);
}
