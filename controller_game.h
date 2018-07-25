#ifndef CONTROLLER_GAME_H
#define CONTROLLER_GAME_H

#include "window_stacked.h"
#include "window_game.h"

class GameController {

public:
    static StackedWindow* stacked_window;
    static GameWindow* game_window;
    static int nonogram_index;

    static void setBackgroundColor(QWidget* widget, QColor color);
    static bool canLoadGame();

    static void loadGame(){}
    static void startGame();
    static QVector<int> readRow(const int row, Nonogram* nonogram){}
    static QVector<int> readColumn(const int column, Nonogram* nonogram){}
    static QVector<int> readHintRow(const int row, Nonogram* nonogram){}
    static QVector<int> readHintColumn(const int column, Nonogram* nonogram){}
};

#endif // CONTROLLER_GAME_H
