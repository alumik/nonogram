#ifndef STACKED_WINDOW_H
#define STACKED_WINDOW_H

#include "main_window.h"
#include "level_selector.h"

#include <QStackedLayout>

class StackedWindow : public QWidget {
	Q_OBJECT

public:
    static const int MAIN_WINDOW_INDEX = 0;
    static const int LEVEL_SELECTOR_INDEX = 1;

    explicit StackedWindow(QWidget* parent = nullptr);
	~StackedWindow();
    void setIndex(int index) const;

private:
	MainWindow* main_window;
    LevelSelector* level_selector;
	QStackedLayout* layout_this;
};

#endif // STACKED_WINDOW_H
