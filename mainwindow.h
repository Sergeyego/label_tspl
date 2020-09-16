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
    QString ipAdr;
    int port;
    void loadSettings();
    void saveSettings();

private slots:
    void updPart();
    void refreshData(QModelIndex index);
    void createSrcLabel();
    void createPackLabel();
    void refreshDocType();
    void settings();
    void viewCmdSrc();
    void viewCmdPack();
    bool printData(const QString &data);
};

#endif // MAINWINDOW_H
