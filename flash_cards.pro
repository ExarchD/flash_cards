#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T09:53:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flash_cards
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp\
        src/flash_alg.cxx\
        src/opto.cxx\
    src/mypopup.cpp

INCLUDEPATH += $$PWD/include
HEADERS  += include/mainwindow.h\
            include/flash_alg.h\
            include/opto.h\
    include/mypopup.h

FORMS    += form/mainwindow.ui \
    form/mypopup.ui

LIBS += -L/usr/lib -lconfig++ 
