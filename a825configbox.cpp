#include "a825configbox.h"
#include "ui_a825configbox.h"

A825ConfigBox::A825ConfigBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::A825ConfigBox)
{
    ui->setupUi(this);
    ui->textBrowser->hide();
    connect(ui->profileButton, SIGNAL(clicked(bool)), this, SLOT(profileButtonClicked()));
}

A825ConfigBox::~A825ConfigBox()
{
    delete ui;
}

void A825ConfigBox::profileButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Json File (*.json)");

    QStringList pieces = fileName.split( "/" );
    QString profileFile = pieces.value( pieces.length() - 1 );

    ui->textBrowser->show();
    ui->textBrowser->setText(profileFile);
    emit newProfileChoice(fileName);

}

void A825ConfigBox::initializeButtonClicked()
{

}
