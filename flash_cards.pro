#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T09:53:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flash_cards
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        carding.cxx \
    mypopup.cpp

HEADERS  += mainwindow.h\
            carding.h \
    mypopup.h

FORMS    += mainwindow.ui \
    mypopup.ui
