#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "nonogram.h"
#include "toolbutton.h"
#include "menubutton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

class GameWindow : public QWidget {
	Q_OBJECT

public:
    static const int TOOL_PAINT = 0;
    static const int TOOL_ERASE = 1;
    static const int TOOL_CROSS = 2;

	int tool_type;
	Nonogram* game_widget;
	ToolButton* btn_undo;
	ToolButton* btn_redo;
	ToolButton* btn_reset;

private:
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
	QLabel* label_game_name;
	QLabel* label_place_holder;
	MenuButton* btn_help;
	MenuButton* btn_back;
	QHBoxLayout* layout_btn_tools;
	QHBoxLayout* layout_btn_menu;
	QVBoxLayout* layout_this;

public:
	explicit GameWindow(QWidget *parent = nullptr);
	~GameWindow();
	void onComplete(QString name);

protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void closeEvent(QCloseEvent* event);
	void showEvent(QShowEvent* event);

private slots:
	void showMain();
	void showHelp();
	void checkedPaint();
	void checkedErase();
	void checkedCross();
};

#endif // GAMEWINDOW_H
