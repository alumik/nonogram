#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T20:12:02
#
#-------------------------------------------------

QT += \
    core \
    gui \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nonogram
TEMPLATE = app

VERSION = 2.8.2.0

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
    src/buttons/button_menu.cpp \
    src/buttons/button_tool.cpp \
    src/controllers/controller_game.cpp \
    src/controllers/controller_version.cpp \
    src/core/nonogram.cpp \
    src/core/nonogram_data.cpp \
    src/core/nonogram_preview.cpp \
    src/utils/util_pixel_font.cpp \
    src/windows/window_game.cpp \
    src/windows/window_info.cpp \
    src/windows/window_level_selector.cpp \
    src/windows/window_main.cpp \
    src/windows/window_stacked.cpp \
    src/main.cpp

HEADERS += \
    src/buttons/button_menu.h \
    src/buttons/button_tool.h \
    src/controllers/controller_game.h \
    src/controllers/controller_version.h \
    src/core/nonogram.h \
    src/core/nonogram_data.h \
    src/core/nonogram_preview.h \
    src/utils/util_build_number.h \
    src/utils/util_generic_define.h \
    src/utils/util_pixel_font.h \
    src/utils/util_pvector.h \
    src/windows/window_game.h \
    src/windows/window_info.h \
    src/windows/window_level_selector.h \
    src/windows/window_main.h \
    src/windows/window_stacked.h

RC_ICONS = images\icon_game_dark.ico

RESOURCES += \
    icon.qrc
