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
    popup.cpp

HEADERS  += mainwindow.h\
            carding.h \
    popup.h

FORMS    += mainwindow.ui \
    popup.ui
