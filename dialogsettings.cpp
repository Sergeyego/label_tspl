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
    connect(ui->pushButtonDownload,SIGNAL(clicked(bool)),this,SLOT(download()));
    connect(ui->pushButtonGet,SIGNAL(clicked(bool)),this,SLOT(getSettings()));
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
    QByteArray cmd;
    cmd.push_back(QString("SIZE %1 mm, %2 mm\n").arg(ui->doubleSpinBoxHeiht->value()).arg(ui->doubleSpinBoxWidth->value()).toLocal8Bit());
    cmd.push_back(QString("BLINEDETECT %1, %2\n").arg(ui->doubleSpinBoxWidth->value()*8.0).arg(ui->doubleSpinBoxGap->value()*8.0).toLocal8Bit());
    cmdPrint(cmd);
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
            cmd.append(QString("DOWNLOAD F, \"%1\", %2, ").arg(fi.fileName()).arg(f.size()).toLatin1());
            cmd.append(f.readAll());
            cmd.append("\n");
            cmdPrint(cmd);
        }
    }
}

void DialogSettings::cmdPrint(QByteArray &data, bool waitresp)
{
    QTcpSocket tcpSocket;
    tcpSocket.connectToHost(getIp(),getPort());
    bool ok=tcpSocket.waitForConnected();
    if (ok){
        qint64 x = 0;
        const qint64 size=data.size();
        int bsize=16384;
        while (x < size) {
            int b= ((size-x)< bsize) ? (size-x) : bsize;
            qint64 y = tcpSocket.write(data,b);
            //tcpSocket.waitForBytesWritten();
            qDebug()<<QString::fromUtf8("Отправлено ")<<y<<QString::fromUtf8(" байт");
            x += y;
        }
        if (waitresp){
            QString buf;
            while (tcpSocket.waitForReadyRead(100)){
                buf.push_back(tcpSocket.readAll());
            }
            if (buf.isEmpty()){
                QMessageBox::critical(this,QString::fromUtf8("Ошибка"),tcpSocket.errorString(),QMessageBox::Ok);
            } else {
                parceCfg(buf);
            }
        }
        tcpSocket.disconnectFromHost();
    } else {
        QMessageBox::critical(this,QString::fromUtf8("Ошибка"),tcpSocket.errorString(),QMessageBox::Ok);
    }
}


void DialogSettings::getSettings()
{
    QByteArray mes;
    mes.push_back("OUT \"MODEL=\";GETSETTING$(\"SYSTEM\", \"INFORMATION\", \"MODEL\")\n");
    mes.push_back("OUT \"BLINE SIZE=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"BLINE SIZE\")\n");
    mes.push_back("OUT \"PAPER SIZE=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"PAPER SIZE\")\n");
    mes.push_back("OUT \"PAPER WIDTH=\";GETSETTING$(\"CONFIG\", \"TSPL\", \"PAPER WIDTH\")\n");
    mes.push_back("OUT \"FILES=\";~!F\n");
    cmdPrint(mes,true);
}

