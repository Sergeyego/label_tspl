#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QFileDialog>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QString ip, int port, QWidget *parent = 0);
    ~DialogSettings();
    QString getIp();
    int getPort();

private:
    Ui::DialogSettings *ui;
    void parceCfg(QString cfg);

private slots:
    void calibr();
    void download();
    void cmdPrint(QByteArray &data, bool waitresp=false);
    void getSettings();
};

#endif // DIALOGSETTINGS_H
