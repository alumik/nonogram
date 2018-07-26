#include "controller_game.h"

#include <QApplication>
#include <QFontDatabase>

/**
 * \brief 入口函数
 * \param argc 参数个数
 * \param argv 参数列表
 * \return
 */
int main(int argc, char* argv[]) {
    // 禁用高DPI缩放以免出现显示问题
    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

    // 创建QApplication实例
    QApplication app(argc, argv);

    // 载入外部字体文件
    QFontDatabase::addApplicationFont("little.style"); // Adobe 黑体 Std R
    QFontDatabase::addApplicationFont("big.style"); // Berlin Sans FB
    QFontDatabase::addApplicationFont("win7support.style"); // Microsoft YaHei UI Regular (for Windows 7)
    QFontDatabase::addApplicationFont("win7supportbd.style"); // Microsoft YaHei UI Bold (for Windows 7)

    // 显示窗口
    GameController::stacked_window = new StackedWindow();
    GameController::stacked_window->show();

    return QApplication::exec();
}
