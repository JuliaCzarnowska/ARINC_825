#include "arinc_msg_composer.h"
#include "ui_arinc_msg_composer.h"

ARINC_MSG_composer::ARINC_MSG_composer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ARINC_MSG_composer)
{
    ui->setupUi(this);
    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(sendClickedHandle()));
}

ARINC_MSG_composer::~ARINC_MSG_composer()
{
    delete ui;
}

void ARINC_MSG_composer::sendClickedHandle()
{
    A825_MSG *msg = new A825_MSG;
    setArincMsg(msg);
}

void ARINC_MSG_composer::setArincMsg(A825_MSG* msg)
{

}
