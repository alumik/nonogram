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
        main_window.cpp \
    game_window.cpp \
    level_selector.cpp \
    stacked_window.cpp \
    tool_button.cpp \
    nonogram.cpp \
    menu_button.cpp \
    line_reader.cpp \
    nonogram_data.cpp \
    nonogram_preview.cpp \
    save_game.cpp \
    load_game.cpp \
    info_window.cpp \
    pixelfont.cpp \
    version.cpp

HEADERS += \
        main_window.h \
    game_window.h \
    level_selector.h \
    stacked_window.h \
    define.h \
    nonogram_data.h \
    tool_button.h \
    nonogram.h \
    menu_button.h \
    build_number.h \
    nonogram_preview.h \
    info_window.h \
    pixelfont.h \
    version.h

RC_ICONS = images\icon_dark_new.ico

RESOURCES += \
    icon.qrc
