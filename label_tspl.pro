#-------------------------------------------------
#
# Project created by QtCreator 2020-09-15T09:59:48
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = label_tspl
TEMPLATE = app

RC_FILE = ico.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    pgdialog.cpp \
    modelro.cpp \
    dialogsettings.cpp \
    dialogcmd.cpp \
    tprinter.cpp

HEADERS += \
        mainwindow.h \
    pgdialog.h \
    modelro.h \
    dialogsettings.h \
    dialogcmd.h \
    tprinter.h

FORMS += \
        mainwindow.ui \
    pgdialog.ui \
    dialogsettings.ui \
    dialogcmd.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    ico.rc
