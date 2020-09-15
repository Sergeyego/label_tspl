#include "mainwindow.h"
#include <QApplication>
#include "pgdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PgDialog d(QObject::tr("Печать пластиковых этикеток"));
    if (d.exec()!=QDialog::Accepted) exit(1);
    MainWindow w;
    w.show();

    return a.exec();
}
