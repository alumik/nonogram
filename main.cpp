#include "stackedwindow.h"
#include "gamewindow.h"

#include <QApplication>
#include <QFontDatabase>

StackedWindow* global_stacked_window;
GameWindow* gameWindow;

int main(int argc, char *argv[]) {

	//禁用高DPI缩放以免出现显示问题
	QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

	QApplication app(argc, argv);

	//载入外部字体文件
	QFontDatabase::addApplicationFont("little.style"); //Adobe Heiti Std Regular
	QFontDatabase::addApplicationFont("big.style"); //Berlin Sans FB
	QFontDatabase::addApplicationFont("win7support.style"); //Microsoft YaHei UI Regular (for Windows 7)
	QFontDatabase::addApplicationFont("win7supportbd.style"); //Microsoft YaHei UI Bold (for Windows 7)

	global_stacked_window = new StackedWindow;
	global_stacked_window->show();

	return app.exec();
}
