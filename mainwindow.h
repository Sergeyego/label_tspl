#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDataWidgetMapper>
#include <QTcpSocket>
#include <QTextCodec>
#include "modelro.h"

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
    bool printData(const QString &data);

private slots:
    void updPart();
    void refreshData(QModelIndex index);
    void createSrcLabel();
    void createPackLabel();
};

#endif // MAINWINDOW_H
