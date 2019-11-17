#include "src/controllers/controller_game.h"
#include "src/utils/util_generic_define.h"
#include "src/windows/window_stacked.h"

/**
 * \brief 层叠窗口构造函数
 * \param parent 父部件指针
 */
StackedWindow::StackedWindow(QWidget* parent) : QWidget(parent) {
    // 设置窗口标题
    setWindowTitle(tr("Nonogram"));

    // 设置窗口颜色
    GameController::setBackgroundColor(this, DARK_COLOR);

    // 设置初始窗口大小
    resize(DEFAULT_WINDOW_SIZE);

    // 创建主界面和游戏选择界面
    main_window = new MainWindow(this);
    level_selector = new LevelSelectorWindow(this);

    // 创建布局
    layout_this = new QStackedLayout();
    setLayout(layout_this);
    layout_this->addWidget(main_window);
    layout_this->addWidget(level_selector);
}

/**
 * \brief 切换页面
 * \param index 页面索引
 */
void StackedWindow::setIndex(const int index) const {
    layout_this->setCurrentIndex(index);
}

/**
 * \brief 判断加载游戏按钮是否可用
 */
void StackedWindow::checkBtnLoad() const {
    main_window->checkBtnLoad();
}

/**
 * \brief 析构函数
 */
StackedWindow::~StackedWindow() {
    delete layout_this;
    layout_this = nullptr;
}
