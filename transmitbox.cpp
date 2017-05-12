#include "transmitbox.h"
#include "ui_transmitbox.h"

TransmitBox::TransmitBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransmitBox)
{
    ui->setupUi(this);
}

TransmitBox::~TransmitBox()
{
    delete ui;
}
