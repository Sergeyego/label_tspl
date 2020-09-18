#include "dialogsettings.h"
#include "ui_dialogsettings.h"

DialogSettings::DialogSettings(TPrinter *p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    printer=p;

    ui->lineEditIp->setText(printer->getIp());
    ui->spinBoxPort->setValue(printer->getPort());

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(ui->pushButtonCal,SIGNAL(clicked(bool)),this,SLOT(calibr()));
    connect(ui->pushButtonDownload,SIGNAL(clicked(bool)),this,SLOT(download()));
    connect(ui->pushButtonGet,SIGNAL(clicked(bool)),this,SLOT(getSettings()));
    connect(ui->lineEditIp,SIGNAL(textChanged(QString)),printer,SLOT(setHost(QString)));
    connect(ui->spinBoxPort,SIGNAL(valueChanged(int)),printer,SLOT(setPort(int)));
    connect(ui->pushButtonSmall,SIGNAL(clicked(bool)),this,SLOT(setSmallLbl()));
    connect(ui->pushButtonBig,SIGNAL(clicked(bool)),this,SLOT(setBigLbl()));
}

DialogSettings::~DialogSettings()
{
    delete ui;
}


void DialogSettings::parceCfg(QString cfg)
{
    QStringList list=cfg.split("\n");
    ui->listWidgetFiles->clear();
    //qDebug()<<list;
    for (int i=0; i<list.size(); i++){
        QString s=list.at(i);
        QRegExp reg("^(.*)=(.*)$");
        if (reg.indexIn(s)!=-1){
            QString par=reg.cap(1);
            QStringList vals=reg.cap(2).split("\r");
            //qDebug()<<reg.cap(1)<<reg.cap(2);
            if (par==QString("BLINE SIZE")){
                if (vals.size()){
                    ui->doubleSpinBoxGap->setValue(vals.at(0).toInt()/8.0);
                }
            } else if (par==QString("PAPER SIZE")){
                if (vals.size()){
                    ui->doubleSpinBoxWidth->setValue(vals.at(0).toInt()/8.0);
                }
            } else if (par==QString("PAPER WIDTH")){
                if (vals.size()){
                    ui->doubleSpinBoxHeiht->setValue(vals.at(0).toInt()/8.0);
                }
            } else if (par==QString("FILES")){
                for (int j=0; j<vals.size()-1; j++){
                    ui->listWidgetFiles->addItem(vals.at(j));
                }
            }
        }
    }
}

void DialogSettings::calibr()
{
    QString cmd;
    cmd+=QString("SIZE %1 mm, %2 mm\n").arg(ui->doubleSpinBoxHeiht->value()).arg(ui->doubleSpinBoxWidth->value());
    cmd+=QString("BLINEDETECT %1, %2\n").arg(ui->doubleSpinBoxWidth->value()*8.0).arg(ui->doubleSpinBoxGap->value()*8.0);
    printer->printDecodeData(cmd);
}

void DialogSettings::download()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"),QDir::homePath(), tr("bmp Files (*.bmp)"));
    if (!fileName.isEmpty()){
        QByteArray cmd;
        QFile f(fileName);
        QFileInfo fi(f);
        if (f.open(QIODevice::ReadOnly)){
            qDebug()<<fi.fileName();
            QString d=QString("DOWNLOAD F,\"%1\",%2,").arg(fi.fileName()).arg(f.size());
            cmd.append(d.toLocal8Bit().data());
            cmd.append(f.readAll());
            //cmd.append("\n");
            printer->printData(cmd);
        }
    }
}


void DialogSettings::getSettings()
{
    QString cmd;
    cmd+=QString("OUT \"MODEL=\";GETSETTING$(\"SYSTEM\", \"INFORMATION\", \"MODEL\")\n");
    cmd+=QString("OUT \"BLINE SIZE=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"BLINE SIZE\")\n");
    cmd+=QString("OUT \"PAPER SIZE=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"PAPER SIZE\")\n");
    cmd+=QString("OUT \"PAPER WIDTH=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"PAPER WIDTH\")\n");
    cmd+=QString("OUT \"FILES=\";~!F\n");
    QString s=printer->printDecodeData(cmd,100);
    parceCfg(s);
}

void DialogSettings::setBigLbl()
{
    ui->doubleSpinBoxGap->setValue(4.0);
    ui->doubleSpinBoxWidth->setValue(110.0);
    ui->doubleSpinBoxHeiht->setValue(95.0);
}

void DialogSettings::setSmallLbl()
{
    ui->doubleSpinBoxGap->setValue(4.0);
    ui->doubleSpinBoxWidth->setValue(101.6);
    ui->doubleSpinBoxHeiht->setValue(80.0);
}

