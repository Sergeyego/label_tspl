#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QString ip, int port, QWidget *parent = 0);
    ~DialogSettings();
    QString getIp();
    int getPort();

private:
    Ui::DialogSettings *ui;

private slots:
    void calibr();

signals:
    void cmdPrint(QString c);
};

#endif // DIALOGSETTINGS_H
