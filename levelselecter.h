#ifndef LEVELSELECTER_H
#define LEVELSELECTER_H

#include "menubutton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class LevelSelecter : public QWidget {
	Q_OBJECT

private:
	QLabel* lbTitle;
	QLabel* lbGameName;
	MenuButton* btnMini;
	MenuButton* btnSmall;
	MenuButton* btnMedium;
	MenuButton* btnLarge;
	MenuButton* btnBack;
	MenuButton* btnTest;
	QHBoxLayout* layoutBtn;
	QVBoxLayout* layoutLvSelecter;

public:
	LevelSelecter(QWidget *parent = nullptr);
	~LevelSelecter();

private slots:
	void startGame();
	void showMain();
};

#endif // LEVELSELECTER_H
