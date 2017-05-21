#include "otm_msgcomposer.h"
#include "ui_otm_msgcomposer.h"

OTM_MsgComposer::OTM_MsgComposer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OTM_MsgComposer)
{
    ui->setupUi(this);
    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(sendClickedHandle()));
    connect(ui->fidComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(fidChangedHandle()));
}

OTM_MsgComposer::~OTM_MsgComposer()
{
    delete ui;
}

void OTM_MsgComposer::sendClickedHandle()
{
    A825_MSG *msg = new A825_MSG;
    setArincMsg(msg);
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

}

void OTM_MsgComposer::fillParameters(Profile* prof)
{
    profile = prof;
    for(auto iter = profile->lccMap.begin(); iter != profile->lccMap.end(); iter++)
    {
        ui->lccComboBox->insertItem(iter.key(),iter.value(), QVariant(iter.key()));
    }

    for(auto iter = profile->fidMap.begin(); iter != profile->fidMap.end(); iter++)
    {
        ui->fidComboBox->insertItem(iter.key(),iter.value().name, QVariant(iter.key()));
    }
}
