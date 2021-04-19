#include "tprinter.h"

TPrinter::TPrinter(QString name, QObject *parent) : QObject(parent)
{
    pname=name;
    loadSettings();
}

TPrinter::~TPrinter()
{
    saveSettings();
}

/*QByteArray TPrinter::printData(QByteArray &data, int respTime)
{
    QTcpSocket tcpSocket;
    QByteArray buf;

    tcpSocket.connectToHost(getIp(),getPort());
    bool ok=tcpSocket.waitForConnected();
    if (ok){
        qint64 x = 0;
        const qint64 size=data.size();
        int bsize=2048;
        while (x < size) {
            int b= ((size-x)< bsize) ? (size-x) : bsize;
            qint64 y = tcpSocket.write(data.right(size-x),b);
            tcpSocket.waitForBytesWritten();
            qDebug()<<QString::fromUtf8("Отправлено %1 байт").arg(y);
            x += y;
        }
        if (respTime>0){
            while (tcpSocket.waitForReadyRead(respTime)){
                buf.push_back(tcpSocket.readAll());
            }
            if (buf.isEmpty()){
                QMessageBox::critical(nullptr,QString::fromUtf8("Ошибка"),tcpSocket.errorString(),QMessageBox::Ok);
            }
        }
        tcpSocket.disconnectFromHost();
    } else {
        QMessageBox::critical(nullptr,QString::fromUtf8("Ошибка"),tcpSocket.errorString(),QMessageBox::Ok);
    }
    return buf;
}*/

/*QByteArray TPrinter::printDecodeData(QString &data, int respTime)
{
    QByteArray d=data.toUtf8();
    return printData(d,respTime);
}*/

int TPrinter::print(QByteArray &data)
{
    int jobId = 0;
    jobId = cupsCreateJob( CUPS_HTTP_DEFAULT, printer_name.toLatin1().data(), "Print_Label", 0, NULL );
    if ( jobId > 0 ){
        const char* format = CUPS_FORMAT_COMMAND;
        cupsStartDocument( CUPS_HTTP_DEFAULT, printer_name.toLatin1().data(), jobId, data.data(), format, true );
        cupsWriteRequestData( CUPS_HTTP_DEFAULT, data.data(), strlen( data ) );
        cupsFinishDocument( CUPS_HTTP_DEFAULT, printer_name.toLatin1().data() );
    }
    return jobId;
}

int TPrinter::printDecode(QString &data)
{
    QByteArray d=data.toUtf8();
    return print(d);
}

QString TPrinter::getPrinterName()
{
    return printer_name;
}

/*void TPrinter::setHost(QString ip)
{
    host=ip;
}*/

/*void TPrinter::setPort(int p)
{
    port=p;
}*/

void TPrinter::setPrinterName(QString name)
{
    printer_name=name;
}

void TPrinter::setDpi(int d)
{
    dpi=d;
}

/*QString TPrinter::getIp()
{
    return host;
}*/

/*int TPrinter::getPort()
{
    return port;
}*/

void TPrinter::loadSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    //host=settings.value(pname+"_ip","192.168.1.118").toString();
    //port=settings.value(pname+"_port",9100).toInt();
    printer_name=settings.value(pname+"_nam").toString();
    dpi=settings.value(pname+"_dpi",200).toInt();
}

void TPrinter::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    //settings.setValue(pname+"_ip",host);
    //settings.setValue(pname+"_port",port);
    settings.setValue(pname+"_nam",printer_name);
    settings.setValue(pname+"_dpi",dpi);
}

QStringList TPrinter::getPrinterList()
{
    QStringList l;
    cups_dest_t *dests;
    int num_dests = cupsGetDests(&dests);
    cups_dest_t *dest;
    int i;
    for (i = num_dests, dest = dests; i > 0; i --, dest ++){
      if (dest->instance == NULL) {
        l.push_back(dest->name);
      }
    }
    cupsFreeDests(num_dests, dests);
    return l;
}

int TPrinter::getDpi()
{
    return dpi;
}
