#include "mainwindow.h"
#include <QApplication>
#include "pgdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icon.ico"));
    PgDialog d(QString::fromUtf8("Печать пластиковых этикеток"));
    if (d.exec()!=QDialog::Accepted) exit(1);
    MainWindow w;
    w.show();

    return a.exec();
}
