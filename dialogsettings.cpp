#include "dialogsettings.h"
#include "ui_dialogsettings.h"

DialogSettings::DialogSettings(TPrinter *p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    printer=p;

    ui->comboBoxPrinters->addItems(printer->getPrinterList());
    ui->comboBoxPrinters->setCurrentText(printer->getPrinterName());

    ui->spinBoxDpi->setValue(printer->getDpi());

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(ui->pushButtonCal,SIGNAL(clicked(bool)),this,SLOT(calibr()));
    connect(ui->spinBoxDpi,SIGNAL(valueChanged(int)),printer,SLOT(setDpi(int)));

    connect(ui->comboBoxPrinters,SIGNAL(currentIndexChanged(QString)),printer,SLOT(setPrinterName(QString)));
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::setLblSize(double width, double heiht, double gap)
{
    ui->doubleSpinBoxGap->setValue(gap);
    ui->doubleSpinBoxWidth->setValue(width);
    ui->doubleSpinBoxHeiht->setValue(heiht);
}


/*void DialogSettings::parceCfg(QString cfg)
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
                    ui->doubleSpinBoxGap->setValue(vals.at(0).toInt()*printer->getDpi()/25.0);
                }
            } else if (par==QString("PAPER SIZE")){
                if (vals.size()){
                    ui->doubleSpinBoxWidth->setValue(vals.at(0).toInt()*printer->getDpi()/25.0);
                }
            } else if (par==QString("PAPER WIDTH")){
                if (vals.size()){
                    ui->doubleSpinBoxHeiht->setValue(vals.at(0).toInt()*printer->getDpi()/25.0);
                }
            } else if (par==QString("FILES")){
                for (int j=0; j<vals.size()-1; j++){
                    ui->listWidgetFiles->addItem(vals.at(j));
                }
            }
        }
    }
}*/

void DialogSettings::calibr()
{
    QString cmd;
    cmd+=QString("SIZE %1 mm, %2 mm\n").arg(ui->doubleSpinBoxHeiht->value()).arg(ui->doubleSpinBoxWidth->value());
    cmd+=QString("BLINEDETECT %1, %2\n").arg(int(ui->doubleSpinBoxWidth->value()*printer->getDpi()/25)).arg(int(ui->doubleSpinBoxGap->value()*printer->getDpi()/25));
    printer->printDecode(cmd);
}

/*void DialogSettings::download()
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
            printer->print(cmd);
        }
    }
}*/


/*void DialogSettings::getSettings()
{
    QString cmd;
    cmd+=QString("OUT \"MODEL=\";GETSETTING$(\"SYSTEM\", \"INFORMATION\", \"MODEL\")\n");
    cmd+=QString("OUT \"BLINE SIZE=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"BLINE SIZE\")\n");
    cmd+=QString("OUT \"PAPER SIZE=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"PAPER SIZE\")\n");
    cmd+=QString("OUT \"PAPER WIDTH=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"PAPER WIDTH\")\n");
    cmd+=QString("OUT \"FILES=\";~!F\n");
    //QString s=printer->printDecodeData(cmd,100);
    //printer->printDecode(cmd);
    //parceCfg(s);
}*/
