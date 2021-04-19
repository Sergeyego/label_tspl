#ifndef LABELBASE_H
#define LABELBASE_H

#include <QObject>
#include <QAction>
#include "tprinter.h"
#include "formdata.h"
#include "dialogsettings.h"
#include "dialogcmd.h"

class LabelBase : public QObject
{
    Q_OBJECT
public:
    explicit LabelBase(QString nam, double w, double h, double g, FormData *d, QObject *parent = nullptr);
    void setActions(QAction *actionCfg, QAction *actionCmd, QAction *actionPrint);
    QString getName();
    TPrinter *getPrinter();

protected:
    double width;
    double height;
    double gap;
    QString name;
    FormData *data;
    TPrinter *printer;
    virtual QString getCod();
    int getDots(double mm);
    QString normalize(QString t);
    QString logo(double x, double y);
    QString text(double x, double y, QString t, int size=10, int rotation=0);
    QString block(double x, double y, double w, double h, QString t, int size=10, int rotation=0);
    QString ean13(double x, double y, QString ean, double h=9, double s=0.375, int rotation=0);
    QString print();
    QString qrCode(double x, double y, QString t, int cellWidth=5);
    QString otkStamp(double x, double y);

signals:

public slots:
    void cfgPrinter();
    void viewCmd();
    void printLabel();
    void calibrate();
};

#endif // LABELBASE_H
