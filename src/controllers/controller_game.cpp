#include "src/controllers/controller_game.h"
#include "src/utils/util_generic_define.h"

#include <fstream>

/**
 * \brief 层叠窗口指针
 */
StackedWindow* GameController::stacked_window = nullptr;

/**
 * \brief 游戏窗口指针
 */
GameWindow* GameController::game_window = nullptr;

/**
 * \brief 网格画编号
 */
int GameController::nonogram_index = 0;

/**
 * \brief 设置窗口背景颜色
 * \param widget 窗口指针
 * \param color 要设置的颜色
 */
void GameController::setBackgroundColor(QWidget* widget, const QColor& color) {
    auto pal = widget->palette();
    pal.setColor(QPalette::Background, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
}

/**
 * \brief 判断存档文件是否存在
 * \return 
 */
bool GameController::saveExists() {
    std::fstream test_loader(SAVE_NAME);
    return test_loader.good();
}

/**
 * \brief 加载游戏
 */
void GameController::loadGame() {
    std::ifstream fin(SAVE_NAME);
    fin >> nonogram_index;
    startGame();
    game_window->game_widget->load(fin);
    game_window->btn_reset->setDisabled(false);
    fin.close();
}

/**
 * \brief 开始新游戏
 */
void GameController::startGame() {
    if (game_window) {
        delete game_window;
        game_window = nullptr;
    }
    remove(SAVE_NAME);
    game_window = new GameWindow();
    game_window->show();
    stacked_window->hide();
}

/**
 * \brief 设置撤销按钮可用性
 * \param enable 按钮是否可用
 */
void GameController::setUndo(const bool enable) {
    game_window->btn_undo->setDisabled(!enable);
}

/**
 * \brief 设置重做按钮可用性
 * \param enable 按钮是否可用
 */
void GameController::setRedo(const bool enable) {
    game_window->btn_redo->setDisabled(!enable);
}

/**
 * \brief 设置重置按钮可用性
 * \param enable 按钮是否可用
 */
void GameController::setReset(const bool enable) {
    game_window->btn_reset->setDisabled(!enable);
}

/**
 * \brief 设置游戏被修改状态
 * \param modified 游戏是否被修改
 */
void GameController::setModified(const bool modified) {
    game_window->setWindowModified(modified);
}
