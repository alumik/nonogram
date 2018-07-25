#ifndef LEVEL_SELECTOR_H
#define LEVEL_SELECTOR_H

#include "menu_button.h"

#include <QHBoxLayout>
#include <QLabel>

extern int global_nonogram_index;

class LevelSelector : public QWidget {
	Q_OBJECT

public:
	explicit LevelSelector(QWidget *parent = nullptr);
	~LevelSelector();

private:
	QLabel* label_title;
	QLabel* label_game_name;
	MenuButton* btn_mini;
	MenuButton* btn_small;
	MenuButton* btn_medium;
	MenuButton* btn_large;
	MenuButton* btn_back;
	MenuButton* btn_test;
	QHBoxLayout* layout_btn;
	QVBoxLayout* layout_this;

private slots:
	void startGame() const;
	static void showMain();
};

#endif // LEVEL_SELECTOR_H
