#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QFile>
#include <QDebug>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QFileDialog>
#include "tprinter.h"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(TPrinter *p, QWidget *parent = 0);
    ~DialogSettings();

public slots:
    void setBigLbl();
    void setSmallLbl();

private:
    Ui::DialogSettings *ui;
    void parceCfg(QString cfg);
    TPrinter *printer;

private slots:
    void calibr();
    void download();
    void getSettings();
};

#endif // DIALOGSETTINGS_H
