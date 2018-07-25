#ifndef WINDOW_STACKED_H
#define WINDOW_STACKED_H

#include "window_main.h"
#include "window_level_selector.h"

#include <QStackedLayout>

class StackedWindow : public QWidget {
	Q_OBJECT

public:
    static const int MAIN_WINDOW_INDEX = 0;
    static const int LEVEL_SELECTOR_INDEX = 1;

    explicit StackedWindow(QWidget* parent = nullptr);
	~StackedWindow();
    void setIndex(int index) const;
    void checkBtnLoad();

private:
	MainWindow* main_window;
    LevelSelectorWindow* level_selector;
	QStackedLayout* layout_this;
};

#endif // WINDOW_STACKED_H
