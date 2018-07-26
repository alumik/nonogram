#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include "button_menu.h"

#include <QHBoxLayout>
#include <QLabel>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void checkBtnLoad();

private:
    QLabel* label_icon;
    QLabel* label_game_title;
    QLabel* label_game_title_secondary;
    MenuButton* btn_start;
    MenuButton* btn_load;
    MenuButton* btn_about;
    MenuButton* btn_exit;
    QVBoxLayout* layout_title;
    QHBoxLayout* layout_btn;
    QVBoxLayout* layout_this;

private slots:
    void showAbout();
    void showLevelSelector();
    static void onLoadGame();
};

#endif // WINDOW_MAIN_H
