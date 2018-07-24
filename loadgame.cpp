#include "define.h"
#include "stackedwindow.h"
#include "nonogrampreview.h"
#include "gamewindow.h"

#include <fstream>

using namespace std;

extern GameWindow* gameWindow;
extern StackedWindow* global_stacked_window;
extern int nonogramIndex;

bool canLoad() {
	fstream test;
	test.open("save.nonogram", ios::in);
	if (!test) {
		return true;
	}
	test.close();
	return false;
}

void loadGame() {
	ifstream loader;
	loader.open("save.nonogram");
	loader >> nonogramIndex;

	//初始化游戏
	if (gameWindow) {
		delete gameWindow;
		gameWindow = NULL;
	}
	gameWindow = new GameWindow;
	gameWindow->show();
	global_stacked_window->hide();

	Nonogram* nonogram = gameWindow->game_widget;
	for (int r = nonogram->hintRow + 1; r < nonogram->rowCount(); r++) {
		for (int c = nonogram->hintColumn + 1; c < nonogram->columnCount(); c++) {
			int state;
			loader >> state;
			switch (state) {
			case 1:
				nonogram->item(r, c)->setBackgroundColor(DARK_COLOR);
				nonogram->nonogramPreview->updatePreview(r, c, Qt::black);
				nonogram->checkLineComplete(r, c);
				break;
			case 2:
				nonogram->item(r, c)->setText(QString("╳"));
			}
		}
	}
	gameWindow->btn_reset->setDisabled(false);
	loader.close();
}
