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
	int toolType;
	Nonogram* gameWidget;
	ToolButton* btnUndo;
	ToolButton* btnRedo;
	ToolButton* btnReset;

private:
	bool back;
	QPixmap cursorTool;
	QPixmap cursorPaint;
	QPixmap cursorErase;
	QPixmap cursorCross;
	QPixmap iconBtn;
	QPixmap iconPaint;
	QPixmap iconErase;
	QPixmap iconCross;
	QPixmap iconPaintChecked;
	QPixmap iconEraseChecked;
	QPixmap iconCrossChecked;
	ToolButton* btnPaint;
	ToolButton* btnErase;
	ToolButton* btnCross;
	QLabel* lbGameName;
	QLabel* placeHolder;
	MenuButton* btnHelp;
	MenuButton* btnBack;
	QHBoxLayout* layoutToolBtn;
	QHBoxLayout* layoutMenuBtn;
	QVBoxLayout* layoutGame;

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
