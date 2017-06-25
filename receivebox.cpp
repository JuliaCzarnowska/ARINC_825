#include "receivebox.h"
#include "ui_receivebox.h"

#include <QString>
#include <QDebug>

ReceiveBox::ReceiveBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiveBox)
{
    ui->setupUi(this);
    setColumnWidths();
    ui->receiveTable->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearTable()));
//    connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(saveTable()));
}

ReceiveBox::~ReceiveBox()
{
    delete ui;
}

void ReceiveBox::displayMessage(A825_MSG* msg)
{
    int channel = msg->identifier.lcc;
    QTableWidgetItem * lcc = new QTableWidgetItem(profile->lccMap[msg->identifier.lcc]);
    QTableWidgetItem * srcfid = new QTableWidgetItem(profile->fidMap[msg->identifier.srcfid].name);
    QTableWidgetItem * cltfid = new QTableWidgetItem(profile->fidMap[msg->identifier.cltfid].name);
    QTableWidgetItem * fsb = new QTableWidgetItem(QString::number(msg->identifier.fsb));
    QTableWidgetItem * smt = new QTableWidgetItem(QString::number(msg->identifier.smt));
    QTableWidgetItem * lcl = new QTableWidgetItem(QString::number(msg->identifier.lcl));
    QTableWidgetItem * pvt = new QTableWidgetItem(QString::number(msg->identifier.pvt));
    QTableWidgetItem * doc = new QTableWidgetItem(QString::number(msg->identifier.doc));

    QTableWidgetItem * parameter = new QTableWidgetItem(
                profile->fidMap[msg->identifier.srcfid].params[msg->identifier.doc].name);
    QTableWidgetItem * rci = new QTableWidgetItem(profile->rciMap[msg->identifier.rci]);
    QTableWidgetItem * data = new QTableWidgetItem(QString(msg->data));
    QTableWidgetItem * unit = new QTableWidgetItem(
                profile->fidMap[msg->identifier.srcfid].params[msg->identifier.doc].unit);
    QString service;
    service = data->text();
    if(data->text() == "0"){
        service = "Node Identification Service";
    }else if(data->text() == "1"){
        service = "Node Synchronisation Service";
    }

    QTableWidgetItem * service_item = new QTableWidgetItem(service);

    count = ui->receiveTable->rowCount();
    ui->receiveTable->insertRow(ui->receiveTable->rowCount());
    ui->receiveTable->setItem(count, LCC, lcc);
    ui->receiveTable->setItem(count, LCL, lcl);
    ui->receiveTable->setItem(count, PVT, pvt);
    ui->receiveTable->setItem(count, RCI, rci);
    if(channel == 4 || channel == 6 || channel == 7){
        ui->receiveTable->setItem(count, FID, cltfid);
        ui->receiveTable->setItem(count, FSB, smt);
        ui->receiveTable->setItem(count, PARAMETER, service_item);
    }else{
        ui->receiveTable->setItem(count, FID, srcfid);
        ui->receiveTable->setItem(count, FSB, fsb);
        ui->receiveTable->setItem(count, DOC, doc);
        ui->receiveTable->setItem(count, VALUE, data);
        ui->receiveTable->setItem(count, UNIT, unit);
        ui->receiveTable->setItem(count, PARAMETER, parameter);
    }
}

void ReceiveBox::setColumnWidths()
{
    ui->receiveTable->setColumnWidth(PARAMETER, 200);
    ui->receiveTable->setColumnWidth(FID, 180);
    ui->receiveTable->setColumnWidth(VALUE, 180);
    ui->receiveTable->setColumnWidth(LCC, 60);
    ui->receiveTable->setColumnWidth(UNIT, 60);
    ui->receiveTable->setColumnWidth(RCI, 30);
    ui->receiveTable->setColumnWidth(FSB, 30);
    ui->receiveTable->setColumnWidth(LCL, 30);
    ui->receiveTable->setColumnWidth(PVT, 30);
}

void ReceiveBox::clearTable()
{
    int count = ui->receiveTable->rowCount();
    for(int i = 0; i < count; i++)
    {
        ui->receiveTable->removeRow(0);
    }
}

void ReceiveBox::saveTable()
{

}

void ReceiveBox::setProfile(Profile *p)
{
    profile = p;
}
