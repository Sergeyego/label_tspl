#include "dialogcmd.h"
#include "ui_dialogcmd.h"

DialogCmd::DialogCmd(QString cmd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCmd)
{
    ui->setupUi(this);
    ui->plainTextEdit->setPlainText(cmd);
    connect(ui->pushButtonGo,SIGNAL(clicked(bool)),this,SLOT(goCmd()));
}

DialogCmd::~DialogCmd()
{
    delete ui;
}

void DialogCmd::goCmd()
{
    emit cmdPrint(ui->plainTextEdit->toPlainText());
}
