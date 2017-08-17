#-------------------------------------------------
#
# Project created by QtCreator 2017-08-11T12:53:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineSwpping
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwidget.cpp \
    clicklabel.cpp \
    corealgorithem.cpp \
    publicdate.cpp \
    gameevent.cpp

HEADERS  += mainwindow.h \
    mainwidget.h \
    clicklabel.h \
    publicdate.h \
    corealgorithem.h \
    gameevent.h

FORMS    += mainwindow.ui

RESOURCES += \
    rec.qrc
