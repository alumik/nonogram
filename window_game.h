#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include "nonogram.h"
#include "button_tool.h"
#include "button_menu.h"

#include <QHBoxLayout>
#include <QPixmap>

class GameWindow : public QWidget {
    Q_OBJECT

public:
    static const int TOOL_PAINT = 0;
    static const int TOOL_ERASE = 1;
    static const int TOOL_CROSS = 2;

    Nonogram* game_widget;
    ToolButton* btn_undo;
    ToolButton* btn_redo;
    ToolButton* btn_reset;

    explicit GameWindow(QWidget* parent = nullptr);
    ~GameWindow() override;

    int getToolType();
    void showComplete(const QString& title);

private:
    int tool_type;
    bool can_return;
    QPixmap cursor_tools;
    QPixmap cursor_paint;
    QPixmap cursor_erase;
    QPixmap cursor_cross;
    QPixmap icon_tools;
    QPixmap icon_paint;
    QPixmap icon_erase;
    QPixmap icon_cross;
    QPixmap icon_paint_checked;
    QPixmap icon_erase_checked;
    QPixmap icon_cross_checked;
    ToolButton* btn_paint;
    ToolButton* btn_erase;
    ToolButton* btn_cross;
    QLabel* label_game_title;
    QLabel* label_place_holder;
    MenuButton* btn_help;
    MenuButton* btn_back;
    QHBoxLayout* layout_btn_tools;
    QHBoxLayout* layout_btn_menu;
    QVBoxLayout* layout_this;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void closeEvent(QCloseEvent* event) override;
    void showEvent(QShowEvent* event) override;

private slots:
    void showMain();
    void showHelp();
    void checkedPaint();
    void checkedErase();
    void checkedCross();
};

#endif // WINDOW_GAME_H
