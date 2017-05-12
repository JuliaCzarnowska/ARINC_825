#include "receivebox.h"
#include "ui_receivebox.h"

#include <QString>

ReceiveBox::ReceiveBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiveBox)
{
    ui->setupUi(this);
    ui->receiveTable->setColumnWidth(PARAMETER, 100);
}

ReceiveBox::~ReceiveBox()
{
    delete ui;
}

void ReceiveBox::displayMessage(A825_MSG* msg)
{
    count = ui->receiveTable->rowCount() - 1;
    ui->receiveTable->insertRow(ui->receiveTable->rowCount());

}

