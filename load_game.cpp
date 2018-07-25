#include "define.h"
#include "window_stacked.h"
#include "nonogram_preview.h"
#include "window_game.h"

#include <fstream>

using namespace std;

extern GameWindow* global_game_window;
extern StackedWindow* global_stacked_window;
extern int global_nonogram_index;

/**
 * \brief 判断是否能够载入
 * \return 
 */
bool canLoad() {
	fstream test;
	test.open("save.nonogram", ios::in);
	if (!test) {
        return false;
	}
	test.close();
    return true;
}

/**
 * \brief 载入游戏
 */
void loadGame() {
	ifstream loader;
	loader.open("save.nonogram");
	loader >> global_nonogram_index;

	// 初始化游戏
	if (global_game_window) {
		delete global_game_window;
		global_game_window = nullptr;
	}
	global_game_window = new GameWindow;
	global_game_window->show();
	global_stacked_window->hide();

	auto nonogram = global_game_window->game_widget;
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
	global_game_window->btn_reset->setDisabled(false);
	loader.close();
}
