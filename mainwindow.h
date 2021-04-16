#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QAction>
#include <QToolButton>
#include "formdata.h"
#include "labels.h"

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
    void loadSettings();
    void saveSettings();
    void createActions(LabelBase *l);
    FormData *data;
    LabelE801016 *labelE801016;
    LabelG95110 *labelG95110;
    LabelE4570 *labelE4570;
    LabelG100100 *labelG100100;
    LabelG100100Pal *labelG100100Pal;

private slots:

};

#endif // MAINWINDOW_H
