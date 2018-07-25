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
    nonogram.cpp \
    line_reader.cpp \
    nonogram_data.cpp \
    nonogram_preview.cpp \
    window_game.cpp \
    controller_version.cpp \
    controller_game.cpp \
    button_tool.cpp \
    window_stacked.cpp \
    button_menu.cpp \
    window_main.cpp \
    util_pixel_font.cpp \
    window_level_selector.cpp \
    window_info.cpp

HEADERS += \
    nonogram_data.h \
    nonogram.h \
    nonogram_preview.h \
    window_game.h \
    controller_version.h \
    button_tool.h \
    window_info.h \
    window_stacked.h \
    util_pixel_font.h \
    window_level_selector.h \
    window_main.h \
    button_menu.h \
    controller_game.h \
    util_build_number.h \
    util_generic_define.h

RC_ICONS = images\icon_dark_new.ico

RESOURCES += \
    icon.qrc
