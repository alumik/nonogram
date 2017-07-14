#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menubutton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class MainWindow : public QWidget {
	Q_OBJECT

private:
	QLabel* lbIcon;
	QLabel* lbGameName;
	QLabel* lbGameName_Sub;
	QLabel* lbVersion;
	MenuButton* btnStart;
	MenuButton* btnResume;
	MenuButton* btnAbout;
	MenuButton* btnExit;
	QVBoxLayout* layoutTitle;
	QHBoxLayout* layoutBtn;
	QVBoxLayout* layoutMain;

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void showAbout();
	void showLvSelecter();
	void loadGameSlot();
};

#endif // MAINWINDOW_H
