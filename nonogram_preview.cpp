#include "nonogram_preview.h"
#include "define.h"

#include <QHeaderView>

/**
 * \brief 完成情况预览窗
 * \param p_game_row 
 * \param p_game_column 
 * \param p_hint_row 
 * \param p_hint_column 
 * \param p_spliter_row 
 * \param p_spliter_column 
 * \param parent 
 */
NonogramPreview::NonogramPreview(const int p_game_row,
                                 const int p_game_column,
                                 const int p_hint_row,
                                 const int p_hint_column,
                                 const int p_spliter_row,
                                 const int p_spliter_column,
								 QWidget* parent)
	: QTableWidget(parent) {

	c_hint_row = p_hint_row;
	c_hint_column = p_hint_column;

	setShowGrid(false);
	verticalHeader()->hide();
    verticalHeader()->setMinimumSectionSize(1);
	horizontalHeader()->hide();
    horizontalHeader()->setMinimumSectionSize(1);
	setFocusPolicy(Qt::NoFocus);
	setFrameShape(QFrame::NoFrame);
	setSelectionMode(QTableWidget::NoSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSizeAdjustPolicy(QTableWidget::AdjustToContents);

	const auto game_ratio = static_cast<double>(p_game_row) / p_game_column;
	const auto hint_ratio = static_cast<double>(c_hint_row) / c_hint_column;
	int block_size;
	if (game_ratio >= hint_ratio) {
		const auto c_height = c_hint_row * BLOCK_SIZE - 5;
		block_size = c_height / p_game_row;
	} else {
		const auto c_width = c_hint_column * BLOCK_SIZE - 5;
		block_size = c_width / p_game_column;
	}

	setRowCount(p_game_row + p_spliter_row + c_hint_row + 1);
	setColumnCount(p_game_column + p_spliter_column + c_hint_column + 1);

	// 初始化表格对象
	for (auto r = 0; r < rowCount(); r++) {
		for(auto c = 0; c < columnCount(); c++) {
			setItem(r, c, new QTableWidgetItem);
		}
	}

	for (auto r = 0; r < c_hint_row; r++) {
		setRowHeight(r, 0);
	}
	for (auto c = 0; c < c_hint_column; c++) {
		setColumnWidth(c, 0);
	}
	for (auto r = c_hint_row + 1; r < rowCount(); r++) {
		setRowHeight(r, block_size);
	}
	for (auto c = c_hint_column + 1; c < columnCount(); c++) {
		setColumnWidth(c, block_size);
	}
	for (auto r = c_hint_row; r < rowCount(); r += 6) {
		setRowHeight(r, 0);
	}
	for (auto c = c_hint_column; c < columnCount(); c += 6) {
		setColumnWidth(c, 0);
	}
}

/**
 * \brief 改变窗口大小事件
 * \param event 
 */
void NonogramPreview::resizeEvent(QResizeEvent *event) {
	move((c_hint_column * BLOCK_SIZE - 2 - event->size().width()) / 2 + 2,
		 (c_hint_row * BLOCK_SIZE - 2 - event->size().height()) / 2 + 2);
}

/**
 * \brief 更新预览窗
 * \param r 
 * \param c 
 * \param color 
 */
void NonogramPreview::updatePreview(const int r, const int c, const QColor& color) const {
	item(r, c)->setBackgroundColor(color);
}
