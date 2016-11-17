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
        flash_alg.cxx\
        opto.cxx\
    mypopup.cpp

HEADERS  += mainwindow.h\
            flash_alg.h\
            opto.h\
    mypopup.h

FORMS    += mainwindow.ui \
    mypopup.ui

LIBS += -L/usr/lib -lconfig++ 
