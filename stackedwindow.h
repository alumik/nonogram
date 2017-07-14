#ifndef STACKEDWINDOW_H
#define STACKEDWINDOW_H

#include "mainwindow.h"
#include "levelselecter.h"

#include <QStackedLayout>

class StackedWindow : public QWidget {
	Q_OBJECT

private:
	MainWindow* mainWindow;
	LevelSelecter* lvSelecter;
	QStackedLayout* layoutStacked;

public:
	StackedWindow(QWidget *parent = nullptr);
	~StackedWindow();
	void setIndex(int index);
	void addWidget(QWidget* widget);
};

#endif // STACKEDWINDOW_H
