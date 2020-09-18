#ifndef DIALOGCMD_H
#define DIALOGCMD_H

#include <QDialog>
#include "tprinter.h"

namespace Ui {
class DialogCmd;
}

class DialogCmd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCmd(QString cmd, TPrinter *p, QWidget *parent = 0);
    ~DialogCmd();

private:
    Ui::DialogCmd *ui;
    TPrinter *printer;

private slots:
    void goCmd();

signals:
    void cmdPrint(QString c, int t);
};

#endif // DIALOGCMD_H
