#include "ptp_msgcomposer.h"
#include "ui_ptp_msgcomposer.h"

PTP_MsgComposer::PTP_MsgComposer(QWidget *parent, Profile *prof) :
    QWidget(parent),
    ui(new Ui::PTP_MsgComposer)
{
    profile = prof;
    ui->setupUi(this);
}

PTP_MsgComposer::~PTP_MsgComposer()
{
    delete ui;
}

void PTP_MsgComposer::setArincMsg(A825_MSG* msg)
{
    msg->identifier.lcc = (unsigned char) (ui->lccComboBox->currentData().toInt());
    msg->identifier.cltfid = (unsigned char) (ui->cltFidComboBox->currentData().toInt());
    msg->identifier.smt = (unsigned char) (ui->smtCheckBox->isChecked());
    msg->identifier.lcl = (unsigned char) (ui->lclCheckBox->isChecked());
    msg->identifier.pvt = (unsigned char) (ui->pvtCheckBox->isChecked());
    msg->identifier.sfid = (unsigned char) (ui->srvFidComboBox->currentData().toInt());
    msg->identifier.rci = (unsigned char) (ui->rciComboBox->currentData().toInt());
    msg->identifier.sid = (unsigned char) (ui->spinBox->value());
    msg->byte_count = 8;
    msg->frame_type = CAN_READ;
}

void PTP_MsgComposer::fillParameters()
{
    ui->lccComboBox->clear();
    for(auto iter = profile->lccMap.begin(); iter != profile->lccMap.end(); iter++)
    {
        ui->lccComboBox->insertItem(iter.key(),iter.value(), QVariant(iter.key()));
    }
    ui->cltFidComboBox->clear();
    ui->srvFidComboBox->clear();
    for(auto iter = profile->fidMap.begin(); iter != profile->fidMap.end(); iter++)
    {
        ui->cltFidComboBox->insertItem(iter.key(),iter.value().name, QVariant(iter.key()));
        ui->srvFidComboBox->insertItem(iter.key(),iter.value().name, QVariant(iter.key()));
    }
    ui->rciComboBox->clear();
    for(auto iter = profile->rciMap.begin(); iter != profile->rciMap.end(); iter++)
    {
        ui->rciComboBox->insertItem(iter.key(),iter.value(), QVariant(iter.key()));
    }
}
