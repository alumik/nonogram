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
    std::fstream test_loader(SAVE_NAME);
    return test_loader.good();
}

void GameController::loadGame() {
    std::ifstream fin(SAVE_NAME);
    fin >> nonogram_index;
    startGame();
    game_window->game_widget->load(fin);
    game_window->btn_reset->setDisabled(false);
    fin.close();
}

void GameController::startGame() {
    if (game_window) {
        delete game_window;
        game_window = nullptr;
    }
    remove(SAVE_NAME);
    game_window = new GameWindow();
    game_window->show();
    stacked_window->hide();
}

void GameController::setUndo(bool enable) {
    game_window->btn_undo->setDisabled(!enable);
}

void GameController::setRedo(bool enable) {
    game_window->btn_redo->setDisabled(!enable);
}

void GameController::setReset(bool enable) {
    game_window->btn_reset->setDisabled(!enable);
}

void GameController::setModified(bool modified) {
    game_window->setWindowModified(modified);
}
