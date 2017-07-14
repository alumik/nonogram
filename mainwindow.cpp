#include "mainwindow.h"
#include "define.h"
#include "build.h"
#include "stackedwindow.h"
#include "infowindow.h"
#include "pixelfont.h"

#include <QApplication>
#include <QPixmap>
#include <QDateTime>
#include <QLocale>

//标记编译时间
static const QDate buildDate = QLocale(QLocale::English).toDate(QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");
static const QTime buildTime = QTime::fromString(__TIME__, "hh:mm:ss");

extern StackedWindow* stackedWindow;
extern bool canLoad();
extern void loadGame();

MenuButton* gBtnResume;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

	//创建图标
	lbIcon = new QLabel(this);
	lbIcon->setFixedSize(GAME_ICON_SIZE);
	QPixmap icon(QString(":/game/icon-white"));
	icon = icon.scaled(lbIcon->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	lbIcon->setPixmap(icon);

	//创建标题
	lbGameName = new QLabel(tr("<font color=\"#cccccc\">Nono</font><font color=\"#FF7800\">gram</font>"), this);
	lbGameName->setFont(PixelFont("Berlin Sans FB", 55, 50));

	lbGameName_Sub = new QLabel(tr("<font color=\"#cccccc\">网格画</font>"), this);
	lbGameName_Sub->setFont(PixelFont("Adobe 黑体 Std R", 30, 50));

	//创建按钮
	btnStart = new MenuButton(tr("开始游戏"), this);
	connect(btnStart, &QPushButton::clicked, this, &MainWindow::showLvSelecter);

	gBtnResume = btnResume = new MenuButton(tr("继续游戏"), this);
	btnResume->setDisabled(canLoad());
	connect(btnResume, &QPushButton::clicked, this, &MainWindow::loadGameSlot);

	btnAbout = new MenuButton(tr("关于"), this, true);
	btnAbout->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btnAbout, &QPushButton::clicked, this, &MainWindow::showAbout);

	btnExit = new MenuButton(tr("退出"), this, true);
	btnExit->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btnExit, &QPushButton::clicked, this, &QApplication::quit);

	//创建标题布局
	layoutTitle = new QVBoxLayout;
	layoutTitle->addWidget(lbIcon, 0, Qt::AlignCenter);
	layoutTitle->addWidget(lbGameName, 0, Qt::AlignCenter);
	layoutTitle->addWidget(lbGameName_Sub, 0, Qt::AlignCenter);
	layoutTitle->setSpacing(SPACING_SMALL / 2);

	//创建按钮布局
	layoutBtn = new QHBoxLayout;
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnAbout);
	layoutBtn->addWidget(btnExit);
	layoutBtn->addStretch();
	layoutBtn->setSpacing(SPACING_SMALL);

	//创建布局
	layoutMain = new QVBoxLayout;
	setLayout(layoutMain);
	layoutMain->addStretch();
	layoutMain->addLayout(layoutTitle);
	layoutMain->addStretch();
	layoutMain->addWidget(btnStart, 0, Qt::AlignHCenter);
	layoutMain->addWidget(btnResume, 0, Qt::AlignHCenter);
	layoutMain->addLayout(layoutBtn);
	layoutMain->setContentsMargins(30, 30, 30, 30);
	layoutMain->setSpacing(SPACING_SMALL);
}

//显示关于
void MainWindow::showAbout() {
	InfoWindow info(tr("本游戏仍处在测试阶段，若出现BUG请及时反馈。\n\n"
					   "版本号：%3 (build %4) Release\n"
					   "编译时间：%1 %2\n\n"
					   "开发者：钟震宇\n"
					   "联系方式：nczzy1997@gmail.com").arg(buildDate.toString("yyyy年M月d日")).arg(buildTime.toString()).arg(VERSION).arg(BUILD),
					1,
					this);
	info.exec();
}

//显示网格画选择
void MainWindow::showLvSelecter() {
	if (!canLoad()) {
		InfoWindow info(tr("<center>您还有未完成的游戏<br>开始新游戏将删除现有游戏进度<br>是否继续？</center>"), 2, this);
		int r = info.exec();
		if (r == QDialog::Accepted) {
			stackedWindow->setIndex(1);
		}
	} else {
		stackedWindow->setIndex(1);
	}
}

//加载游戏
void MainWindow::loadGameSlot() {
	loadGame();
}

MainWindow::~MainWindow() {
	delete layoutTitle;
	layoutTitle = NULL;
	delete layoutBtn;
	layoutBtn = NULL;
	delete layoutMain;
	layoutMain = NULL;
}
