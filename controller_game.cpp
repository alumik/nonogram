#include "controller_game.h"
#include "util_generic_define.h"

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

void GameController::loadGame() {
    std::ifstream loader("save.nonogram");
    loader >> nonogram_index;
    startGame();
    game_window->game_widget->load(loader);
    game_window->btn_reset->setDisabled(false);
    loader.close();
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
