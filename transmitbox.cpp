#include "transmitbox.h"
#include "ui_transmitbox.h"

TransmitBox::TransmitBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransmitBox)
{
    ui->setupUi(this);
    comp1 = new ARINC_MSG_composer(this);
    ui->transmitLayout->addWidget(comp1);
}

TransmitBox::~TransmitBox()
{
    delete ui;
}

void TransmitBox::setProfile(Profile *p)
{
    profile = p;
}
