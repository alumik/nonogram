#include "src/core/nonogram.h"
#include "src/controllers/controller_game.h"
#include "src/utils/util_generic_define.h"
#include "src/utils/util_pixel_font.h"
#include "src/windows/window_info.h"

#include <QHeaderView>
#include <fstream>

/**
 * \brief 网格画构造函数
 * \param parent 父部件指针
 */
Nonogram::Nonogram(QWidget* parent) : QTableWidget(parent) {
    index = GameController::nonogram_index;
    title = global_nonogram_data[index].title;
    game_grid = global_nonogram_data[index].game_grid;
    hint = global_nonogram_data[index].hint;
	const PVector hint_grid(hint.left.size, hint.top.size);
    last_pos = hint_grid + 1;

	auto separator = game_grid / 5;
    if (game_grid.column() % 5 == 0) {
        separator.column()--;
    }
    if (game_grid.row() % 5 == 0) {
        separator.row()--;
    }

	auto table_grid = game_grid + hint_grid + separator + 1;
    setColumnCount(table_grid.column());
    setRowCount(table_grid.row());

    table_size = (game_grid + hint_grid) * BLOCK_SIZE + (separator + 1) * SEPARATOR_SIZE + 2;
    table_size.sepCompare(635, std::less<>());
    auto min_size = PVector::sepCompare(table_size, 15 * BLOCK_SIZE, std::less<>());
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
    label_drag->setStyleSheet(
        "QLabel { background-color: rgb(43, 43, 43); color: rgb(204, 204, 204); border: 2px solid black }"
    );
    label_drag->setFont(PixelFont("Microsoft YaHei UI", 10, 50));

    for (auto row = 0; row < rowCount(); row++) {
        for (auto column = 0; column < columnCount(); column++) {
            setItem(row, column, new QTableWidgetItem);
            item(row, column)->setBackgroundColor(PRIMARY_COLOR);
            item(row, column)->setTextAlignment(Qt::AlignCenter);
            item(row, column)->setText(EMPTY_SYMBOL);
            item(row, column)->setFont(PixelFont("宋体", 12, 50));
        }
    }

    for (auto column = 0; column < columnCount(); column++) {
        setColumnWidth(column, BLOCK_SIZE);
    }
    for (auto row = 0; row < rowCount(); row++) {
        setRowHeight(row, BLOCK_SIZE);
    }
    for (auto column = hint.left.size; column < columnCount(); column += 6) {
        setColumnWidth(column, SEPARATOR_SIZE);
    }
    for (auto row = hint.top.size; row < rowCount(); row += 6) {
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

    for (auto row = hint.top.size + 1; row < rowCount(); row++) {
        hint_row_vector.append(readHintRow(row - (hint.top.size + 1)));
    }
    for (auto column = hint.left.size + 1; column < columnCount(); column++) {
        hint_column_vector.append(readHintColumn(column - (hint.left.size + 1)));
    }

    connect(this, &QAbstractItemView::entered, this, &Nonogram::getBlock);
}

/**
 * \brief 判断鼠标所在网格是否可操作
 * \param pos 位置
 * \return 
 */
bool Nonogram::canAct(PVector pos) const {
    for (auto column = hint.left.size; column < columnCount(); column += 6) {
        if (column == pos.column()) {
            return false;
        }
    }
    for (auto row = hint.top.size; row < rowCount(); row += 6) {
        if (row == pos.row()) {
            return false;
        }
    }
	return !(pos.column() < hint.left.size || pos.row() < hint.top.size);
}

/**
 * \brief 以指定位置为中心进行十字高亮
 * \param pos 位置
 * \return 
 */
bool Nonogram::crossHighlight(PVector pos) {
    if (!canAct(pos)) {
        return false;
    }

    for (auto row = 0; row < hint.top.size; row++) {
        const auto hint_data = hint.top.data[row][pos.column() - (hint.left.size + 1)];
        if (hint_data != Nonogram::NO_HINT && hint_data != Nonogram::SEPARATOR_HINT) {
            if (item(row, pos.column())->backgroundColor() != HINT_SOLVED_COLOR) {
                item(row, pos.column())->setBackgroundColor(ACCENT_COLOR);
            }
        } else if (hint_data == Nonogram::NO_HINT) {
            item(row, pos.column())->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
        }
    }
    for (auto column = 0; column < hint.left.size; column++) {
        const auto hint_data = hint.left.data[column][pos.row() - (hint.top.size + 1)];
        if (hint_data != Nonogram::NO_HINT && hint_data != Nonogram::SEPARATOR_HINT) {
            if (item(pos.row(), column)->backgroundColor() != HINT_SOLVED_COLOR) {
                item(pos.row(), column)->setBackgroundColor(ACCENT_COLOR);
            }
        } else if (hint_data == Nonogram::NO_HINT) {
            item(pos.row(), column)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
        }
    }

    for (auto row = hint.top.size + 1; row < rowCount(); row++) {
        if (item(row, pos.column())->backgroundColor() == PRIMARY_COLOR && row != pos.row()) {
            item(row, pos.column())->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
        }
    }
    for (auto column = hint.left.size + 1; column < columnCount(); column++) {
        if (item(pos.row(), column)->backgroundColor() == PRIMARY_COLOR && column != pos.column()) {
            item(pos.row(), column)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
        }
    }

    last_cross_highlighted_pos = pos;
    return true;
}

/**
 * \brief 删除上一次的十字高亮
 */
void Nonogram::eraseLastCrossHighlight() {
    for (auto row = 0; row < hint.top.size; row++) {
        const auto hint_data = hint.top.data[row][last_cross_highlighted_pos.column() - (hint.left.size + 1)];
        if (hint_data != Nonogram::NO_HINT && hint_data != Nonogram::SEPARATOR_HINT) {
            if (item(row, last_cross_highlighted_pos.column())->backgroundColor() != HINT_SOLVED_COLOR) {
                item(row, last_cross_highlighted_pos.column())->setBackgroundColor(HINT_UNSOLVED_COLOR);
            }
        } else if (hint_data == Nonogram::NO_HINT) {
            item(row, last_cross_highlighted_pos.column())->setBackgroundColor(PRIMARY_COLOR);
        }
    }
    for (auto column = 0; column < hint.left.size; column++) {
        const auto hint_data = hint.left.data[column][last_cross_highlighted_pos.row() - (hint.top.size + 1)];
        if (hint_data != Nonogram::NO_HINT && hint_data != Nonogram::SEPARATOR_HINT) {
            if (item(last_cross_highlighted_pos.row(), column)->backgroundColor() != HINT_SOLVED_COLOR) {
                item(last_cross_highlighted_pos.row(), column)->setBackgroundColor(HINT_UNSOLVED_COLOR);
            }
        } else if (hint_data == Nonogram::NO_HINT) {
            item(last_cross_highlighted_pos.row(), column)->setBackgroundColor(PRIMARY_COLOR);
        }
    }

    for (auto row = hint.top.size + 1; row < rowCount(); row++) {
        if (item(row, last_cross_highlighted_pos.column())->backgroundColor() == CROSS_HIGHLIGHT_COLOR) {
            item(row, last_cross_highlighted_pos.column())->setBackgroundColor(PRIMARY_COLOR);
        }
    }
    for (auto column = hint.left.size + 1; column < columnCount(); column++) {
        if (item(last_cross_highlighted_pos.row(), column)->backgroundColor() == CROSS_HIGHLIGHT_COLOR) {
            item(last_cross_highlighted_pos.row(), column)->setBackgroundColor(PRIMARY_COLOR);
        }
    }
}

/**
 * \brief 区域高亮
 */
void Nonogram::areaHighlight() {
	auto max_pos = PVector::sepCompare(current_pos, record_pos, std::greater<>());
	auto min_pos = PVector::sepCompare(current_pos, record_pos, std::less<>());
    min_pos.sepCompare(PVector(hint.left.size, hint.top.size) + 1, std::greater<>());

    for (auto column = min_pos.column(); column <= max_pos.column(); column++) {
        if (crossHighlight(PVector(column, min_pos.row()))) {
            drag_size.column()++;
        }
    }
    for (auto row = min_pos.row(); row <= max_pos.row(); row++) {
        if (crossHighlight(PVector(min_pos.column(), row))) {
            drag_size.row()++;
        }
    }

    for (auto row = min_pos.row(); row <= max_pos.row(); row++) {
        for (auto column = min_pos.column(); column <= max_pos.column(); column++) {
            if (item(row, column)->backgroundColor() != SECONDARY_SEPARATOR_COLOR
                    && item(row, column)->backgroundColor() != DARK_COLOR
                    && item(row, column)->backgroundColor() != AREA_HIGHLIGHT_DARK_COLOR) {
                item(row, column)->setBackgroundColor(AREA_HIGHLIGHT_COLOR);
            } else if (item(row, column)->backgroundColor() == DARK_COLOR) {
                item(row, column)->setBackgroundColor(AREA_HIGHLIGHT_DARK_COLOR);
            }
        }
    }
}

/**
 * \brief 删除区域高亮
 */
void Nonogram::eraseAreaHighlight() {
	auto max_pos = PVector::sepCompare(last_pos, record_pos, std::greater<>());
	auto min_pos = PVector::sepCompare(last_pos, record_pos, std::less<>());
    min_pos.sepCompare(PVector(hint.left.size, hint.top.size) + 1, std::greater<>());

    for (auto row = min_pos.row(); row <= max_pos.row(); row++) {
        for (auto column = min_pos.column(); column <= max_pos.column(); column++) {
            if (item(row, column)->backgroundColor() == AREA_HIGHLIGHT_COLOR) {
                item(row, column)->setBackgroundColor(PRIMARY_COLOR);
            } else if (item(row, column)->backgroundColor() == AREA_HIGHLIGHT_DARK_COLOR) {
                item(row, column)->setBackgroundColor(DARK_COLOR);
            }
        }
    }

    for (auto column = min_pos.column(); column <= max_pos.column(); column++) {
        last_cross_highlighted_pos.column() = column;
        eraseLastCrossHighlight();
    }

    for (auto row = min_pos.row(); row <= max_pos.row(); row++) {
        last_cross_highlighted_pos.row() = row;
        eraseLastCrossHighlight();
    }
}

/**
 * \brief 获取当前鼠标所在网格坐标并进行记录
 * \param index 鼠标位置
 */
void Nonogram::getBlock(const QModelIndex& index) {
    current_pos = PVector(index.column(), index.row());
    if (canAct(current_pos)) {
        if (!mouse_pressed) {
            eraseLastCrossHighlight();
            crossHighlight(current_pos);
        } else if (canAct(record_pos)) {
            eraseAreaHighlight();
            areaHighlight();
            label_drag->setText(QString("%1x%2").arg(drag_size.column()).arg(drag_size.row()));
            drag_size = PVector();
            label_drag->adjustSize();
            label_drag->setVisible(true);
        }
        last_pos = current_pos;
    }
}

/**
 * \brief 鼠标按下事件响应
 * \param event 鼠标按下事件
 */
void Nonogram::mousePressEvent(QMouseEvent* event) {
    QTableWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        mouse_pressed = true;
        record_pos = current_pos;
    }
}

/**
 * \brief 鼠标松开事件响应
 * \param event 鼠标松开事件
 */
void Nonogram::mouseReleaseEvent(QMouseEvent* event) {
    QTableWidget::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton) {
        mouse_pressed =false;
        label_drag->setVisible(false);

	    auto max_pos = PVector::sepCompare(current_pos, record_pos, std::greater<>());
	    auto min_pos = PVector::sepCompare(current_pos, record_pos, std::less<>());
        min_pos.sepCompare(PVector(hint.left.size, hint.top.size) + 1, std::greater<>());

        if (canAct(current_pos)) {
            eraseLastCrossHighlight();
            eraseAreaHighlight();
            crossHighlight(current_pos);
        }

        if (canAct(current_pos) && canAct(record_pos)) {
            switch (GameController::game_window->getToolType()) {
                case GameWindow::TOOL_PAINT:
                    for (auto row = min_pos.row(); row <= max_pos.row(); row++) {
                        for (auto column = min_pos.column(); column <= max_pos.column(); column++) {
	                        const PVector pos(column, row);
                            if (canAct(pos)) {
                                if (item(row, column)->backgroundColor() != DARK_COLOR) {
                                    record(pos, DARK_COLOR, EMPTY_SYMBOL);
                                    GameController::setReset(true);
                                    GameController::setModified(true);
                                }
                                item(row, column)->setBackgroundColor(DARK_COLOR);
                                item(row, column)->setText(EMPTY_SYMBOL);
                                nonogram_preview->updatePreview(pos, NonogramPreview::PRV_FILL);
                                checkCrossComplete(pos);
                            }
                        }
                    }
                    break;
                case GameWindow::TOOL_ERASE:
                    for (auto row = min_pos.row(); row <= max_pos.row(); row++) {
                        for (auto column = min_pos.column(); column <= max_pos.column(); column++) {
	                        const PVector pos(column, row);
                            if (canAct(pos)) {
                                if (item(row, column)->backgroundColor() != PRIMARY_COLOR
                                        || item(row, column)->text() != EMPTY_SYMBOL) {
                                    record(pos, PRIMARY_COLOR, EMPTY_SYMBOL);
                                    GameController::setReset(true);
                                    GameController::setModified(true);
                                }
                                item(row, column)->setBackgroundColor(PRIMARY_COLOR);
                                item(row, column)->setText(EMPTY_SYMBOL);
                                nonogram_preview->updatePreview(pos, NonogramPreview::PRV_NOFILL);
                                checkCrossComplete(pos);
                            }
                        }
                    }
                    break;
                case GameWindow::TOOL_CROSS:
                    for (auto row = min_pos.row(); row <= max_pos.row(); row++) {
                        for (auto column = min_pos.column(); column <= max_pos.column(); column++) {
	                        const PVector pos(column, row);
                            if (canAct(pos)) {
                                if (item(row, column)->text() != CROSS_SYMBOL) {
                                    record(pos, PRIMARY_COLOR, CROSS_SYMBOL);
                                    GameController::setReset(true);
                                    GameController::setModified(true);
                                }
                                item(row, column)->setBackgroundColor(PRIMARY_COLOR);
                                item(row, column)->setText(CROSS_SYMBOL);
                                nonogram_preview->updatePreview(pos, NonogramPreview::PRV_NOFILL);
                                checkCrossComplete(pos);
                            }
                        }
                    }
                    break;
                default: ;
            }
        }
        checkGameComplete();
    }
}

/**
 * \brief 记录一步操作
 * \param pos 位置
 * \param new_background_color 新的背景色
 * \param new_text 新的文字
 */
void Nonogram::record(PVector pos, const QColor& new_background_color, const QString& new_text) {
    GameMove move;
    move.pos = pos;
    move.new_background_color = new_background_color;
    move.new_text = new_text;
    move.old_background_color = item(pos.row(), pos.column())->backgroundColor();
    move.old_text = item(pos.row(), pos.column())->text();
    undos.append(move);
    GameController::setUndo(true);
    redos.clear();
    GameController::setRedo(false);
}

/**
 * \brief 撤销功能
 */
void Nonogram::undo() {
    auto current_move = undos.last();
    undos.pop_back();
    redos.append(current_move);
    GameController::setRedo(true);

    item(current_move.pos.row(), current_move.pos.column())->setBackgroundColor(current_move.old_background_color);
    item(current_move.pos.row(), current_move.pos.column())->setText(current_move.old_text);
    bool preview_fill = false;
    if (current_move.old_background_color == DARK_COLOR) {
        preview_fill = NonogramPreview::PRV_FILL;
    } else if (current_move.old_background_color == PRIMARY_COLOR) {
        preview_fill = NonogramPreview::PRV_NOFILL;
    }
    nonogram_preview->updatePreview(current_move.pos, preview_fill);

    eraseLastCrossHighlight();
    if (undos.empty()) {
        GameController::setModified(false);
        GameController::setUndo(false);
    } else {
        crossHighlight(current_move.pos);
        last_pos = current_move.pos;
    }

    checkCrossComplete(current_move.pos);
    checkGameComplete();
}

/**
 * \brief 重做功能
 */
void Nonogram::redo() {
    auto current_move = redos.last();
    redos.pop_back();
    undos.append(current_move);
    GameController::setUndo(true);

    item(current_move.pos.row(), current_move.pos.column())->setBackgroundColor(current_move.new_background_color);
    item(current_move.pos.row(), current_move.pos.column())->setText(current_move.new_text);
    bool preview_fill = false;
    if (current_move.new_background_color == DARK_COLOR) {
        preview_fill = NonogramPreview::PRV_FILL;
    } else if (current_move.new_background_color == PRIMARY_COLOR) {
        preview_fill = NonogramPreview::PRV_NOFILL;
    }
    nonogram_preview->updatePreview(current_move.pos, preview_fill);

    eraseLastCrossHighlight();
    crossHighlight(current_move.pos);
    last_pos = current_move.pos;
    if (redos.empty()) {
        GameController::setRedo(false);
    }

    checkCrossComplete(current_move.pos);
}

/**
 * \brief 重置游戏
 */
void Nonogram::resetGame() {
    InfoWindow info(tr("是否重置游戏？您将丢失该网格画的全部进度！"), 2, this);
    const auto response = info.exec();
    if (response == QDialog::Accepted) {
        eraseLastCrossHighlight();

        for (auto row = hint.top.size + 1; row < rowCount(); row++) {
            for (auto column = hint.left.size + 1; column < columnCount(); column++) {
                if (item(row, column)->backgroundColor() != SECONDARY_SEPARATOR_COLOR) {
                    item(row, column)->setBackgroundColor(PRIMARY_COLOR);
                    item(row, column)->setText(EMPTY_SYMBOL);
                    nonogram_preview->updatePreview(PVector(column, row), NonogramPreview::PRV_NOFILL);
                }
            }
        }
        for (auto column = hint.left.size + 1; column < columnCount(); column++) {
	        const PVector anchor(column, hint.top.size + 1);
            if (canAct(anchor)) {
                checkCrossComplete(anchor);
            }
        }
        for (auto row = hint.top.size + 1; row < rowCount(); row++) {
	        const PVector anchor(hint.left.size + 1, row);
            if (canAct(anchor)) {
                checkCrossComplete(anchor);
            }
        }

        undos.clear();
        redos.clear();
        current_pos = PVector();
        last_pos = PVector(hint.left.size, hint.top.size) + 1;
        remove(SAVE_NAME);
        GameController::setModified(false);
        GameController::setReset(false);
        GameController::setUndo(false);
        GameController::setRedo(false);
    }
}

/**
 * \brief 检查一行一列是否已经完成
 * \param pos 位置
 */
void Nonogram::checkCrossComplete(PVector pos) {
    const auto row = readRow(pos.row());
    const auto column = readColumn(pos.column());

    if (row == hint_row_vector[pos.row() - (hint.top.size + 1)]) {
        colorHintRow(pos.row(), HINT_SOLVED_COLOR);
    } else if (current_pos == pos) {
        colorHintRow(pos.row(), ACCENT_COLOR);
    } else {
        colorHintRow(pos.row(), HINT_UNSOLVED_COLOR);
    }

    if (column == hint_column_vector[pos.column() - (hint.left.size + 1)]) {
        colorHintColumn(pos.column(), HINT_SOLVED_COLOR);
    } else if (current_pos == pos) {
        colorHintColumn(pos.column(), ACCENT_COLOR);
    } else {
        colorHintColumn(pos.column(), HINT_UNSOLVED_COLOR);
    }
}

/**
 * \brief 检查游戏是否完成
 */
void Nonogram::checkGameComplete() {
    complete = true;
    for (auto column = hint.left.size + 1; column < columnCount(); column++) {
        const auto color = item(hint.top.size - 1, column)->backgroundColor();
        if (color != HINT_SOLVED_COLOR && color != SECONDARY_SEPARATOR_COLOR && color != PRIMARY_COLOR) {
            complete = false;
        }
    }
    for (auto row = hint.top.size + 1; row < rowCount(); row++) {
        const auto color = item(row, hint.left.size - 1)->backgroundColor();
        if (color != HINT_SOLVED_COLOR && color != SECONDARY_SEPARATOR_COLOR && color != PRIMARY_COLOR) {
            complete = false;
        }
    }

    if (complete) {
        viewport()->installEventFilter(GameController::game_window);
        disconnect(this, &QAbstractItemView::entered, this, &Nonogram::getBlock);
        setShowGrid(false);
        setMouseTracking(false);
        viewport()->setCursor(Qt::ArrowCursor);
        eraseLastCrossHighlight();
        if (game_grid.column() * BLOCK_SIZE + 2 < minimumWidth()) {
            setMinimumWidth(game_grid.column() * BLOCK_SIZE + 2);
        }
        if (game_grid.row() * BLOCK_SIZE + 2 < minimumHeight()) {
            setMinimumHeight(game_grid.row() * BLOCK_SIZE + 2);
        }
        for (auto row = 0; row < rowCount(); row++) {
            for (auto column = 0; column < columnCount(); column++) {
                item(row, column)->setText(EMPTY_SYMBOL);
            }
        }
        for (auto row = 0; row < hint.top.size; row++) {
            setRowHeight(row, 0);
        }
        for (auto column = 0; column < hint.left.size; column++) {
            setColumnWidth(column, 0);
        }
        for (auto row = hint.top.size; row < rowCount(); row += 6) {
            setRowHeight(row, 0);
        }
        for (auto column = hint.left.size; column < columnCount(); column += 6) {
            setColumnWidth(column, 0);
        }

        undos.clear();
        redos.clear();
        label_preview->hide();
        GameController::game_window->showComplete(title);
    }
}

/**
 * \brief 保存游戏
 */
void Nonogram::save() const {
    std::ofstream fout(SAVE_NAME);
    fout << index << std::endl;

    for (auto row = hint.top.size + 1; row < rowCount(); row++) {
        for (auto column = hint.left.size + 1; column < columnCount(); column++) {
            const auto color = item(row, column)->backgroundColor();
            const auto text = item(row, column)->text();
            if ((color == PRIMARY_COLOR || color == CROSS_HIGHLIGHT_COLOR) && text == EMPTY_SYMBOL) {
                fout << 0 << " ";
            } else if (color == DARK_COLOR) {
                fout << 1 << " ";
            } else if ((color == PRIMARY_COLOR || color == CROSS_HIGHLIGHT_COLOR) && text == CROSS_SYMBOL) {
                fout << 2 << " ";
            } else if (color == SECONDARY_SEPARATOR_COLOR) {
                fout << -1 << " ";
            }
        }
        fout << std::endl;
    }

    fout.close();
}

/**
 * \brief 加载游戏
 * \param fin 输入流
 */
void Nonogram::load(std::ifstream& fin) {
    for (auto row = hint.top.size + 1; row < rowCount(); row++) {
        for (auto column = hint.left.size + 1; column < columnCount(); column++) {
            int state;
            fin >> state;
            switch (state) {
                case 1:
                    item(row, column)->setBackgroundColor(DARK_COLOR);
                    nonogram_preview->updatePreview(PVector(column, row), NonogramPreview::PRV_FILL);
                    checkCrossComplete(PVector(column, row));
                    break;
                case 2:
                    item(row, column)->setText(CROSS_SYMBOL);
                default: ;
            }
        }
    }
}

/**
 * \brief 判断游戏是否结束
 * \return 
 */
bool Nonogram::isComplete() const {
    return complete;
}

/**
 * \brief 获取表格大小
 * \return 
 */
PVector Nonogram::getTableSize() const {
    return table_size;
}

/**
 * \brief 为一行的提示上色
 * \param row 行标
 * \param color 颜色
 */
void Nonogram::colorHintRow(const int row, const QColor& color) {
    for (auto column = 0; column < hint.left.size; column++) {
        if (hint.left.data[column][row - (hint.top.size + 1)] != 0) {
            item(row, column)->setBackgroundColor(color);
        }
    }
}

/**
 * \brief 为一列的提示上色
 * \param column 列标
 * \param color 颜色
 */
void Nonogram::colorHintColumn(const int column, const QColor& color) {
    for (auto row = 0; row < hint.top.size; row++) {
        if (hint.top.data[row][column - (hint.left.size + 1)] != 0) {
            item(row, column)->setBackgroundColor(color);
        }
    }
}

/**
 * \brief 读取一行游戏填充情况
 * \param row 行标
 * \return 
 */
QVector<int> Nonogram::readRow(const int row) const {
    QVector<int> data;
    auto tmp = 0;
    for (auto column = hint.left.size + 1; column < columnCount(); column++) {
        if (item(row, column)->backgroundColor() == DARK_COLOR) {
            tmp++;
        } else if (item(row, column)->backgroundColor() != DARK_COLOR
                   && item(row, column)->backgroundColor() != SECONDARY_SEPARATOR_COLOR
                   && tmp != 0) {
            data.append(tmp);
            tmp = 0;
        }
    }
    if (tmp != 0) {
        data.append(tmp);
    }
    return data;
}

/**
 * \brief 读取一列游戏填充情况
 * \param column 列标
 * \return 
 */
QVector<int> Nonogram::readColumn(const int column) const {
    QVector<int> data;
    auto tmp = 0;
    for (auto row = hint.top.size + 1; row < rowCount(); row++) {
        if (item(row, column)->backgroundColor() == DARK_COLOR) {
            tmp++;
        } else if (item(row, column)->backgroundColor() != DARK_COLOR
                   && item(row, column)->backgroundColor() != SECONDARY_SEPARATOR_COLOR
                   && tmp != 0) {
            data.append(tmp);
            tmp = 0;
        }
    }
    if (tmp != 0) {
        data.append(tmp);
    }
    return data;
}

/**
 * \brief 读取一行提示
 * \param row 行标
 * \return 
 */
QVector<int> Nonogram::readHintRow(const int row) {
    QVector<int> data;
    for (auto column = 0; column < hint.left.size; column++) {
        if (hint.left.data[column][row] != 0) {
            data.append(hint.left.data[column][row]);
        }
    }
    return data;
}

/**
 * \brief 读取一列提示
 * \param column 列标
 * \return 
 */
QVector<int> Nonogram::readHintColumn(const int column) {
    QVector<int> data;
    for (auto row = 0; row < hint.top.size; row++) {
        if (hint.top.data[row][column] != 0) {
            data.append(hint.top.data[row][column]);
        }
    }
    return data;
}
