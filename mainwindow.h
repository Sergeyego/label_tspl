#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDataWidgetMapper>
#include <QTcpSocket>
#include <QTextCodec>
#include <QComboBox>
#include <QSettings>
#include <QMap>
#include "dialogsettings.h"
#include "modelro.h"
#include "dialogcmd.h"
#include "tprinter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelRo *modelPart;
    ModelRo *modelTu;
    ModelRo *modelVol;
    ModelRo *modelNam;
    ModelRo *modelOdobr;
    QDataWidgetMapper *mapper;
    QString getCodSrc();
    QString getCodPack();
    QString getNum(QComboBox *c);
    QString strGost();
    QString getSert();
    QMap <int, QString> docType;
    QString getEanPack();
    void loadSettings();
    void saveSettings();
    TPrinter *printerSrc;
    TPrinter *printerPack;

private slots:
    void updPart();
    void refreshData(QModelIndex index);
    void createSrcLabel();
    void createPackLabel();
    void refreshDocType();
    void settingsPrintSrc();
    void settingsPrintPack();
    void viewCmdSrc();
    void viewCmdPack();
};

#endif // MAINWINDOW_H
