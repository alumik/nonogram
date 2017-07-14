#include "levelselecter.h"
#include "define.h"
#include "stackedwindow.h"
#include "gamewindow.h"
#include "pixelfont.h"

#include <cstdio>

extern StackedWindow* stackedWindow;
extern GameWindow* gameWindow;
extern MenuButton* gBtnResume;

int nonogramIndex;

LevelSelecter::LevelSelecter(QWidget *parent) : QWidget(parent) {

	//创建游戏标题
	lbGameName = new QLabel(tr("<font color=\"#cccccc\">Nono</font><font color=\"#FF7800\">gram</font>"), this);
	lbGameName->setFont(PixelFont("Berlin Sans FB", 40, 50));

	//创建窗口标题
	lbTitle = new QLabel(tr("<center><font color=\"#cccccc\">网格画选择</font></center>"), this);
	lbTitle->setFont(PixelFont("Adobe 黑体 Std R", 30, 50));

	//创建按钮
	btnMini = new MenuButton(tr("音符 [10x10]"), this);
	connect(btnMini, &QPushButton::clicked, this, &LevelSelecter::startGame);

	btnSmall = new MenuButton(tr("Android [15x19]"), this);
	connect(btnSmall, &QPushButton::clicked, this, &LevelSelecter::startGame);

	btnMedium = new MenuButton(tr("狗 [20x20]"), this);
	connect(btnMedium, &QPushButton::clicked, this, &LevelSelecter::startGame);

	btnLarge = new MenuButton(tr("公鸡 [30x30]"), this);
	connect(btnLarge, &QPushButton::clicked, this, &LevelSelecter::startGame);

	btnTest = new MenuButton(tr("测试"), this, true);
	btnTest->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btnTest, &QPushButton::clicked, this, &LevelSelecter::startGame);

	btnBack = new MenuButton(tr("返回"), this, true);
	btnBack->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btnBack, &QPushButton::clicked, this, &LevelSelecter::showMain);

	//创建按钮布局
	layoutBtn = new QHBoxLayout;
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnTest, 0, Qt::AlignHCenter);
	layoutBtn->addWidget(btnBack, 0, Qt::AlignHCenter);
	layoutBtn->addStretch();
	layoutBtn->setSpacing(SPACING_SMALL);

	//创建布局
	layoutLvSelecter = new QVBoxLayout();
	setLayout(layoutLvSelecter);
	layoutLvSelecter->addStretch(1);
	layoutLvSelecter->addWidget(lbGameName, 0, Qt::AlignCenter);
	layoutLvSelecter->addWidget(lbTitle, 0, Qt::AlignCenter);
	layoutLvSelecter->addStretch(2);
	layoutLvSelecter->addWidget(btnMini, 0, Qt::AlignCenter);
	layoutLvSelecter->addWidget(btnSmall, 0, Qt::AlignCenter);
	layoutLvSelecter->addWidget(btnMedium, 0, Qt::AlignCenter);
	layoutLvSelecter->addWidget(btnLarge, 0, Qt::AlignCenter);
	layoutLvSelecter->addLayout(layoutBtn);
	layoutLvSelecter->setContentsMargins(30, 30, 30, 30);
	layoutLvSelecter->setSpacing(SPACING_SMALL);
}

//开始游戏
void LevelSelecter::startGame() {
	if (sender() == btnMini) {
		nonogramIndex = 1;
	} else if (sender() == btnSmall) {
		nonogramIndex = 2;
	} else if (sender() == btnMedium) {
		nonogramIndex = 3;
	} else if (sender() == btnLarge) {
		nonogramIndex = 4;
	} else if (sender() == btnTest) {
		nonogramIndex = 0;
	}

	if (gameWindow) {
		delete gameWindow;
		gameWindow = NULL;
	}

	remove("save.nonogram");
	gBtnResume->setDisabled(true);
	gameWindow = new GameWindow;
	gameWindow->show();
	stackedWindow->hide();
}

void LevelSelecter::showMain() {
	stackedWindow->setIndex(0);
}

LevelSelecter::~LevelSelecter() {
	delete layoutBtn;
	layoutBtn = NULL;
	delete layoutLvSelecter;
	layoutLvSelecter = NULL;
}
