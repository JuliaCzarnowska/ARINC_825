#include "otm_msgcomposer.h"
#include "ui_otm_msgcomposer.h"

OTM_MsgComposer::OTM_MsgComposer(QWidget *parent, Profile *prof) :
    QWidget(parent),
    ui(new Ui::OTM_MsgComposer)
{
    profile = prof;
    ui->setupUi(this);
    connect(ui->fidComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(fidChangedHandle()));
}

OTM_MsgComposer::~OTM_MsgComposer()
{
    delete ui;
}

void OTM_MsgComposer::fidChangedHandle()
{
    ui->docComboBox->clear();
    int code = ui->fidComboBox->currentData().toInt();
    for( auto iter = profile->fidMap[code].params.begin();
         iter != profile->fidMap[code].params.end(); iter++)
    {
        ui->docComboBox->insertItem(iter.key(), iter.value().name, QVariant(iter.key()));
    }
}

void OTM_MsgComposer::setArincMsg(A825_MSG* msg)
{
    msg->identifier.lcc = (unsigned char) (ui->lccComboBox->currentData().toInt());
    msg->identifier.srcfid = (unsigned char) (ui->fidComboBox->currentData().toInt());
    msg->identifier.fsb = (unsigned char) (ui->fsbCheckBox->isChecked());
    msg->identifier.lcl = (unsigned char) (ui->lclCheckBox->isChecked());
    msg->identifier.pvt = (unsigned char) (ui->pvtCheckBox->isChecked());
    msg->identifier.doc = (unsigned char) (ui->docComboBox->currentData().toInt());
    msg->identifier.rci = (unsigned char) (ui->rciComboBox->currentData().toInt());
    msg->byte_count = 8;
    QString data1 = ui->dataLineEdit->text();
    data1.size();
    QByteArray ba = data1.toLatin1();
    for(int i =0; i < 8; i++)
    {
        msg->data[i] = ba[i];
    }

    msg->frame_type = CAN_READ;
}

void OTM_MsgComposer::fillParameters()
{
    ui->lccComboBox->clear();
    for(auto iter = profile->lccMap.begin(); iter != profile->lccMap.end(); iter++)
    {
        if(iter.key() != 4 && iter.key() != 6 && iter.key() != 7)
            ui->lccComboBox->insertItem(iter.key(),iter.value(), QVariant(iter.key()));
    }
    ui->fidComboBox->clear();
    for(auto iter = profile->fidMap.begin(); iter != profile->fidMap.end(); iter++)
    {
        ui->fidComboBox->insertItem(iter.key(),iter.value().name, QVariant(iter.key()));
    }
    ui->rciComboBox->clear();
    for(auto iter = profile->rciMap.begin(); iter != profile->rciMap.end(); iter++)
    {
        ui->rciComboBox->insertItem(iter.key(),iter.value(), QVariant(iter.key()));
    }
}
