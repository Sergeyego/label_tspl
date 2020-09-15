#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDataWidgetMapper>
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
    QDataWidgetMapper *mapper;

private slots:
    void updPart();
    void refreshData(QModelIndex index);
};

#endif // MAINWINDOW_H
