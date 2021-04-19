#ifndef TPRINTER_H
#define TPRINTER_H

#include <QObject>
//#include <QTcpSocket>
#include <QMessageBox>
#include <QSettings>
#include <QApplication>
#include <cups/cups.h>
#include <cups/sidechannel.h>

class TPrinter : public QObject
{
    Q_OBJECT
public:
    explicit TPrinter(QString name, QObject *parent = nullptr);
    ~TPrinter();
    //QByteArray printData(QByteArray &data, int respTime=0);
    //QByteArray printDecodeData(QString &data, int respTime=0);
    int print(QByteArray &data);
    int printDecode(QString &data);
    QString getPrinterName();
    //QString getIp();
    //int getPort();
    void loadSettings();
    void saveSettings();
    QStringList getPrinterList();
    int getDpi();

private:
    //QString host;
    //int port;
    QString pname;
    QString printer_name;
    int dpi;

signals:

public slots:
    //void setHost(QString ip);
    //void setPort(int p);
    void setPrinterName(QString name);
    void setDpi(int d);
};

#endif // TPRINTER_H
