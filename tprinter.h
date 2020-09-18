#ifndef TPRINTER_H
#define TPRINTER_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTextCodec>
#include <QSettings>
#include <QApplication>

class TPrinter : public QObject
{
    Q_OBJECT
public:
    explicit TPrinter(QObject *parent = nullptr);
    ~TPrinter();
    QByteArray printData(QByteArray &data, int respTime=0);
    QString getIp();
    int getPort();
    void loadSettings();
    void saveSettings();

private:
    QString host;
    int port;

signals:

public slots:
    QByteArray printDecodeData(QString &data, int respTime=0);
    void setHost(QString ip);
    void setPort(int p);
};

#endif // TPRINTER_H
