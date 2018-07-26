#ifndef WINDOW_LEVEL_SELECTOR_H
#define WINDOW_LEVEL_SELECTOR_H

#include "button_menu.h"

#include <QHBoxLayout>
#include <QLabel>

class LevelSelectorWindow : public QWidget {
    Q_OBJECT

public:
    explicit LevelSelectorWindow(QWidget* parent = nullptr);
    ~LevelSelectorWindow();

private:
    QLabel* label_title;
    QLabel* label_game_title;
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

#endif // WINDOW_LEVEL_SELECTOR_H
