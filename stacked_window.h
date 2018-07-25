#ifndef STACKED_WINDOW_H
#define STACKED_WINDOW_H

#include "main_window.h"
#include "level_selector.h"

#include <QStackedLayout>

class StackedWindow : public QWidget {
	Q_OBJECT

public:
	explicit StackedWindow(QWidget *parent = nullptr);
	~StackedWindow();
	void setIndex(int index) const;
	void addWidget(QWidget* widget) const;

private:
	MainWindow* main_window;
	LevelSelector* level_selecter;
	QStackedLayout* layout_this;
};

#endif // STACKED_WINDOW_H
