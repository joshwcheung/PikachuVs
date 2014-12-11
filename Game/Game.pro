#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T20:09:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += \
    Sources/gameboard.cpp \
    Sources/howto.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/pikachu.cpp \
    Sources/quitwidget.cpp \
    Sources/gameoverwidget.cpp

HEADERS  += \
    Headers/gameboard.h \
    Headers/howto.h \
    Headers/mainwindow.h \
    Headers/pikachu.h \
    Headers/quitwidget.h \
    Headers/gameoverwidget.h

FORMS    += \
    mainwindow.ui
