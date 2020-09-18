#include "tprinter.h"

TPrinter::TPrinter(QObject *parent) : QObject(parent)
{
    loadSettings();
}

TPrinter::~TPrinter()
{
    saveSettings();
}

QByteArray TPrinter::printData(QByteArray &data, int respTime)
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
}

QByteArray TPrinter::printDecodeData(QString &data, int respTime)
{
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QByteArray d=codec->fromUnicode(data);
    return printData(d,respTime);
}

void TPrinter::setHost(QString ip)
{
    host=ip;
}

void TPrinter::setPort(int p)
{
    port=p;
}

QString TPrinter::getIp()
{
    return host;
}

int TPrinter::getPort()
{
    return port;
}

void TPrinter::loadSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    host=settings.value(this->objectName()+"_ip","192.168.1.118").toString();
    port=settings.value(this->objectName()+"_port",9100).toInt();
}

void TPrinter::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    settings.setValue(this->objectName()+"_ip",host);
    settings.setValue(this->objectName()+"_port",port);
}
