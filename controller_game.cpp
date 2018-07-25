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

    auto nonogram = game_window->game_widget;
    for (auto r = nonogram->hint_row + 1; r < nonogram->rowCount(); r++) {
        for (auto c = nonogram->hint_column + 1; c < nonogram->columnCount(); c++) {
            int state;
            loader >> state;
            switch (state) {
                case 1:
                    nonogram->item(r, c)->setBackgroundColor(DARK_COLOR);
                    nonogram->nonogram_preview->updatePreview(r, c, Qt::black);
                    nonogram->checkLineComplete(r, c);
                    break;
                case 2:
                    nonogram->item(r, c)->setText(QString("╳"));
                default: ;
            }
        }
    }
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
