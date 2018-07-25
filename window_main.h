#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include "button_menu.h"

#include <QHBoxLayout>
#include <QLabel>

extern MenuButton* global_btn_resume;

class MainWindow : public QWidget {
	Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	QLabel* label_icon;
	QLabel* label_game_name;
	QLabel* label_game_name_sub;
	MenuButton* btn_start;
	MenuButton* btn_resume;
	MenuButton* btn_about;
	MenuButton* btn_exit;
	QVBoxLayout* layout_title;
	QHBoxLayout* layout_btn;
	QVBoxLayout* layout_this;

private slots:
	void showAbout();
    void showLevelSelector();
    static void loadGameSlot();
};

#endif // WINDOW_MAIN_H
