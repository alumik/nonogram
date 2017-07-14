#ifndef DEFINE_H
#define DEFINE_H

////版本号
#define VERSION QString("2.7.4.0")

////尺寸
//间隔
#define SPACING_SMALL                  12
#define SPACING_LARGE                  16
//按钮字体大小
#define BUTTON_FONT_SIZE               12
//全局按钮尺寸
#define BUTTON_HEIGHT                  42
#define BUTTON_WIDTH                   200
//工具按钮尺寸
#define TOOLBUTTON_SIZE                70, BUTTON_HEIGHT + 5
//工具按钮图标尺寸
#define TOOLBUTTON_ICON_SIZE           28, 28
//导航按钮尺寸
#define NAVBUTTON_WIDTH				   (BUTTON_WIDTH - SPACING_SMALL) / 2
//游戏图标大小
#define GAME_ICON_SIZE                 130, 130
//默认窗口大小
#define DEFAULT_WINDOW_SIZE            400, 550
//方格尺寸
#define BLOCK_SIZE                     25
#define SPLITER_SIZE                   2

////颜色
#define PRIMARY_COLOR                  QColor(204, 204, 204)
#define DARK_COLOR                     QColor(43, 43, 43)
#define ACCENT_COLOR                   QColor(255, 120, 0)

#define MAIN_SPLITER_COLOR             Qt::white
#define SECONDARY_SPLITER_COLOR        Qt::black

#define HINT_TEXT_COLOR                Qt::white
#define HINT_UNSOLVED_COLOR            DARK_COLOR
#define HINT_SOLVED_COLOR              QColor(139, 195, 74)

#define CROSS_HIGHLIGHT_COLOR          QColor(200, 180, 160)
#define AREA_HIGHLIGHT_COLOR           QColor(200, 160, 130)
#define AREA_HIGHLIGHT_DARK_COLOR      QColor(50 , 25,  5)

#endif // DEFINE_H
