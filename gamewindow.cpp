#include "gamewindow.h"
#include "define.h"
#include "stackedwindow.h"
#include "infowindow.h"
#include "pixelfont.h"

#include <QPalette>
#include <QIcon>
#include <QDesktopWidget>
#include <QApplication>
#include <cstdio>

extern StackedWindow* stackedWindow;
extern MenuButton* gBtnResume;
extern void saveGame(Nonogram* nonogram);
extern bool canLoad();

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {

	//判断能否回到主界面
	back = false;
	//工具类型
	toolType = 0;

	//设置窗口标题
	setWindowTitle(tr("Nonogram[*]"));

	//设置窗口颜色
	QPalette pal = palette();
	pal.setColor(QPalette::Background, DARK_COLOR);
	setAutoFillBackground(true);
	setPalette(pal);

	//创建游戏控件
	gameWidget = new Nonogram(this);

	//图片素材
	iconBtn = QPixmap(":/button/icon-button");
	iconPaint = iconBtn.copy(0, 0, 96, 96);
	iconErase = iconBtn.copy(96, 0, 96, 96);
	iconCross = iconBtn.copy(192, 0, 96, 96);
	iconPaintChecked = iconBtn.copy(0, 96, 96, 96);
	iconEraseChecked = iconBtn.copy(96, 96, 96, 96);
	iconCrossChecked = iconBtn.copy(192, 96, 96, 96);

	cursorTool = QPixmap(":/cursor/tool");
	cursorPaint = cursorTool.copy(3,3,23,23);
	cursorErase = cursorTool.copy(33,3,23,23);
	cursorCross = cursorTool.copy(63,3,23,23);

	//工具按钮
	btnPaint = new ToolButton(QIcon(iconPaintChecked), tr("填充"), this, true, true);
	connect(btnPaint, &QPushButton::clicked, this, &GameWindow::checkedPaint);
	gameWidget->viewport()->setCursor(QCursor(cursorPaint, 1, 22));
	btnPaint->setChecked(true);

	btnErase = new ToolButton(QIcon(iconErase), tr("清除"), this, true, true);
	connect(btnErase, &QPushButton::clicked, this, &GameWindow::checkedErase);

	btnCross = new ToolButton(QIcon(iconCross), tr("标记空白"), this, true, true);
	connect(btnCross, &QPushButton::clicked, this, &GameWindow::checkedCross);

	btnUndo = new ToolButton(QIcon(iconBtn.copy(288, 0, 96, 96)), tr("撤销"), this);
	connect(btnUndo, &QPushButton::clicked, gameWidget, &Nonogram::undo);
	btnUndo->setDisabled(true);

	btnRedo = new ToolButton(QIcon(iconBtn.copy(288, 96, 96, 96)), tr("重做"), this);
	connect(btnRedo, &QPushButton::clicked, gameWidget, &Nonogram::redo);
	btnRedo->setDisabled(true);

	btnReset = new ToolButton(QIcon(iconBtn.copy(384, 0, 96, 96)), tr("重置"), this);
	connect(btnReset, &QPushButton::clicked, gameWidget, &Nonogram::resetGame);
	btnReset->setDisabled(true);

	//游戏标题
	lbGameName = new QLabel(tr("<font color=\"#cccccc\">Nono</font><font color=\"#FF7800\">gram</font>"), this);
	lbGameName->setFont(PixelFont("Berlin Sans FB", 30, 50));

	//菜单按钮
	btnHelp = new MenuButton(tr("帮助"), this, true);
	btnHelp->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btnHelp, &QPushButton::clicked, this, &GameWindow::showHelp);

	btnBack = new MenuButton(tr("返回"), this, true);
	btnBack->setFixedWidth(NAVBUTTON_WIDTH);
	connect(btnBack, &QPushButton::clicked, this, &GameWindow::showMain);

	//工具按钮布局
	layoutToolBtn = new QHBoxLayout;
	layoutToolBtn->addStretch();
	layoutToolBtn->addWidget(btnPaint);
	layoutToolBtn->addWidget(btnErase);
	layoutToolBtn->addWidget(btnCross);
	layoutToolBtn->addWidget(btnUndo);
	layoutToolBtn->addWidget(btnRedo);
	layoutToolBtn->addWidget(btnReset);
	layoutToolBtn->addStretch();
	layoutToolBtn->setSpacing(SPACING_SMALL / 2);

	//菜单按钮布局
	layoutMenuBtn = new QHBoxLayout;
	layoutMenuBtn->addStretch();
	layoutMenuBtn->addWidget(lbGameName, 0, Qt::AlignCenter);
	placeHolder = new QLabel(this);
	placeHolder->setFixedWidth(10);
	layoutMenuBtn->addWidget(placeHolder, 0, Qt::AlignCenter);
	layoutMenuBtn->addWidget(btnHelp, 0, Qt::AlignCenter);
	layoutMenuBtn->addWidget(btnBack, 0, Qt::AlignCenter);
	layoutMenuBtn->addStretch();
	layoutMenuBtn->setSpacing(SPACING_SMALL);

	//创建布局
	layoutGame = new QVBoxLayout;
	setLayout(layoutGame);
	layoutGame->addWidget(gameWidget, 0, Qt::AlignCenter);
	layoutGame->addLayout(layoutToolBtn);
	layoutGame->addStretch();
	layoutGame->addLayout(layoutMenuBtn);
	layoutGame->setContentsMargins(30, 30, 30, 30);
	layoutGame->setSpacing(SPACING_LARGE);
}

void GameWindow::showMain() {
	close();
	if (back) {
		stackedWindow->setIndex(0);
		stackedWindow->show();
		stackedWindow->activateWindow();
	}
}
//TODO:解决窗口显示在其他窗口后面的问题

void GameWindow::showHelp() {
	InfoWindow info(tr("<font color=\"#FF7800\">Nonogram</font> 是一种逻辑游戏，玩家在游戏中以猜谜的方式画图。<br><br>"
					   "在一个网格中，每行每列的开头都有一组数。玩家需要根据它们来填充格子，<br>"
					   "最后可以得出一幅图画，谓之网格画。<br><br>"
					   "例如“4 8 1 1”是指该行（或该列）上，按照数字顺序，有四条<font color=\"#FF7800\">连续的</font>由格子连成的线，<br>"
					   "四条线分别占了4格、8格、1格和1格。每条线之间最少要有一个空格。<br>"
					   "即“████ ████████ █ █”。<font color=\"#FF7800\">线条间可以间隔多个空格</font>，但<font color=\"#FF7800\">线条的顺序不能变</font>。<br><br>"
					   "玩家应尽量用“╳”号标记一定不需要填充的格子，以辅助判断。"),
					1,
					this);
	info.exec();
}

void GameWindow::checkedPaint() {
	gameWidget->viewport()->setCursor(QCursor(cursorPaint, 1, 22));
	btnPaint->setIcon(QIcon(iconPaintChecked));
	toolType = 0;
	btnErase->setChecked(false);
	btnErase->setIcon(QIcon(iconErase));
	btnCross->setChecked(false);
	btnCross->setIcon(QIcon(iconCross));
}

void GameWindow::checkedErase() {
	gameWidget->viewport()->setCursor(QCursor(cursorErase));
	btnErase->setIcon(QIcon(iconEraseChecked));
	toolType = 1;
	btnPaint->setChecked(false);
	btnPaint->setIcon(QIcon(iconPaint));
	btnCross->setChecked(false);
	btnCross->setIcon(QIcon(iconCross));
}

void GameWindow::checkedCross() {
	gameWidget->viewport()->setCursor(QCursor(cursorCross));
	btnCross->setIcon(QIcon(iconCrossChecked));
	toolType = 2;
	btnPaint->setChecked(false);
	btnPaint->setIcon(QIcon(iconPaint));
	btnErase->setChecked(false);
	btnErase->setIcon(QIcon(iconErase));
}

//游戏结束后屏蔽鼠标输入
bool GameWindow::eventFilter(QObject *obj, QEvent *event) {
	if (obj == gameWidget->viewport()) {
		if (event->type() == QEvent::MouseButtonPress
				|| event->type() == QEvent::MouseButtonRelease
				|| event->type() == QEvent::MouseMove
				|| event->type() == QEvent::MouseButtonDblClick) {
			return true;
		} else {
			return false;
		}
	} else {
		return QWidget::eventFilter(obj, event);
	}
}

//询问是否要保存游戏
void GameWindow::closeEvent(QCloseEvent *event) {
	if (isWindowModified() && !gameWidget->complete) {
		InfoWindow info(tr("是否保存游戏进度？"), 3, this);
		int r = info.exec();
		if (r == QDialog::Accepted) {
			saveGame(gameWidget);
			gBtnResume->setDisabled(false);
			event->accept();
			back = true;
		} else if (r == 3) {
			event->ignore();
			back = false;
		} else {
			event->accept();
			back = true;
		}
	} else {
		if (gameWidget->complete) {
			remove("save.nonogram");
		}
		gBtnResume->setDisabled(canLoad());
		event->accept();
		back = true;
	}
}

//游戏开始前智能调整窗口大小和位置
void GameWindow::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);
	resize(gameWidget->tableSizeW + 60, gameWidget->tableSizeH + SPACING_LARGE * 2 + 60 + BUTTON_HEIGHT + 10 + BUTTON_HEIGHT);
	QRect desktopGeopmetry = QApplication::desktop()->availableGeometry();
	int x = stackedWindow->pos().x() + ((stackedWindow->frameGeometry().width() - frameGeometry().width()) / 2);
	int y = stackedWindow->pos().y() + ((stackedWindow->frameGeometry().height() - frameGeometry().height()) / 2);
	if (x < 8) {
		x = 8;
	} else if (x + frameGeometry().width() > desktopGeopmetry.width()) {
		x = desktopGeopmetry.width() - frameGeometry().width() - 8;
	}
	if (y < 8) {
		y = 8;
	} else if (y + frameGeometry().height() > desktopGeopmetry.height()) {
		y = desktopGeopmetry.height() - frameGeometry().height() - 8;
	}
	move(x, y);
}

//游戏结束后调整界面显示
void GameWindow::onComplete(QString name) {
	btnHelp->setVisible(false);
	btnPaint->setVisible(false);
	btnErase->setVisible(false);
	btnCross->setVisible(false);
	btnUndo->setVisible(false);
	btnRedo->setVisible(false);
	btnReset->setVisible(false);
	placeHolder->setVisible(false);
	layoutMenuBtn->removeWidget(lbGameName);
	layoutMenuBtn->removeWidget(btnBack);
	layoutGame->addWidget(lbGameName, 0, Qt::AlignCenter);
	layoutGame->addWidget(btnBack, 0, Qt::AlignCenter);

	InfoWindow info(tr("恭喜您，游戏<font color=\"#ff7800\"> “%1” </font>已完成！").arg(name), 1, this);
	info.exec();
}

GameWindow::~GameWindow() {
	delete layoutToolBtn;
	layoutToolBtn = NULL;
	delete layoutMenuBtn;
	layoutMenuBtn = NULL;
	delete layoutGame;
	layoutGame = NULL;
}
