#include "transmitbox.h"
#include "ui_transmitbox.h"

TransmitBox::TransmitBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransmitBox)
{
    ui->setupUi(this);
    comp1 = new OTM_MsgComposer(this);
    comp2 = new PTP_MsgComposer(this);
    ui->transmitLayout->addWidget(comp1);
    ui->transmitLayout->addWidget(comp2);
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
