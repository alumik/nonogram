#include "controller_game.h"

#include <fstream>

StackedWindow* GameController::stacked_window = nullptr;
GameWindow* GameController::game_window = nullptr;
int GameController::nonogram_index = 0;

void GameController::setBackgroundColor(QWidget* widget, QColor color) {
    auto pal = widget->palette();
    pal.setColor(QPalette::Background, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
}

bool GameController::canLoadGame() {
    std::fstream test_loader("save.nonogram");
    return test_loader.good();
}

void GameController::startGame() {
    if (game_window) {
        delete game_window;
        game_window = nullptr;
    }
    remove("save.nonogram");
    game_window = new GameWindow();
    game_window->show();
    stacked_window->hide();
}
