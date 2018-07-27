#include "nonogram_preview.h"
#include "util/util_generic_define.h"

#include <QHeaderView>

/**
 * \brief 网格画完成效果预览框
 * \param game_grid 游戏网格尺寸
 * \param hint_grid 提示网格尺寸
 * \param separator 分割线数量
 * \param parent 父部件指针
 */
NonogramPreview::NonogramPreview(PVector game_grid,
                                 PVector hint_grid,
                                 const PVector separator,
                                 QWidget* parent)
		: QTableWidget(parent) {
	// 配置预览框参数
    private_hint_grid = hint_grid;
    setShowGrid(false);
    verticalHeader()->hide();
    horizontalHeader()->hide();
    verticalHeader()->setMinimumSectionSize(1);
    horizontalHeader()->setMinimumSectionSize(1);
    setFocusPolicy(Qt::NoFocus);
    setFrameShape(QFrame::NoFrame);
    setSelectionMode(QTableWidget::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSizeAdjustPolicy(QTableWidget::AdjustToContents);

	// 计算预览框大小
    const auto game_ratio = static_cast<double>(game_grid.row()) / game_grid.column();
    const auto hint_ratio = static_cast<double>(hint_grid.row()) / hint_grid.column();
    int block_size;
    if (game_ratio >= hint_ratio) {
        const auto height = hint_grid.row() * BLOCK_SIZE - 5;
        block_size = height / game_grid.row();
    } else {
        const auto width = hint_grid.column() * BLOCK_SIZE - 5;
        block_size = width / game_grid.column();
    }

	// 设置预览框尺寸
	auto table_grid = game_grid + separator + hint_grid + 1;
    setRowCount(table_grid.row());
    setColumnCount(table_grid.column());

    // 初始化表格对象
    for (auto row = 0; row < rowCount(); row++) {
        for(auto column = 0; column < columnCount(); column++) {
            setItem(row, column, new QTableWidgetItem);
        }
    }

	// 设置行列宽高度
    for (auto row = 0; row < hint_grid.row(); row++) {
        setRowHeight(row, 0);
    }
    for (auto column = 0; column < hint_grid.column(); column++) {
        setColumnWidth(column, 0);
    }
    for (auto row = hint_grid.row() + 1; row < rowCount(); row++) {
        setRowHeight(row, block_size);
    }
    for (auto column = hint_grid.column() + 1; column < columnCount(); column++) {
        setColumnWidth(column, block_size);
    }
    for (auto row = hint_grid.row(); row < rowCount(); row += 6) {
        setRowHeight(row, 0);
    }
    for (auto column = hint_grid.column(); column < columnCount(); column += 6) {
        setColumnWidth(column, 0);
    }
}

/**
 * \brief 改变界面大小
 * \param event 改变窗口大小事件
 */
void NonogramPreview::resizeEvent(QResizeEvent *event) {
    move((private_hint_grid.column() * BLOCK_SIZE - 2 - event->size().width()) / 2 + 2,
         (private_hint_grid.row() * BLOCK_SIZE - 2 - event->size().height()) / 2 + 2);
}

/**
 * \brief 更新预览框
 * \param pos 要更新的位置
 * \param fill 是否填充颜色
 */
void NonogramPreview::updatePreview(PVector pos, const bool fill) const {
    item(pos.row(), pos.column())->setBackgroundColor(fill ? Qt::black : Qt::white);
}
