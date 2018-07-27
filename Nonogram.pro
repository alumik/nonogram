#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T20:12:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nonogram
TEMPLATE = app

VERSION = 2.8.0.3

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++1z

SOURCES += \
    button/button_menu.cpp \
    button/button_tool.cpp \
    controller/controller_game.cpp \
    controller/controller_version.cpp \
    core/nonogram.cpp \
    core/nonogram_data.cpp \
    core/nonogram_preview.cpp \
    util/util_pixel_font.cpp \
    window/window_game.cpp \
    window/window_info.cpp \
    window/window_level_selector.cpp \
    window/window_main.cpp \
    window/window_stacked.cpp \
    main.cpp

HEADERS += \
    button/button_menu.h \
    button/button_tool.h \
    controller/controller_game.h \
    controller/controller_version.h \
    core/nonogram.h \
    core/nonogram_data.h \
    core/nonogram_preview.h \
    util/util_build_number.h \
    util/util_generic_define.h \
    util/util_pixel_font.h \
    util/util_pvector.h \
    window/window_game.h \
    window/window_info.h \
    window/window_level_selector.h \
    window/window_main.h \
    window/window_stacked.h

RC_ICONS = image\icon_game_dark.ico

RESOURCES += \
    icon.qrc
