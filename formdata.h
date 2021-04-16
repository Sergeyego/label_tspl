#ifndef FORMDATA_H
#define FORMDATA_H

#include <QWidget>
#include "modelro.h"
#include <QDataWidgetMapper>
#include <QCompleter>
#include <QComboBox>

namespace Ui {
class FormData;
}

class FormData : public QWidget
{
    Q_OBJECT

public:
    explicit FormData(QWidget *parent = 0);
    ~FormData();
    QString getSert();
    QString marka();
    QString diametr();
    QString plavka();
    QString part();
    QString datePart();
    QString datePack();
    QString spool();
    QString mas();
    QString eanEd();
    QString eanGr();
    QString count();
    QString qrCode();
    QString codeProd();
    QString otkNum();
    QString otkNam();
    QString gost();
    QString description();
    QString upkNum();
    QString adr();
    QString kvoSpool();
    QString master();

private:
    Ui::FormData *ui;
    ModelRo *modelPart;
    ModelRo *modelTu;
    ModelRo *modelOtk;
    ModelRo *modelNam;
    ModelRo *modelOdobr;
    ModelRo *modelPartOrig;
    ModelRo *modelMaster;
    QDataWidgetMapper *mapper;
    QMap <int, QString> docType;
    bool selectPart();
    QString strAdr;
    QString site;
    QString getNum(QComboBox *c);

private slots:
    void refreshData(QModelIndex index);
    void genEan();
    void setOrigPart();
    void refreshDocType();

public slots:
    void updPart();
};

#endif // FORMDATA_H
