#include "level_selector.h"
#include "define.h"
#include "stacked_window.h"
#include "game_window.h"
#include "pixelfont.h"

#include <cstdio>

extern StackedWindow* global_stacked_window;
extern GameWindow* global_game_window;
extern MenuButton* global_btn_resume;

int global_nonogram_index;

/**
 * \brief 关卡选择器
 * \param parent 
 */
LevelSelector::LevelSelector(QWidget *parent) : QWidget(parent) {
	// 创建游戏标题
	label_game_name = new QLabel(tr(R"(<font color="#cccccc">Nono</font><font color="#FF7800">gram</font>)"), this);
	label_game_name->setFont(PixelFont("Berlin Sans FB", 40, 50));

	// 创建窗口标题
	label_title = new QLabel(tr(R"(<center><font color="#cccccc">网格画选择</font></center>)"), this);
	label_title->setFont(PixelFont("Adobe 黑体 Std R", 30, 50));

	// 创建按钮
	btn_mini = new MenuButton(tr("音符 [10x10]"), this);
	connect(btn_mini, &QPushButton::clicked, this, &LevelSelector::startGame);

	btn_small = new MenuButton(tr("Android [15x19]"), this);
	connect(btn_small, &QPushButton::clicked, this, &LevelSelector::startGame);

	btn_medium = new MenuButton(tr("狗 [20x20]"), this);
	connect(btn_medium, &QPushButton::clicked, this, &LevelSelector::startGame);

	btn_large = new MenuButton(tr("公鸡 [30x30]"), this);
	connect(btn_large, &QPushButton::clicked, this, &LevelSelector::startGame);

	btn_test = new MenuButton(tr("测试"), this, true);
	btn_test->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btn_test, &QPushButton::clicked, this, &LevelSelector::startGame);

	btn_back = new MenuButton(tr("返回"), this, true);
	btn_back->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btn_back, &QPushButton::clicked, this, &LevelSelector::showMain);

	// 创建按钮布局
	layout_btn = new QHBoxLayout;
	layout_btn->addStretch();
	layout_btn->addWidget(btn_test, 0, Qt::AlignHCenter);
	layout_btn->addWidget(btn_back, 0, Qt::AlignHCenter);
	layout_btn->addStretch();
	layout_btn->setSpacing(SPACING_SMALL);

	// 创建布局
	layout_this = new QVBoxLayout();
	setLayout(layout_this);
	layout_this->addStretch(1);
	layout_this->addWidget(label_game_name, 0, Qt::AlignCenter);
	layout_this->addWidget(label_title, 0, Qt::AlignCenter);
	layout_this->addStretch(2);
	layout_this->addWidget(btn_mini, 0, Qt::AlignCenter);
	layout_this->addWidget(btn_small, 0, Qt::AlignCenter);
	layout_this->addWidget(btn_medium, 0, Qt::AlignCenter);
	layout_this->addWidget(btn_large, 0, Qt::AlignCenter);
	layout_this->addLayout(layout_btn);
	layout_this->setContentsMargins(30, 30, 30, 30);
	layout_this->setSpacing(SPACING_SMALL);
}

/**
 * \brief 开始游戏
 */
void LevelSelector::startGame() const {
	if (sender() == btn_mini) {
		global_nonogram_index = 1;
	} else if (sender() == btn_small) {
		global_nonogram_index = 2;
	} else if (sender() == btn_medium) {
		global_nonogram_index = 3;
	} else if (sender() == btn_large) {
		global_nonogram_index = 4;
	} else if (sender() == btn_test) {
		global_nonogram_index = 0;
	}

	if (global_game_window) {
		delete global_game_window;
		global_game_window = nullptr;
	}

	remove("save.nonogram");
	global_btn_resume->setDisabled(true);
	global_game_window = new GameWindow;
	global_game_window->show();
	global_stacked_window->hide();
}

/**
 * \brief 显示主界面
 */
void LevelSelector::showMain() {
	global_stacked_window->setIndex(0);
}

/**
 * \brief 析构函数
 */
LevelSelector::~LevelSelector() {
	delete layout_btn;
	layout_btn = nullptr;
	delete layout_this;
	layout_this = nullptr;
}
