#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T20:12:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nonogram
TEMPLATE = app

VERSION = 2.7.4.0

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
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
    gamewindow.cpp \
    levelselecter.cpp \
    stackedwindow.cpp \
    toolbutton.cpp \
    nonogram.cpp \
    menubutton.cpp \
    linereader.cpp \
    nonogramdata.cpp \
    nonogrampreview.cpp \
    savegame.cpp \
    loadgame.cpp \
    infowindow.cpp \
    pixelfont.cpp

HEADERS += \
        mainwindow.h \
    gamewindow.h \
    levelselecter.h \
    stackedwindow.h \
    define.h \
    nonogramdata.h \
    toolbutton.h \
    nonogram.h \
    menubutton.h \
    build.h \
    nonogrampreview.h \
    infowindow.h \
    pixelfont.h

RC_ICONS = images\icon_dark_new.ico

RESOURCES += \
    icon.qrc
