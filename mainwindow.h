#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDataWidgetMapper>
#include <QComboBox>
#include <QSettings>
#include <QMap>
#include <QCompleter>
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
    ModelRo *modelOtk;
    ModelRo *modelNam;
    ModelRo *modelOdobr;
    ModelRo *modelPartOrig;
    QDataWidgetMapper *mapper;
    QString getCodSrc(int dpi);
    QString getCodPack(int dpi);
    QString getCodPBig(int dpi);
    QString getCodPSmall(int dpi);
    QString getNum(QComboBox *c);
    QString strGost();
    QString getSert();
    QMap <int, QString> docType;
    QString getEanPack();
    void loadSettings();
    void saveSettings();
    TPrinter *printerSrc;
    TPrinter *printerPack;
    TPrinter *printerPBig;
    TPrinter *printerPSmall;
    QString getCod();
    int getDots(double mm, int dpi);
    QString getOtkStamp(double x, double y, int dpi);

private slots:
    void updPart();
    void setOrigPart();
    void refreshData(QModelIndex index);
    void createSrcLabel();
    void createPackLabel();
    void createPBigLabel();
    void createPSmallLabel();
    void refreshDocType();
    void settingsPrintSrc();
    void settingsPrintPack();
    void settingsPrintPBig();
    void settingsPrintPSmall();
    void viewCmdSrc();
    void viewCmdPack();
    void viewCmdPBig();
    void viewCmdPSmall();
};

#endif // MAINWINDOW_H
