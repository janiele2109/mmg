#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T18:14:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += inc/

TARGET = MasterMind
TEMPLATE = app

SOURCES += src/main.cpp\
           src/mainwindow.cpp \
    src/mastermindgame.cpp \
    src/decodingboard.cpp \
    src/holematrix.cpp \
    src/customcontrols.cpp \
    src/breaker.cpp \
    src/maker.cpp

HEADERS  += inc/mainwindow.h \
    inc/mastermindgame.h \
    inc/decodingboard.h \
    inc/holematrix.h \
    inc/customcontrols.h \
    inc/comdef.h \
    inc/breaker.h \
    inc/maker.h

FORMS    += ui/mainwindow.ui

RESOURCES += \
    res/resources.qrc
