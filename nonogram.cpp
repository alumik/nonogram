#include "nonogram.h"
#include "define.h"
#include "nonogramdata.h"
#include "gamewindow.h"
#include "nonogrampreview.h"
#include "pixelfont.h"
#include "infowindow.h"

#include <QHeaderView>
#include <cstdio>

extern int nonogramIndex;
extern GameWindow* gameWindow;
extern NonogramData nonogramData[4];
extern MenuButton* gBtnResume;

extern QVector<int> readRow(int r, Nonogram* nonogram);
extern QVector<int> readColumn(int c, Nonogram* nonogram);
extern QVector<int> readHintRow(int r, Nonogram* nonogram);
extern QVector<int> readHintColumn(int c, Nonogram* nonogram);

Nonogram::Nonogram(QWidget* parent) : QTableWidget(parent) {

	//读取游戏数据
	index = nonogramIndex;
	complete = false;
	gameRow = nonogramData[index].gameRow;
	gameColumn = nonogramData[index].gameColumn;
	hintRow = nonogramData[index].hintRow;
	hintColumn = nonogramData[index].hintColumn;
	lastR = hintRow + 1;
	lastC = hintColumn + 1;
	dragR = 0;
	dragC = 0;

	//计算分割线数量
	int spliterRow = gameRow / 5;
	if (gameRow % 5 == 0) {
		spliterRow--;
	}

	int spliterColumn = gameColumn / 5;
	if (gameColumn % 5 == 0) {
		spliterColumn--;
	}

	//配置游戏区域大小
	setRowCount(gameRow + hintRow + spliterRow + 1);
	setColumnCount(gameColumn + hintColumn + spliterColumn + 1);

	tableSizeW = (gameColumn + hintColumn) * BLOCK_SIZE + (spliterColumn + 1) * SPLITER_SIZE + 2;
	tableSizeH = (gameRow + hintRow) * BLOCK_SIZE + (spliterRow + 1) * SPLITER_SIZE + 2;
	tableSizeW = tableSizeW > 635 ? 635 : tableSizeW;
	tableSizeH = tableSizeH > 635 ? 635 : tableSizeH;
	setMinimumWidth(tableSizeW >= 15 * BLOCK_SIZE ? 15 * BLOCK_SIZE : tableSizeW);
	setMinimumHeight(tableSizeH >= 15 * BLOCK_SIZE ? 15 * BLOCK_SIZE : tableSizeH);

	//配置其他参数
	mousePressed = false;
	setMouseTracking(true);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	setFocusPolicy(Qt::NoFocus);
	setSelectionMode(QTableWidget::NoSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSizeAdjustPolicy(QTableWidget::AdjustToContents);
	setStyleSheet("QTableWidget { gridline-color: rgb(0, 0, 0) }");

	//创建预览界面
	preview = new QLabel(this);
	preview->move(1, 1);
	preview->setStyleSheet("QLabel { background-color: rgb(255, 255, 255) }");
	preview->setFixedSize(hintColumn * BLOCK_SIZE, hintRow * BLOCK_SIZE);
	preview->setFrameShape(QFrame::Box);
	preview->setLineWidth(2);
	nonogramPreview = new NonogramPreview(gameRow, gameColumn, hintRow, hintColumn, spliterRow, spliterColumn, preview);

	//创建拖动区域大小显示标签
	dragSize = new QLabel(this);
	dragSize->setVisible(false);
	dragSize->move(1, 1);
	dragSize->setStyleSheet("QLabel { background-color: rgb(43, 43, 43); color: rgb(204, 204, 204); border: 2px solid black }");
	dragSize->setFont(PixelFont("Microsoft YaHei UI", 10, 50));

	//初始化表格对象
	for (int r = 0; r < rowCount(); r++) {
		for(int c = 0; c < columnCount(); c++) {
			setItem(r, c, new QTableWidgetItem);
			item(r, c)->setBackgroundColor(PRIMARY_COLOR);
			item(r, c)->setTextAlignment(Qt::AlignCenter);
			item(r, c)->setText(QString(""));
			item(r, c)->setFont(PixelFont("宋体", 12, 50));
		}
	}

	//设置Block和Spliter的行宽及列高
	for (int r = 0; r < rowCount(); r++) {
		setRowHeight(r, BLOCK_SIZE);
	}
	for (int c = 0; c < columnCount(); c++) {
		setColumnWidth(c, BLOCK_SIZE);
	}
	for (int r = hintRow; r < rowCount(); r += 6) {
		setRowHeight(r, SPLITER_SIZE);
	}
	for (int c = hintColumn; c < columnCount(); c += 6) {
		setColumnWidth(c, SPLITER_SIZE);
	}

	//设置主Spliter颜色
	for (int r = 0; r < rowCount(); r++) {
		item(r, hintColumn)->setBackgroundColor(MAIN_SPLITER_COLOR);
	}
	for (int c = 0; c < columnCount(); c++) {
		item(hintRow, c)->setBackgroundColor(MAIN_SPLITER_COLOR);
	}

	//设置副Spliter颜色
	for (int r = hintRow + 6; r < rowCount(); r += 6) {
		for (int c = 0; c < columnCount(); c++) {
			item(r, c)->setBackgroundColor(SECONDARY_SPLITER_COLOR);
		}
	}
	for (int c = hintColumn + 6; c < columnCount(); c += 6) {
		for (int r = 0; r < rowCount(); r++) {
			item(r, c)->setBackgroundColor(SECONDARY_SPLITER_COLOR);
		}
	}

	//配置Hint
	for (int r = 0; r < hintRow; r++) {
		for (int c = hintColumn + 1; c < columnCount(); c++) {
			int hint = nonogramData[index].hintH[r][c - hintColumn - 1];
			if (hint != 0 && hint != -1) {
				item(r, c)->setTextColor(HINT_TEXT_COLOR);
				item(r, c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
				item(r, c)->setText(QString::number(hint));
				item(r, c)->setFont(PixelFont("Microsoft YaHei UI", 12, 50));
			}
		}
	}
	for (int c = 0; c < hintColumn; c++) {
		for (int r = hintRow + 1; r < rowCount(); r++) {
			int hint = nonogramData[index].hintV[c][r - hintRow - 1];
			if (hint != 0 && hint != -1) {
				item(r, c)->setTextColor(HINT_TEXT_COLOR);
				item(r, c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
				item(r, c)->setText(QString::number(hint));
				item(r, c)->setFont(PixelFont("Microsoft YaHei UI", 12, 50));
			}
		}
	}

	//连接信号与槽
	connect(this, &QAbstractItemView::entered, this, &Nonogram::getBlock);
}

//判断能否操作
bool Nonogram::canAct(int r, int c) {
	bool canAct = true;
	for (int _r = hintRow; _r < rowCount(); _r += 6) {
		if (r == _r) {
			canAct = false;
		}
	}
	for (int _c = hintColumn; _c < columnCount(); _c += 6) {
		if (c == _c) {
			canAct = false;
		}
	}
	if (r <= hintRow || c <= hintColumn) {
		canAct = false;
	}
	return canAct;
}

//十字高亮
bool Nonogram::crossHighlight(int r, int c) {
	if (!canAct(r, c)) {
		return false;
	}
	for (int _r = 0; _r < hintRow; _r++) {
		int hint = nonogramData[index].hintH[_r][c - hintColumn - 1];
		if (hint != 0 && hint != -1) {
			if (item(_r, c)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(_r, c)->setBackgroundColor(ACCENT_COLOR);
			}
		} else if (hint == 0) {
			item(_r, c)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	for (int _c = 0; _c < hintColumn; _c++) {
		int hint = nonogramData[index].hintV[_c][r - hintRow - 1];
		if (hint != 0 && hint != -1) {
			if (item(r, _c)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(r, _c)->setBackgroundColor(ACCENT_COLOR);
			}
		} else if (hint == 0) {
			item(r, _c)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	for (int _r = hintRow + 1; _r < rowCount(); _r++) {
		if (item(_r, c)->backgroundColor() == PRIMARY_COLOR && _r != r ) {
			item(_r, c)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	for (int _c = hintColumn + 1; _c < columnCount(); _c++) {
		if (item(r, _c)->backgroundColor() == PRIMARY_COLOR && _c != c) {
			item(r, _c)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	return true;
}

//清除十字高亮
void Nonogram::eraseCrossHighlight() {
	for (int r = 0; r < hintRow; r++) {
		int hint = nonogramData[index].hintH[r][lastC - hintColumn - 1];
		if (hint != 0 && hint != -1) {
			if (item(r, lastC)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(r, lastC)->setBackgroundColor(HINT_UNSOLVED_COLOR);
			}
		} else if (hint == 0) {
			item(r, lastC)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
	for (int c = 0; c < hintColumn; c++) {
		int hint = nonogramData[index].hintV[c][lastR - hintRow - 1];
		if (hint != 0 && hint != -1) {
			if (item(lastR, c)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(lastR, c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
			}
		} else if (hint == 0) {
			item(lastR, c)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
	for (int r = hintRow + 1; r < rowCount(); r++) {
		if (item(r, lastC)->backgroundColor() == CROSS_HIGHLIGHT_COLOR) {
			item(r, lastC)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
	for (int c = hintColumn + 1; c < columnCount(); c++) {
		if (item(lastR, c)->backgroundColor() == CROSS_HIGHLIGHT_COLOR) {
			item(lastR, c)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
}

//区域高亮
void Nonogram::areaHighlight() {
	int maxR = currentR >= recordR ? currentR : recordR;
	int minR = currentR < recordR ? currentR : recordR;
	int maxC = currentC >= recordC ? currentC : recordC;
	int minC = currentC < recordC ? currentC : recordC;
	minR = minR < hintRow + 1 ? hintRow + 1 : minR;
	minC = minC < hintColumn  + 1 ? hintColumn + 1 : minC;
	for (int r = minR; r <= maxR; r++) {
		if (crossHighlight(r, minC)) {
			dragR++;
		}
	}
	for (int c = minC; c <= maxC; c++) {
		if (crossHighlight(minR, c)) {
			dragC++;
		}
	}
	for (int r = minR; r <= maxR; r++) {
		for (int c = minC; c <= maxC; c++) {
			if (item(r, c)->backgroundColor() != SECONDARY_SPLITER_COLOR
					&& item(r, c)->backgroundColor() != DARK_COLOR
					&& item(r, c)->backgroundColor() != AREA_HIGHLIGHT_DARK_COLOR) {
				item(r, c)->setBackgroundColor(AREA_HIGHLIGHT_COLOR);
			} else if (item(r, c)->backgroundColor() == DARK_COLOR) {
				item(r, c)->setBackgroundColor(AREA_HIGHLIGHT_DARK_COLOR);
			}
		}
	}
}

//清除区域高亮
void Nonogram::eraseAreaHighlight() {
	int lastMaxR = lastR >= recordR ? lastR : recordR;
	int lastMinR = lastR < recordR ? lastR : recordR;
	int lastMaxC = lastC >= recordC ? lastC : recordC;
	int lastMinC = lastC < recordC ? lastC : recordC;
	lastMinR = lastMinR < hintRow + 1 ? hintRow + 1 : lastMinR;
	lastMinC = lastMinC < hintColumn + 1 ? hintColumn + 1 : lastMinC;
	for (int r = lastMinR; r <= lastMaxR; r++) {
		for (int c = lastMinC; c <= lastMaxC; c++) {
			if (item(r, c)->backgroundColor() == AREA_HIGHLIGHT_COLOR) {
				item(r, c)->setBackgroundColor(PRIMARY_COLOR);
			} else if (item(r, c)->backgroundColor() == AREA_HIGHLIGHT_DARK_COLOR) {
				item(r, c)->setBackgroundColor(DARK_COLOR);
			}
		}
	}
	for (int r = lastMinR; r <= lastMaxR; r++) {
		lastR = r;
		eraseCrossHighlight();
	}
	for (int c = lastMinC; c <= lastMaxC; c++) {
		lastC = c;
		eraseCrossHighlight();
	}
}

void Nonogram::getBlock(const QModelIndex& index) {
	//记录鼠标位置
	currentR = index.row();
	currentC = index.column();
	if (canAct(currentR, currentC)) {
		if (!mousePressed) {
			//跟随鼠标十字高亮
			eraseCrossHighlight();
			crossHighlight(currentR, currentC);
		} else if (canAct(recordR, recordC)) {
			//跟随鼠标及时调整选中区域高亮
			eraseAreaHighlight();
			areaHighlight();

			//显示拖动区域大小
			dragSize->setText(QString("%1x%2").arg(dragC).arg(dragR));
			dragC = 0;
			dragR = 0;
			dragSize->adjustSize();
			dragSize->setVisible(true);
		}
		lastR = currentR;
		lastC = currentC;
	}
}

void Nonogram::mousePressEvent(QMouseEvent *event) {
	QTableWidget::mousePressEvent(event);
	if (event->button() == Qt::LeftButton) {
		mousePressed = true;
		recordR = currentR;
		recordC = currentC;
	}
}

void Nonogram::mouseReleaseEvent(QMouseEvent *event) {
	QTableWidget::mouseReleaseEvent(event);
	if (event->button() == Qt::LeftButton) {
		mousePressed = false;
		dragSize->setVisible(false);
		int maxR = currentR >= recordR ? currentR : recordR;
		int minR = currentR < recordR ? currentR : recordR;
		int maxC = currentC >= recordC ? currentC : recordC;
		int minC = currentC < recordC ? currentC : recordC;
		minR = minR < hintRow + 1 ? hintRow + 1 : minR;
		minC = minC < hintColumn  + 1 ? hintColumn + 1 : minC;
		eraseAreaHighlight();
		if (canAct(currentR, currentC) && canAct(recordR, recordC)) {
			switch (gameWindow->toolType) {
			case 0:
				for (int r = minR; r <= maxR; r++) {
					for (int c = minC; c <= maxC; c++) {
						if (canAct(r, c)) {
							if (item(r, c)->backgroundColor() != DARK_COLOR) {
								record(r, c, DARK_COLOR, QString(""));
								gameWindow->btnReset->setDisabled(false);
								gameWindow->setWindowModified(true);
							}
							item(r, c)->setBackgroundColor(DARK_COLOR);
							item(r, c)->setText(QString(""));
							nonogramPreview->updatePreview(r, c, Qt::black);
							checkLineComplete(r, c);
						}
					}
				}
				break;
			case 1:
				for (int r = minR; r <= maxR; r++) {
					for (int c = minC; c <= maxC; c++) {
						if (canAct(r, c)) {
							if (item(r, c)->backgroundColor() != PRIMARY_COLOR || item(r, c)->text() != QString("")) {
								record(r, c, PRIMARY_COLOR, QString(""));
								gameWindow->btnReset->setDisabled(false);
								gameWindow->setWindowModified(true);
							}
							item(r, c)->setBackgroundColor(PRIMARY_COLOR);
							item(r, c)->setText(QString(""));
							nonogramPreview->updatePreview(r, c, Qt::white);
							checkLineComplete(r, c);
						}
					}
				}
				break;
			case 2:
				for (int r = minR; r <= maxR; r++) {
					for (int c = minC; c <= maxC; c++) {
						if (canAct(r, c)) {
							if (item(r, c)->text() != QString("╳")) {
								record(r, c, PRIMARY_COLOR, QString("╳"));
								gameWindow->btnReset->setDisabled(false);
								gameWindow->setWindowModified(true);
							}
							item(r, c)->setBackgroundColor(PRIMARY_COLOR);
							item(r, c)->setText(QString("╳"));
							nonogramPreview->updatePreview(r, c, Qt::white);
							checkLineComplete(r, c);
						}
					}
				}
				break;
			}
			crossHighlight(currentR, currentC);
			lastR = currentR;
			lastC = currentC;
		}
		checkGameComplete();
	}
}

void Nonogram::record(int r, int c, QColor newBackgroundColor, QString newText) {
	gameMove move;
	move.row = r;
	move.column = c;
	move.newBackgroundColor = newBackgroundColor;
	move.newText = newText;
	move.oldBackgroundColor = item(r, c)->backgroundColor();
	move.oldText = item(r, c)->text();
	undos.append(move);
	gameWindow->btnUndo->setDisabled(false);
	if (redos.length() != 0) {
		redos.clear();
		gameWindow->btnRedo->setDisabled(true);
	}
}

//撤销功能
void Nonogram::undo() {
	gameMove currentMove = undos[undos.length() - 1];
	item(currentMove.row, currentMove.column)->setBackgroundColor(currentMove.oldBackgroundColor);
	item(currentMove.row, currentMove.column)->setText(currentMove.oldText);
	QColor previewColor;
	if (currentMove.oldBackgroundColor == DARK_COLOR) {
		previewColor = Qt::black;
	}
	if (currentMove.oldBackgroundColor == PRIMARY_COLOR) {
		previewColor = Qt::white;
	}
	nonogramPreview->updatePreview(currentMove.row, currentMove.column, previewColor);
	checkLineComplete(currentMove.row, currentMove.column);
	eraseCrossHighlight();
	if (undos.length() == 1) {
		gameWindow->setWindowModified(false);
		gameWindow->btnUndo->setDisabled(true);
	} else {
		crossHighlight(currentMove.row, currentMove.column);
		lastC = currentMove.column;
		lastR = currentMove.row;
	}
	redos.append(currentMove);
	gameWindow->btnRedo->setDisabled(false);
	undos.pop_back();
	checkGameComplete();
}

//重做功能
void Nonogram::redo() {
	gameMove currentMove = redos[redos.length() - 1];
	item(currentMove.row, currentMove.column)->setBackgroundColor(currentMove.newBackgroundColor);
	item(currentMove.row, currentMove.column)->setText(currentMove.newText);
	QColor previewColor;
	if (currentMove.newBackgroundColor == DARK_COLOR) {
		previewColor = Qt::black;
	}
	if (currentMove.newBackgroundColor == PRIMARY_COLOR) {
		previewColor = Qt::white;
	}
	nonogramPreview->updatePreview(currentMove.row, currentMove.column, previewColor);
	checkLineComplete(currentMove.row, currentMove.column);
	eraseCrossHighlight();
	crossHighlight(currentMove.row, currentMove.column);
	lastC = currentMove.column;
	lastR = currentMove.row;
	if (redos.length() == 1) {
		gameWindow->btnRedo->setDisabled(true);
	}
	undos.append(currentMove);
	gameWindow->btnUndo->setDisabled(false);
	redos.pop_back();
}

//重置游戏功能
void Nonogram::resetGame() {
	InfoWindow info(tr("是否重置游戏？您将丢失该网格画的全部进度！"), 2, this);
	int r = info.exec();
	if (r == QDialog::Accepted) {

		//重置游戏区域
		eraseCrossHighlight();
		for (int r = hintRow + 1; r < rowCount(); r++) {
			for (int c = hintColumn + 1; c < columnCount(); c++) {
				if (item(r, c)->backgroundColor() != SECONDARY_SPLITER_COLOR) {
					item(r, c)->setBackgroundColor(PRIMARY_COLOR);
					item(r, c)->setText(QString(""));
					nonogramPreview->updatePreview(r, c, Qt::white);
				}
			}
		}

		for (int r = hintRow + 1; r < rowCount(); r++) {
			if (canAct(r, hintColumn + 1)) {
				checkLineComplete(r, hintColumn + 1);
			}
		}
		for (int c = hintColumn + 1; c < columnCount(); c++) {
			if (canAct(hintRow + 1, c)) {
				checkLineComplete(hintRow + 1, c);
			}
		}

		undos.clear();
		redos.clear();
		currentR = -1;
		currentC = -1;
		lastR = hintRow + 1;
		lastC = hintColumn + 1;
		remove("save.nonogram");
		gBtnResume->setDisabled(true);
		gameWindow->setWindowModified(false);
		gameWindow->btnUndo->setDisabled(true);
		gameWindow->btnRedo->setDisabled(true);
		gameWindow->btnReset->setDisabled(true);
	}
}

//判断单行单列完成
void Nonogram::checkLineComplete(int r, int c) {
	QVector<int> row = readRow(r, this);
	QVector<int> column = readColumn(c, this);
	QVector<int> hRow = readHintRow(r - hintRow - 1, this);
	QVector<int> hColumn = readHintColumn(c - hintColumn - 1, this);
	if (row == hRow) {
		for (int _c = 0; _c < hintColumn; _c++) {
			if (nonogramData[index].hintV[_c][r - hintRow - 1] != 0) {
				item(r, _c)->setBackgroundColor(HINT_SOLVED_COLOR);
			}
		}
	} else {
		if (currentR == r && currentC == c) {
			for (int _c = 0; _c < hintColumn; _c++) {
				if (nonogramData[index].hintV[_c][r - hintRow - 1] != 0) {
					item(r, _c)->setBackgroundColor(ACCENT_COLOR);
				}
			}
		} else {
			for (int _c = 0; _c < hintColumn; _c++) {
				if (nonogramData[index].hintV[_c][r - hintRow - 1] != 0) {
					item(r, _c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
				}
			}
		}
	}
	if (column == hColumn) {
		for (int _r = 0; _r < hintRow; _r++) {
			if (nonogramData[index].hintH[_r][c - hintColumn - 1] != 0) {
				item(_r, c)->setBackgroundColor(HINT_SOLVED_COLOR);
			}
		}
	} else {
		if (currentR == r && currentC == c) {
			for (int _r = 0; _r < hintRow; _r++) {
				if (nonogramData[index].hintH[_r][c - hintColumn - 1] != 0) {
					item(_r, c)->setBackgroundColor(ACCENT_COLOR);
				}
			}
		} else {
			for (int _r = 0; _r < hintRow; _r++) {
				if (nonogramData[index].hintH[_r][c - hintColumn - 1] != 0) {
					item(_r, c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
				}
			}
		}
	}
}

//判断游戏完成
void Nonogram::checkGameComplete() {
	complete = true;
	for (int c = hintColumn + 1; c < columnCount(); c++) {
		QColor tmp = item(hintRow - 1, c)->backgroundColor();
		if (tmp != HINT_SOLVED_COLOR && tmp != SECONDARY_SPLITER_COLOR && tmp != PRIMARY_COLOR) {
			complete = false;
		}
	}
	for (int r = hintRow + 1; r < rowCount(); r++) {
		QColor tmp = item(r, hintColumn - 1)->backgroundColor();
		if (tmp != HINT_SOLVED_COLOR && tmp != SECONDARY_SPLITER_COLOR && tmp != PRIMARY_COLOR) {
			complete = false;
		}
	}	

	if (complete) {
		viewport()->installEventFilter(gameWindow);
		disconnect(this, &QAbstractItemView::entered, this, &Nonogram::getBlock);
		setShowGrid(false);
		setMouseTracking(false);
		viewport()->setCursor(Qt::ArrowCursor);
		eraseCrossHighlight();
		if (gameColumn * BLOCK_SIZE + 2 < minimumWidth()) {
			setMinimumWidth(gameColumn * BLOCK_SIZE + 2);
		}
		if (gameRow * BLOCK_SIZE + 2 < minimumHeight()) {
			setMinimumHeight(gameRow * BLOCK_SIZE + 2);
		}
		for (int r = 0; r < rowCount(); r++) {
			for(int c = 0; c < columnCount(); c++) {
				item(r, c)->setText(QString(""));
			}
		}

		for (int r = 0; r < hintRow; r++) {
			setRowHeight(r, 0);
		}
		for (int c = 0; c < hintColumn; c++) {
			setColumnWidth(c, 0);
		}
		for (int r = hintRow; r < rowCount(); r += 6) {
			setRowHeight(r, 0);
		}
		for (int c = hintColumn; c < columnCount(); c += 6) {
			setColumnWidth(c, 0);
		}

		undos.clear();
		redos.clear();
		preview->hide();
		gameWindow->onComplete(nonogramData[index].name);
	}
}
