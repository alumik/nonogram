#include "nonogram.h"
#include "controller_game.h"
#include "util_generic_define.h"
#include "util_pixel_font.h"

#include <QHeaderView>

Nonogram::Nonogram(QWidget* parent) : QTableWidget(parent) {
    loadGameMeta();

    PVector hint_grid(hint.left.size, hint.top.size);
    last_pos = hint_grid + 1;

    PVector separator = game_grid / 5;
    if (game_grid.column() % 5 == 0) {
        separator.column()--;
    }
    if (game_grid.row() % 5 == 0) {
        separator.row()--;
    }

    PVector table_grid = game_grid + hint_grid + separator + 1;
    setColumnCount(table_grid.column());
    setRowCount(table_grid.row());

    table_size = (game_grid + hint_grid) * BLOCK_SIZE + (separator + 1) * SEPARATOR_SIZE + 2;
    table_size.singleJudge(635, std::greater<int>());
    PVector min_size = PVector::singleJudge(table_size, 15 * BLOCK_SIZE, std::greater_equal<int>());
    setMinimumWidth(min_size.width());
    setMinimumHeight(min_size.height());

    complete = false;
    mouse_pressed = false;
    setMouseTracking(true);
    verticalHeader()->hide();
    verticalHeader()->setMinimumSectionSize(1);
    horizontalHeader()->hide();
    horizontalHeader()->setMinimumSectionSize(1);
    setFocusPolicy(Qt::NoFocus);
    setSelectionMode(QTableWidget::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    setStyleSheet("QTableWidget { gridline-color: rgb(0, 0, 0) }");

    label_preview = new QLabel(this);
    label_preview->move(1, 1);
    label_preview->setStyleSheet("QLabel { background-color: rgb(255, 255, 255) }");
    label_preview->setFixedSize(hint.left.size * BLOCK_SIZE, hint.top.size * BLOCK_SIZE);
    label_preview->setFrameShape(QFrame::Box);
    label_preview->setLineWidth(2);
    nonogram_preview = new NonogramPreview(game_grid, hint_grid, separator, label_preview);

    label_drag = new QLabel(this);
    label_drag->setVisible(false);
    label_drag->move(1, 1);
    label_drag->setStyleSheet("QLabel { background-color: rgb(43, 43, 43); color: rgb(204, 204, 204); border: 2px solid black }");
    label_drag->setFont(PixelFont("Microsoft YaHei UI", 10, 50));

    for (auto row = 0; row < rowCount(); row++) {
        for (auto column = 0; column < columnCount(); column++) {
            setItem(row, column, new QTableWidgetItem);
            item(row, column)->setBackgroundColor(PRIMARY_COLOR);
            item(row, column)->setTextAlignment(Qt::AlignCenter);
            item(row, column)->setText(QString(""));
            item(row, column)->setFont(PixelFont("宋体", 12, 50));
        }
    }

    for (auto column = 0; column < columnCount(); column++) {
        setColumnWidth(column, BLOCK_SIZE);
    }
    for (auto row = 0; row < rowCount(); row++) {
        setRowHeight(row, BLOCK_SIZE);
    }
    for (auto column = hint.left.size; column < columnCount(); column++) {
        setColumnWidth(column, SEPARATOR_SIZE);
    }
    for (auto row = hint.top.size; row < rowCount(); row++) {
        setRowHeight(row, SEPARATOR_SIZE);
    }

    for (auto column = 0; column < columnCount(); column++) {
        item(hint.top.size, column)->setBackgroundColor(MAIN_SEPARATOR_COLOR);
    }
    for (auto row = 0; row < rowCount(); row++) {
        item(row, hint.left.size)->setBackgroundColor(MAIN_SEPARATOR_COLOR);
    }

    for (auto column = hint.left.size + 6; column < columnCount(); column += 6) {
        for (auto row = 0; row < rowCount(); row++) {
            item(row, column)->setBackgroundColor(SECONDARY_SEPARATOR_COLOR);
        }
    }
    for (auto row = hint.top.size + 6; row < rowCount(); row += 6) {
        for (auto column = 0; column < columnCount(); column++) {
            item(row, column)->setBackgroundColor(SECONDARY_SEPARATOR_COLOR);
        }
    }

    for (auto row = 0; row < hint.top.size; row++) {
        for (auto column = hint.left.size + 1; column < columnCount(); column++) {
            const auto hint_data = hint.top.data[row][column - (hint.left.size + 1)];
            if (hint_data != Nonogram::NO_HINT && hint_data != Nonogram::SEPARATOR_HINT) {
                item(row, column)->setTextColor(HINT_TEXT_COLOR);
                item(row, column)->setBackgroundColor(HINT_UNSOLVED_COLOR);
                item(row, column)->setText(QString::number(hint_data));
                item(row, column)->setFont(PixelFont("Microsoft YaHei UI", 12, 50));
            }
        }
    }

    for (auto column = 0; column < hint.left.size; column++) {
        for (auto row = hint.top.size + 1; row < rowCount(); row++) {
            const auto hint_data = hint.left.data[column][row - (hint.top.size + 1)];
            if (hint_data != Nonogram::NO_HINT && hint_data != Nonogram::SEPARATOR_HINT) {
                item(row, column)->setTextColor(HINT_TEXT_COLOR);
                item(row, column)->setBackgroundColor(HINT_UNSOLVED_COLOR);
                item(row, column)->setText(QString::number(hint_data));
                item(row, column)->setFont(PixelFont("Microsoft YaHei UI", 12, 50));
            }
        }
    }

    connect(this, &QAbstractItemView::entered, this, &Nonogram::getBlock);
}

void Nonogram::loadGameMeta() {
    index = GameController::nonogram_index;
    title = nonogram_data[index].title;
    game_grid = nonogram_data[index].game_grid;
    hint = nonogram_data[index].hint;
}
