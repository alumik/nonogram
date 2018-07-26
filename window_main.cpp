#include "window_main.h"
#include "util_generic_define.h"
#include "controller_version.h"
#include "window_stacked.h"
#include "window_info.h"
#include "util_pixel_font.h"
#include "controller_game.h"

#include <QApplication>
#include <QPixmap>

/**
 * \brief 游戏主窗口
 * \param parent 父部件指针
 */
MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    // 创建图标
    label_icon = new QLabel(this);
    label_icon->setFixedSize(GAME_ICON_SIZE);
    QPixmap icon(QString(":/icon/icon-game-white"));
    icon = icon.scaled(label_icon->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label_icon->setPixmap(icon);

    // 创建标题
    label_game_title = new QLabel(tr(R"(<font color="#cccccc">Nono</font><font color="#FF7800">gram</font>)"), this);
    label_game_title->setFont(PixelFont("Berlin Sans FB", 55, 50));

    // 创建副标题
    label_game_title_secondary = new QLabel(tr(R"(<font color="#cccccc">网格画</font>)"), this);
    label_game_title_secondary->setFont(PixelFont("Adobe 黑体 Std R", 30, 50));

    // 创建按钮
    btn_start = new MenuButton(tr("开始游戏"), this);
    connect(btn_start, &QPushButton::clicked, this, &MainWindow::showLevelSelector);

    btn_load = new MenuButton(tr("继续游戏"), this);
    checkBtnLoad();
    connect(btn_load, &QPushButton::clicked, this, &MainWindow::onLoadGame);

    btn_about = new MenuButton(tr("关于"), this, false);
    btn_about->setFixedWidth(NAV_BUTTON_WIDTH);
    connect(btn_about, &QPushButton::clicked, this, &MainWindow::showAbout);

    btn_exit = new MenuButton(tr("退出"), this, false);
    btn_exit->setFixedWidth(NAV_BUTTON_WIDTH);
    connect(btn_exit, &QPushButton::clicked, this, &QApplication::quit);

    // 创建标题布局
    layout_title = new QVBoxLayout();
    layout_title->addWidget(label_icon, 0, Qt::AlignCenter);
    layout_title->addWidget(label_game_title, 0, Qt::AlignCenter);
    layout_title->addWidget(label_game_title_secondary, 0, Qt::AlignCenter);
    layout_title->setSpacing(SPACING_SMALL / 2);

    // 创建按钮布局
    layout_btn = new QHBoxLayout();
    layout_btn->addStretch();
    layout_btn->addWidget(btn_about);
    layout_btn->addWidget(btn_exit);
    layout_btn->addStretch();
    layout_btn->setSpacing(SPACING_SMALL);

    // 创建布局
    layout_this = new QVBoxLayout();
    setLayout(layout_this);
    layout_this->addStretch();
    layout_this->addLayout(layout_title);
    layout_this->addStretch();
    layout_this->addWidget(btn_start, 0, Qt::AlignHCenter);
    layout_this->addWidget(btn_load, 0, Qt::AlignHCenter);
    layout_this->addLayout(layout_btn);
    layout_this->setContentsMargins(30, 30, 30, 30);
    layout_this->setSpacing(SPACING_SMALL);
}

/**
 * \brief 显示关于信息
 */
void MainWindow::showAbout() {
    InfoWindow info(tr("版本号：%1\n"
                       "编译时间：%2\n\n"
                       "作者：钟震宇\n"
                       "联系方式：nczzy1997@gmail.com")
                    .arg(VersionController::getVersion())
                    .arg(VersionController::getBulidDateTime()),
                    1,
                    this);
    info.exec();
}

/**
 * \brief 显示网格画选择
 */
void MainWindow::showLevelSelector() {
    if (GameController::canLoadGame()) {
        InfoWindow info(tr("<center>您还有未完成的游戏<br>开始新游戏将删除现有游戏进度<br>是否继续？</center>"), 2, this);
        const auto response = info.exec();
        if (response == QDialog::Accepted) {
            GameController::stacked_window->setIndex(StackedWindow::LEVEL_SELECTOR_INDEX);
        }
    } else {
        GameController::stacked_window->setIndex(StackedWindow::LEVEL_SELECTOR_INDEX);
    }
}

/**
 * \brief 加载游戏
 */
void MainWindow::onLoadGame() {
    GameController::loadGame();
}

void MainWindow::checkBtnLoad() {
    btn_load->setDisabled(!GameController::canLoadGame());
}

/**
 * \brief 析构函数
 */
MainWindow::~MainWindow() {
    delete layout_title;
    layout_title = nullptr;
    delete layout_btn;
    layout_btn = nullptr;
    delete layout_this;
    layout_this = nullptr;
}
