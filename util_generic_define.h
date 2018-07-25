#ifndef DEFINE_H
#define DEFINE_H

#define SPACING_SMALL             12
#define SPACING_LARGE             16

#define BUTTON_HEIGHT             42
#define BUTTON_WIDTH              200
#define BUTTON_FONT_SIZE          12

#define TOOL_BUTTON_SIZE           70, BUTTON_HEIGHT + 5
#define TOOL_BUTTON_ICON_SIZE      28, 28
#define NAV_BUTTON_WIDTH           ((BUTTON_WIDTH - SPACING_SMALL) / 2)

#define GAME_ICON_SIZE            130, 130

#define DEFAULT_WINDOW_SIZE       400, 550

#define BLOCK_SIZE                25
#define SPLITER_SIZE              2

#define PRIMARY_COLOR             QColor(204, 204, 204)
#define DARK_COLOR                QColor(43, 43, 43)
#define ACCENT_COLOR              QColor(255, 120, 0)

#define MAIN_SPLITER_COLOR        Qt::white
#define SECONDARY_SPLITER_COLOR   Qt::black

#define HINT_TEXT_COLOR           Qt::white
#define HINT_UNSOLVED_COLOR       DARK_COLOR
#define HINT_SOLVED_COLOR         QColor(139, 195, 74)

#define CROSS_HIGHLIGHT_COLOR     QColor(200, 180, 160)
#define AREA_HIGHLIGHT_COLOR      QColor(200, 160, 130)
#define AREA_HIGHLIGHT_DARK_COLOR QColor(50 , 25,  5)

#endif // DEFINE_H
