#include "a825configbox.h"
#include "ui_a825configbox.h"

A825ConfigBox::A825ConfigBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::A825ConfigBox)
{
    ui->setupUi(this);
    ui->textBrowser->hide();
    fillParameters();
    connect(ui->profileButton, SIGNAL(clicked(bool)), this, SLOT(profileButtonClicked()));
    ui->statusLabel->setText(tr("Status: %1").arg("OFF"));
    ui->modeLabel->setText(tr("Mode: %1").arg("Normal"));
    ui->bitRateLabel_2->setText(tr("Bit Rate: %1").arg("1000 kbit/s"));

    connect(ui->initializeButton, SIGNAL(clicked(bool)), this, SLOT(initializeButtonClicked()));
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
    if(ui->textBrowser->isVisible())
    {
        ui->modeLabel->clear();
        ui->bitRateLabel_2->clear();
        ui->statusLabel->clear();

        ui->statusLabel->setText(tr("Status: %1").arg("ON"));
        QString mode;
        if(ui->monitorModeCheckBox->isChecked())
            mode.append("Monitor");

        if(ui->loopbackModeCheckBox->isChecked()){
            if(mode.size() > 0)
                mode.append("/");
            mode.append("Loopback");
        }

        if(ui->sleepModeCheckBox->isChecked()){
            if(mode.size() > 0)
                mode.append("/");
            mode.append("Sleep");
        }
        if(mode.size()==0)
            mode.append("Normal");
        ui->modeLabel->setText(tr("Mode: %1").arg(mode));
        ui->bitRateLabel_2->setText(tr("Bit Rate: %1 %2").arg(ui->bitRateComboBox->currentText(), "kbit/s"));
    }else{
        QMessageBox noProfile;
        noProfile.setInformativeText("Select a communication profile file!");
        noProfile.exec();
    }
}

void A825ConfigBox::fillParameters()
{
    QStringList bitrates;
    bitrates << "1000" << "500" << "250" << "125" << "83.333";
    ui->bitRateComboBox->addItems(bitrates);
}
