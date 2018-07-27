#include "window/window_level_selector.h"
#include "util/util_generic_define.h"
#include "window/window_stacked.h"
#include "window/window_game.h"
#include "util/util_pixel_font.h"
#include "controller/controller_game.h"

/**
 * \brief 关卡选择器
 * \param parent 父部件指针
 */
LevelSelectorWindow::LevelSelectorWindow(QWidget* parent) : QWidget(parent) {
    // 创建游戏标题
    label_game_title = new QLabel(tr(R"(<font color="#cccccc">Nono</font><font color="#FF7800">gram</font>)"), this);
    label_game_title->setFont(PixelFont("Berlin Sans FB", 40, 50));

    // 创建窗口标题
    label_title = new QLabel(tr(R"(<center><font color="#cccccc">网格画选择</font></center>)"), this);
    label_title->setFont(PixelFont("Adobe 黑体 Std R", 30, 50));

    // 创建按钮
    btn_mini = new MenuButton(tr("音符 [10x10]"), this);
    connect(btn_mini, &QPushButton::clicked, this, &LevelSelectorWindow::startGame);

    btn_small = new MenuButton(tr("Android [15x19]"), this);
    connect(btn_small, &QPushButton::clicked, this, &LevelSelectorWindow::startGame);

    btn_medium = new MenuButton(tr("狗 [20x20]"), this);
    connect(btn_medium, &QPushButton::clicked, this, &LevelSelectorWindow::startGame);

    btn_large = new MenuButton(tr("公鸡 [30x30]"), this);
    connect(btn_large, &QPushButton::clicked, this, &LevelSelectorWindow::startGame);

    btn_test = new MenuButton(tr("测试"), this, false);
    btn_test->setFixedWidth(NAV_BUTTON_WIDTH);
    connect(btn_test, &QPushButton::clicked, this, &LevelSelectorWindow::startGame);

    btn_back = new MenuButton(tr("返回"), this, false);
    btn_back->setFixedWidth(NAV_BUTTON_WIDTH);
    connect(btn_back, &QPushButton::clicked, this, &LevelSelectorWindow::showMain);

    // 创建按钮布局
    layout_btn = new QHBoxLayout();
    layout_btn->addStretch();
    layout_btn->addWidget(btn_test, 0, Qt::AlignHCenter);
    layout_btn->addWidget(btn_back, 0, Qt::AlignHCenter);
    layout_btn->addStretch();
    layout_btn->setSpacing(SPACING_SMALL);

    // 创建布局
    layout_this = new QVBoxLayout();
    setLayout(layout_this);
    layout_this->addStretch(1);
    layout_this->addWidget(label_game_title, 0, Qt::AlignCenter);
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
void LevelSelectorWindow::startGame() const {
    if (sender() == btn_mini) {
        GameController::nonogram_index = 1;
    } else if (sender() == btn_small) {
        GameController::nonogram_index = 2;
    } else if (sender() == btn_medium) {
        GameController::nonogram_index = 3;
    } else if (sender() == btn_large) {
        GameController::nonogram_index = 4;
    } else if (sender() == btn_test) {
        GameController::nonogram_index = 0;
    }

    GameController::startGame();
}

/**
 * \brief 显示主界面
 */
void LevelSelectorWindow::showMain() {
    GameController::stacked_window->setIndex(StackedWindow::MAIN_WINDOW_INDEX);
}

/**
 * \brief 析构函数
 */
LevelSelectorWindow::~LevelSelectorWindow() {
    delete layout_btn;
    layout_btn = nullptr;
    delete layout_this;
    layout_this = nullptr;
}
