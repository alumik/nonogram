#include "stackedwindow.h"
#include "define.h"

#include <QPalette>

StackedWindow::StackedWindow(QWidget *parent) : QWidget(parent) {

	//设置窗口标题
	setWindowTitle(tr("Nonogram"));

	//设置窗口颜色
	QPalette pal = palette();
	pal.setColor(QPalette::Background, DARK_COLOR);
	setAutoFillBackground(true);
	setPalette(pal);

	//设置初始窗口大小
	resize(DEFAULT_WINDOW_SIZE);

	//创建主界面和游戏选择界面
	mainWindow = new MainWindow(this);
	lvSelecter = new LevelSelecter(this);

	//创建布局
	layoutStacked = new QStackedLayout;
	setLayout(layoutStacked);
	layoutStacked->addWidget(mainWindow);
	layoutStacked->addWidget(lvSelecter);
}

//切换页面
void StackedWindow::setIndex(int index) {
	layoutStacked->setCurrentIndex(index);
}

//添加控件
void StackedWindow::addWidget(QWidget * widget) {
	layoutStacked->addWidget(widget);
}

StackedWindow::~StackedWindow() {
	delete layoutStacked;
	layoutStacked = NULL;
}
