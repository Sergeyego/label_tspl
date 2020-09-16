#include "dialogsettings.h"
#include "ui_dialogsettings.h"

DialogSettings::DialogSettings(QString ip, int port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    ui->lineEditIp->setText(ip);
    ui->spinBoxPort->setValue(port);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(ui->pushButtonCal,SIGNAL(clicked(bool)),this,SLOT(calibr()));
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

QString DialogSettings::getIp()
{
    return ui->lineEditIp->text();
}

int DialogSettings::getPort()
{
    return ui->spinBoxPort->value();
}

void DialogSettings::calibr()
{
    QString cmd;
    cmd.push_back(QString("SIZE %1 mm, %2 mm\n").arg(ui->doubleSpinBoxHeiht->value()).arg(ui->doubleSpinBoxWidth->value()));
    cmd.push_back(QString("BLINEDETECT %1, %2\n").arg(ui->doubleSpinBoxWidth->value()*8.0).arg(ui->doubleSpinBoxGap->value()*8.0));
    emit cmdPrint(cmd);
}
