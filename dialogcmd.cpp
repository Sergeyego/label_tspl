#include "dialogcmd.h"
#include "ui_dialogcmd.h"

DialogCmd::DialogCmd(QString cmd, TPrinter *p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCmd),
    printer(p)
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
    QString s=ui->plainTextEdit->toPlainText();
    printer->printDecodeData(s);
}
