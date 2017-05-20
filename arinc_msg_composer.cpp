#include "arinc_msg_composer.h"
#include "ui_arinc_msg_composer.h"

ARINC_MSG_composer::ARINC_MSG_composer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ARINC_MSG_composer)
{
    ui->setupUi(this);
}

ARINC_MSG_composer::~ARINC_MSG_composer()
{
    delete ui;
}

void ARINC_MSG_composer::fillParameters(Profile* profile)
{
    for(auto iter = profile->lccMap.begin(); iter != profile->lccMap.end(); iter++)
    {

    }
}
