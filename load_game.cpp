#include "util_generic_define.h"
#include "window_stacked.h"
#include "nonogram_preview.h"
#include "window_game.h"
#include "controller_game.h"

#include <fstream>

using namespace std;

/**
 * \brief 载入游戏
 */
void loadGame() {
	ifstream loader;
	loader.open("save.nonogram");
    loader >> GameController::nonogram_index;

	// 初始化游戏
    if (GameController::game_window) {
        delete GameController::game_window;
        GameController::game_window = nullptr;
	}
    GameController::game_window = new GameWindow;
    GameController::game_window->show();
    GameController::stacked_window->hide();

    auto nonogram = GameController::game_window->game_widget;
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
    GameController::game_window->btn_reset->setDisabled(false);
	loader.close();
}
