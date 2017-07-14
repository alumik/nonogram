#include "infowindow.h"
#include "define.h"
#include "pixelfont.h"

#include <windows.h>
#include <QPropertyAnimation>

InfoWindow::InfoWindow(QString content, int btnCount, QWidget *parent)
	: QDialog(parent) {

	//设置窗口颜色
	QPalette pal = palette();
	pal.setColor(QPalette::Background, DARK_COLOR);
	setAutoFillBackground(true);
	setPalette(pal);

	//无边框模式
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	//失焦闪烁功能
	connect(this, &InfoWindow::ncActive, this, &InfoWindow::flashWindow);

	//内容文字
	lbContent = new QLabel(content, this);
	lbContent->setFont(PixelFont("Microsoft YaHei UI", 12, 50));
	lbContent->setStyleSheet("QLabel { color: rgb(204, 204, 204) }");

	//按钮布局
	layoutBtn = new QHBoxLayout;
	layoutBtn->setSpacing(SPACING_SMALL);

	switch (btnCount) {
	case 1:
		cBtn1 = new MenuButton(tr("返回"), this, true);
		lbGameName = new QLabel(tr("<font color=\"#cccccc\">Nono</font><font color=\"#FF7800\">gram</font>"), this);
		lbGameName->setFont(PixelFont("Berlin Sans FB", 25, 50));
		layoutBtn->addWidget(lbGameName, 0, Qt::AlignCenter);
		layoutBtn->addStretch();
		layoutBtn->addWidget(cBtn1, 0, Qt::AlignCenter);
		break;
	case 2:
		cBtn1 = new MenuButton(tr("确定"), this, true);
		cBtn2 = new MenuButton(tr("取消"), this, true);
		cBtn2->setDefault(true);
		layoutBtn->addStretch();
		layoutBtn->addWidget(cBtn1, 0, Qt::AlignCenter);
		layoutBtn->addWidget(cBtn2, 0, Qt::AlignCenter);
		layoutBtn->addStretch();
		cBtn2->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
		connect(cBtn2, &QPushButton::clicked, this, &InfoWindow::cBtn2Clicked);
		break;
	case 3:
		cBtn1 = new MenuButton(tr("保存"), this, true);
		cBtn2 = new MenuButton(tr("不保存"), this, true);
		cBtn3 = new MenuButton(tr("取消"), this, true);
		cBtn1->setDefault(true);
		layoutBtn->addStretch();
		layoutBtn->addWidget(cBtn1, 0, Qt::AlignCenter);
		layoutBtn->addWidget(cBtn2, 0, Qt::AlignCenter);
		layoutBtn->addWidget(cBtn3, 0, Qt::AlignCenter);
		layoutBtn->addStretch();
		cBtn2->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
		cBtn3->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
		connect(cBtn2, &QPushButton::clicked, this, &InfoWindow::cBtn2Clicked);
		connect(cBtn3, &QPushButton::clicked, this, &InfoWindow::cBtn3Clicked);
	}
	cBtn1->setFixedSize(NAVBUTTON_WIDTH - 5, BUTTON_HEIGHT - 5);
	connect(cBtn1, &QPushButton::clicked, this, &InfoWindow::cBtn1Clicked);

	layoutDialog = new QVBoxLayout;
	setLayout(layoutDialog);
	layoutDialog->addWidget(lbContent, 0, Qt::AlignCenter);
	layoutDialog->addLayout(layoutBtn);
	layoutDialog->setContentsMargins(40, 15, 40, 15);
	layoutDialog->setSpacing(2 * SPACING_LARGE);
}

void InfoWindow::cBtn1Clicked() {
	done(Accepted);
}

void InfoWindow::cBtn2Clicked() {
	done(Rejected);
}

void InfoWindow::cBtn3Clicked() {
	done(3);
}

//移动无边框窗口
void InfoWindow::mousePressEvent(QMouseEvent *event) {
	if (ReleaseCapture())
		SendMessage(HWND(this->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
	event->ignore();
}

//微调位置和淡入效果
//注：该函数未在非“1080p 100%缩放”的显示器上测试过，可能会出现显示问题
void InfoWindow::showEvent(QShowEvent *event) {
	QDialog::showEvent(event);
	move(geometry().x() + 8, geometry().y());
	QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
	anim->setStartValue(0.0);
	anim->setEndValue(1.0);
	anim->setDuration(120);
	anim->start(QAbstractAnimation::DeleteWhenStopped);
}

//窗口失焦闪烁信号
bool InfoWindow::nativeEvent(const QByteArray& eventType, void* message, long* result) {
	MSG* msg = static_cast<MSG*>(message);
	if(msg->message == WM_NCACTIVATE) {
		emit ncActive((bool)(msg->wParam));
	}
	return QWidget::nativeEvent(eventType, message, result);
}

//窗口失焦闪烁效果
void InfoWindow::flashWindow(bool active) {
	if (active) {
		setStyleSheet("QDialog { border: 2px solid rgb(255, 120, 0); background-color: rgb(43, 43, 43) }");
	} else {
		setStyleSheet("QDialog { border: 3px solid rgb(255, 120, 0); background-color: rgb(43, 43, 43) }");
	}
}

InfoWindow::~InfoWindow() {
	delete layoutBtn;
	layoutBtn = NULL;
	delete layoutDialog;
	layoutDialog = NULL;
}
