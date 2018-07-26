#include "nonogram_preview.h"
#include "util_generic_define.h"

#include <QHeaderView>

NonogramPreview::NonogramPreview(PVector _game_grid,
                                 PVector _hint_grid,
                                 PVector _separator,
                                 QWidget* parent)
    : QTableWidget(parent) {

    hint_grid = _hint_grid;
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

    const auto game_ratio = static_cast<double>(_game_grid.row()) / _game_grid.column();
    const auto hint_ratio = static_cast<double>(_hint_grid.row()) / _hint_grid.column();
    int block_size;
    if (game_ratio >= hint_ratio) {
        const auto height = _hint_grid.row() * BLOCK_SIZE - 5;
        block_size = height / _game_grid.row();
    } else {
        const auto width = _hint_grid.column() * BLOCK_SIZE - 5;
        block_size = width / _game_grid.column();
    }

    PVector table_grid = _game_grid + _separator + _hint_grid + 1;
    setRowCount(table_grid.row());
    setColumnCount(table_grid.column());

    // 初始化表格对象
    for (auto row = 0; row < rowCount(); row++) {
        for(auto column = 0; column < columnCount(); column++) {
            setItem(row, column, new QTableWidgetItem);
        }
    }

    for (auto row = 0; row < _hint_grid.row(); row++) {
        setRowHeight(row, 0);
    }
    for (auto column = 0; column < _hint_grid.column(); column++) {
        setColumnWidth(column, 0);
    }
    for (auto row = _hint_grid.row() + 1; row < rowCount(); row++) {
        setRowHeight(row, block_size);
    }
    for (auto column = _hint_grid.column() + 1; column < columnCount(); column++) {
        setColumnWidth(column, block_size);
    }
    for (auto row = _hint_grid.row(); row < rowCount(); row += 6) {
        setRowHeight(row, 0);
    }
    for (auto column = _hint_grid.column(); column < columnCount(); column += 6) {
        setColumnWidth(column, 0);
    }
}

/**
 * \brief 改变窗口大小事件
 * \param event 
 */
void NonogramPreview::resizeEvent(QResizeEvent *event) {
    move((hint_grid.column() * BLOCK_SIZE - 2 - event->size().width()) / 2 + 2,
         (hint_grid.row() * BLOCK_SIZE - 2 - event->size().height()) / 2 + 2);
}

/**
 * \brief 更新预览窗
 * \param r 
 * \param c 
 * \param color 
 */
void NonogramPreview::updatePreview(PVector pos, const QColor& color) const {
    item(pos.row(), pos.column())->setBackgroundColor(color);
}
