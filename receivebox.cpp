#include "receivebox.h"
#include "ui_receivebox.h"

#include <QString>
#include <QDebug>

ReceiveBox::ReceiveBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiveBox)
{
    ui->setupUi(this);
    ui->receiveTable->setColumnWidth(PARAMETER, 100);
    ui->receiveTable->setColumnWidth(LCC, 60);
    ui->receiveTable->setColumnWidth(UNIT, 60);
    ui->receiveTable->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearTable()));
}

ReceiveBox::~ReceiveBox()
{
    delete ui;
}

void ReceiveBox::displayMessage(A825_MSG* msg)
{
    QTableWidgetItem * lcc = new QTableWidgetItem(profile->lccMap[msg->identifier.lcc]);
    QTableWidgetItem * fid = new QTableWidgetItem(QString::number(msg->identifier.srcfid));
    QTableWidgetItem * fsb = new QTableWidgetItem(QString::number(msg->identifier.fsb));
    QTableWidgetItem * lcl = new QTableWidgetItem(QString::number(msg->identifier.lcl));
    QTableWidgetItem * pvt = new QTableWidgetItem(QString::number(msg->identifier.pvt));
    QTableWidgetItem * doc = new QTableWidgetItem(QString::number(msg->identifier.doc));
    QTableWidgetItem * rci = new QTableWidgetItem(QString::number(msg->identifier.rci));
    QTableWidgetItem * data = new QTableWidgetItem(QString::number((int)msg->data));
    count = ui->receiveTable->rowCount();
    ui->receiveTable->insertRow(ui->receiveTable->rowCount());
    ui->receiveTable->setItem(count, LCC, lcc);
    ui->receiveTable->setItem(count, FID, fid);
    ui->receiveTable->setItem(count, FSB, fsb);
    ui->receiveTable->setItem(count, LCL, lcl);
    ui->receiveTable->setItem(count, PVT, pvt);
    ui->receiveTable->setItem(count, RCI, rci);
    ui->receiveTable->setItem(count, DOC, doc);
    ui->receiveTable->setItem(count, VALUE, data);
}

void ReceiveBox::clearTable()
{
    int count = ui->receiveTable->rowCount();
    for(int i = 0; i < count; i++)
    {
        ui->receiveTable->removeRow(0);
    }
}

void ReceiveBox::setProfile(Profile *p)
{
    profile = p;
}
