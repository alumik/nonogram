#include "nonogrampreview.h"
#include "define.h"

#include <QHeaderView>

NonogramPreview::NonogramPreview(int pGameRow,
								 int pGameColumn,
								 int pHintRow,
								 int pHintColumn,
								 int pSpliterRow,
								 int pSpliterColumn,
								 QWidget* parent)
	: QTableWidget(parent) {

	cHintRow = pHintRow;
	cHintColumn = pHintColumn;

	setShowGrid(false);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	setFocusPolicy(Qt::NoFocus);
	setFrameShape(QFrame::NoFrame);
	setSelectionMode(QTableWidget::NoSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSizeAdjustPolicy(QTableWidget::AdjustToContents);

	double gameRatio = (double)pGameRow / pGameColumn;
	double hintRatio = (double)cHintRow / cHintColumn;
	int blockSize = 0;
	if (gameRatio >= hintRatio) {
		int cHeight = cHintRow * BLOCK_SIZE - 5;
		blockSize = cHeight / pGameRow;
	} else {
		int cWidth = cHintColumn * BLOCK_SIZE - 5;
		blockSize = cWidth / pGameColumn;
	}

	setRowCount(pGameRow + pSpliterRow + cHintRow + 1);
	setColumnCount(pGameColumn + pSpliterColumn + cHintColumn + 1);

	//初始化表格对象
	for (int r = 0; r < rowCount(); r++) {
		for(int c = 0; c < columnCount(); c++) {
			setItem(r, c, new QTableWidgetItem);
		}
	}

	for (int r = 0; r < cHintRow; r++) {
		setRowHeight(r, 0);
	}
	for (int c = 0; c < cHintColumn; c++) {
		setColumnWidth(c, 0);
	}
	for (int r = cHintRow + 1; r < rowCount(); r++) {
		setRowHeight(r, blockSize);
	}
	for (int c = cHintColumn + 1; c < columnCount(); c++) {
		setColumnWidth(c, blockSize);
	}
	for (int r = cHintRow; r < rowCount(); r += 6) {
		setRowHeight(r, 0);
	}
	for (int c = cHintColumn; c < columnCount(); c += 6) {
		setColumnWidth(c, 0);
	}
}

void NonogramPreview::resizeEvent(QResizeEvent *event) {
	move((cHintColumn * BLOCK_SIZE - 2 - event->size().width()) / 2 + 2,
		 (cHintRow * BLOCK_SIZE - 2 - event->size().height()) / 2 + 2);
}

void NonogramPreview::updatePreview(int r, int c, QColor color) {
	item(r, c)->setBackgroundColor(color);
}
