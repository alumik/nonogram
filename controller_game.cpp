#include "controller_game.h"

#include <fstream>

StackedWindow* GameController::stacked_window = nullptr;
GameWindow* GameController::game_window = nullptr;

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
