#ifndef DIALOGCMD_H
#define DIALOGCMD_H

#include <QDialog>

namespace Ui {
class DialogCmd;
}

class DialogCmd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCmd(QString cmd, QWidget *parent = 0);
    ~DialogCmd();

private:
    Ui::DialogCmd *ui;

private slots:
    void goCmd();

signals:
    void cmdPrint(QString c);
};

#endif // DIALOGCMD_H
