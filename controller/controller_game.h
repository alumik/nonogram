#ifndef CONTROLLER_GAME_H
#define CONTROLLER_GAME_H

#include "window/window_stacked.h"
#include "window/window_game.h"

class GameController {

public:
    static StackedWindow* stacked_window;
    static GameWindow* game_window;
    static int nonogram_index;

    static void setBackgroundColor(QWidget* widget, QColor color);
    static bool canLoadGame();
    static void loadGame();
    static void startGame();
    static void setUndo(bool enable);
    static void setRedo(bool enable);
    static void setReset(bool enable);
    static void setModified(bool modified);
};

#endif // CONTROLLER_GAME_H
