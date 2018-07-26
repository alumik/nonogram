#include "nonogram.h"
#include "util_generic_define.h"
#include "nonogram_data.h"
#include "window_game.h"
#include "nonogram_preview.h"
#include "util_pixel_font.h"
#include "window_info.h"
#include "controller_game.h"

#include <QHeaderView>
#include <cstdio>
#include <fstream>

extern QVector<int> readRow(int r, Nonogram* nonogram);
extern QVector<int> readColumn(int c, Nonogram* nonogram);
extern QVector<int> readHintRow(int r, Nonogram* nonogram);
extern QVector<int> readHintColumn(int c, Nonogram* nonogram);

/**
 * \brief 游戏网格
 * \param parent 
 */
Nonogram::Nonogram(QWidget* parent) : QTableWidget(parent) {
	// 读取游戏数据
    index = GameController::nonogram_index;
	complete = false;
	game_row = global_nonogram_data[index].game_row;
	game_column = global_nonogram_data[index].game_column;
	hint_row = global_nonogram_data[index].hint_row;
	hint_column = global_nonogram_data[index].hint_column;
	last_r = hint_row + 1;
	last_c = hint_column + 1;
	drag_r = 0;
	drag_c = 0;
	current_r = 0;
	current_c = 0;
	record_r = 0;
	record_c = 0;

	// 计算分割线数量
	auto spliter_row = game_row / 5;
	if (game_row % 5 == 0) {
		spliter_row--;
	}

	auto spliter_column = game_column / 5;
	if (game_column % 5 == 0) {
		spliter_column--;
	}

	// 配置游戏区域大小
	setRowCount(game_row + hint_row + spliter_row + 1);
	setColumnCount(game_column + hint_column + spliter_column + 1);

    table_width = (game_column + hint_column) * BLOCK_SIZE + (spliter_column + 1) * SPLITER_SIZE + 2;
    table_height = (game_row + hint_row) * BLOCK_SIZE + (spliter_row + 1) * SPLITER_SIZE + 2;
    table_width = table_width > 635 ? 635 : table_width;
    table_height = table_height > 635 ? 635 : table_height;
    setMinimumWidth(table_width >= 15 * BLOCK_SIZE ? 15 * BLOCK_SIZE : table_width);
    setMinimumHeight(table_height >= 15 * BLOCK_SIZE ? 15 * BLOCK_SIZE : table_height);

	// 配置其他参数
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

	// 创建预览界面
	preview = new QLabel(this);
	preview->move(1, 1);
	preview->setStyleSheet("QLabel { background-color: rgb(255, 255, 255) }");
	preview->setFixedSize(hint_column * BLOCK_SIZE, hint_row * BLOCK_SIZE);
	preview->setFrameShape(QFrame::Box);
	preview->setLineWidth(2);
	nonogram_preview = new NonogramPreview(game_row, game_column, hint_row, hint_column, spliter_row, spliter_column, preview);

	// 创建拖动区域大小显示标签
	drag_size = new QLabel(this);
	drag_size->setVisible(false);
	drag_size->move(1, 1);
	drag_size->setStyleSheet("QLabel { background-color: rgb(43, 43, 43); color: rgb(204, 204, 204); border: 2px solid black }");
	drag_size->setFont(PixelFont("Microsoft YaHei UI", 10, 50));

	// 初始化表格对象
	for (auto r = 0; r < rowCount(); r++) {
		for(auto c = 0; c < columnCount(); c++) {
			setItem(r, c, new QTableWidgetItem);
			item(r, c)->setBackgroundColor(PRIMARY_COLOR);
			item(r, c)->setTextAlignment(Qt::AlignCenter);
			item(r, c)->setText(QString(""));
			item(r, c)->setFont(PixelFont("宋体", 12, 50));
		}
	}

	// 设置Block和Spliter的行宽及列高
	for (auto r = 0; r < rowCount(); r++) {
		setRowHeight(r, BLOCK_SIZE);
	}
	for (auto c = 0; c < columnCount(); c++) {
		setColumnWidth(c, BLOCK_SIZE);
	}
	for (auto r = hint_row; r < rowCount(); r += 6) {
		setRowHeight(r, SPLITER_SIZE);
	}
	for (auto c = hint_column; c < columnCount(); c += 6) {
		setColumnWidth(c, SPLITER_SIZE);
	}

	// 设置主Spliter颜色
	for (auto r = 0; r < rowCount(); r++) {
		item(r, hint_column)->setBackgroundColor(MAIN_SPLITER_COLOR);
	}
	for (auto c = 0; c < columnCount(); c++) {
		item(hint_row, c)->setBackgroundColor(MAIN_SPLITER_COLOR);
	}

	// 设置副Spliter颜色
	for (auto r = hint_row + 6; r < rowCount(); r += 6) {
		for (auto c = 0; c < columnCount(); c++) {
			item(r, c)->setBackgroundColor(SECONDARY_SPLITER_COLOR);
		}
	}
	for (auto c = hint_column + 6; c < columnCount(); c += 6) {
		for (auto r = 0; r < rowCount(); r++) {
			item(r, c)->setBackgroundColor(SECONDARY_SPLITER_COLOR);
		}
	}

	// 配置Hint
	for (auto r = 0; r < hint_row; r++) {
		for (auto c = hint_column + 1; c < columnCount(); c++) {
			const auto hint = global_nonogram_data[index].hint_h[r][c - hint_column - 1];
			if (hint != 0 && hint != -1) {
				item(r, c)->setTextColor(HINT_TEXT_COLOR);
				item(r, c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
				item(r, c)->setText(QString::number(hint));
				item(r, c)->setFont(PixelFont("Microsoft YaHei UI", 12, 50));
			}
		}
	}
	for (auto c = 0; c < hint_column; c++) {
		for (auto r = hint_row + 1; r < rowCount(); r++) {
			const auto hint = global_nonogram_data[index].hint_v[c][r - hint_row - 1];
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

/**
 * \brief 判断能否操作
 * \param r 
 * \param c 
 * \return 
 */
bool Nonogram::canAct(const int r, const int c) const {
	auto can_act = true;
	for (auto tmp_r = hint_row; tmp_r < rowCount(); tmp_r += 6) {
		if (r == tmp_r) {
			can_act = false;
		}
	}
	for (auto tmp_c = hint_column; tmp_c < columnCount(); tmp_c += 6) {
		if (c == tmp_c) {
			can_act = false;
		}
	}
	if (r <= hint_row || c <= hint_column) {
		can_act = false;
	}
	return can_act;
}

/**
 * \brief 十字高亮
 * \param r 
 * \param c 
 * \return 
 */
bool Nonogram::crossHighlight(const int r, const int c) const {
	if (!canAct(r, c)) {
		return false;
	}
	for (auto tmp_r = 0; tmp_r < hint_row; tmp_r++) {
		const auto hint = global_nonogram_data[index].hint_h[tmp_r][c - hint_column - 1];
		if (hint != 0 && hint != -1) {
			if (item(tmp_r, c)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(tmp_r, c)->setBackgroundColor(ACCENT_COLOR);
			}
		} else if (hint == 0) {
			item(tmp_r, c)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	for (auto tmp_c = 0; tmp_c < hint_column; tmp_c++) {
		const auto hint = global_nonogram_data[index].hint_v[tmp_c][r - hint_row - 1];
		if (hint != 0 && hint != -1) {
			if (item(r, tmp_c)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(r, tmp_c)->setBackgroundColor(ACCENT_COLOR);
			}
		} else if (hint == 0) {
			item(r, tmp_c)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	for (auto tmp_row = hint_row + 1; tmp_row < rowCount(); tmp_row++) {
		if (item(tmp_row, c)->backgroundColor() == PRIMARY_COLOR && tmp_row != r ) {
			item(tmp_row, c)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	for (auto tmp_column = hint_column + 1; tmp_column < columnCount(); tmp_column++) {
		if (item(r, tmp_column)->backgroundColor() == PRIMARY_COLOR && tmp_column != c) {
			item(r, tmp_column)->setBackgroundColor(CROSS_HIGHLIGHT_COLOR);
		}
	}
	return true;
}

/**
 * \brief 清除十字高亮
 */
void Nonogram::eraseCrossHighlight() const {
	for (auto r = 0; r < hint_row; r++) {
		const auto hint = global_nonogram_data[index].hint_h[r][last_c - hint_column - 1];
		if (hint != 0 && hint != -1) {
			if (item(r, last_c)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(r, last_c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
			}
		} else if (hint == 0) {
			item(r, last_c)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
	for (auto c = 0; c < hint_column; c++) {
		const auto hint = global_nonogram_data[index].hint_v[c][last_r - hint_row - 1];
		if (hint != 0 && hint != -1) {
			if (item(last_r, c)->backgroundColor() != HINT_SOLVED_COLOR) {
				item(last_r, c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
			}
		} else if (hint == 0) {
			item(last_r, c)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
	for (auto r = hint_row + 1; r < rowCount(); r++) {
		if (item(r, last_c)->backgroundColor() == CROSS_HIGHLIGHT_COLOR) {
			item(r, last_c)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
	for (auto c = hint_column + 1; c < columnCount(); c++) {
		if (item(last_r, c)->backgroundColor() == CROSS_HIGHLIGHT_COLOR) {
			item(last_r, c)->setBackgroundColor(PRIMARY_COLOR);
		}
	}
}

/**
 * \brief 区域高亮
 */
void Nonogram::areaHighlight() {
	const auto max_r = current_r >= record_r ? current_r : record_r;
	auto min_r = current_r < record_r ? current_r : record_r;
	const auto max_c = current_c >= record_c ? current_c : record_c;
	auto min_c = current_c < record_c ? current_c : record_c;
	min_r = min_r < hint_row + 1 ? hint_row + 1 : min_r;
	min_c = min_c < hint_column  + 1 ? hint_column + 1 : min_c;
	for (auto r = min_r; r <= max_r; r++) {
		if (crossHighlight(r, min_c)) {
			drag_r++;
		}
	}
	for (auto c = min_c; c <= max_c; c++) {
		if (crossHighlight(min_r, c)) {
			drag_c++;
		}
	}
	for (auto r = min_r; r <= max_r; r++) {
		for (auto c = min_c; c <= max_c; c++) {
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

/**
 * \brief 清除区域高亮
 */
void Nonogram::eraseAreaHighlight() {
	const auto last_max_r = last_r >= record_r ? last_r : record_r;
	auto last_min_r = last_r < record_r ? last_r : record_r;
	const auto last_max_c = last_c >= record_c ? last_c : record_c;
	auto last_min_c = last_c < record_c ? last_c : record_c;
	last_min_r = last_min_r < hint_row + 1 ? hint_row + 1 : last_min_r;
	last_min_c = last_min_c < hint_column + 1 ? hint_column + 1 : last_min_c;
	for (auto r = last_min_r; r <= last_max_r; r++) {
		for (auto c = last_min_c; c <= last_max_c; c++) {
			if (item(r, c)->backgroundColor() == AREA_HIGHLIGHT_COLOR) {
				item(r, c)->setBackgroundColor(PRIMARY_COLOR);
			} else if (item(r, c)->backgroundColor() == AREA_HIGHLIGHT_DARK_COLOR) {
				item(r, c)->setBackgroundColor(DARK_COLOR);
			}
		}
	}
	for (auto r = last_min_r; r <= last_max_r; r++) {
		last_r = r;
		eraseCrossHighlight();
	}
	for (auto c = last_min_c; c <= last_max_c; c++) {
		last_c = c;
		eraseCrossHighlight();
	}
}

/**
 * \brief 获取方块
 * \param index 
 */
void Nonogram::getBlock(const QModelIndex& index) {
	// 记录鼠标位置
	current_r = index.row();
	current_c = index.column();
	if (canAct(current_r, current_c)) {
		if (!mouse_pressed) {
			// 跟随鼠标十字高亮
			eraseCrossHighlight();
			// ReSharper disable once CppExpressionWithoutSideEffects
			crossHighlight(current_r, current_c);
		} else if (canAct(record_r, record_c)) {
			// 跟随鼠标及时调整选中区域高亮
			eraseAreaHighlight();
			areaHighlight();

			// 显示拖动区域大小
			drag_size->setText(QString("%1x%2").arg(drag_c).arg(drag_r));
			drag_c = 0;
			drag_r = 0;
			drag_size->adjustSize();
			drag_size->setVisible(true);
		}
		last_r = current_r;
		last_c = current_c;
	}
}

/**
 * \brief 鼠标按下事件
 * \param event 
 */
void Nonogram::mousePressEvent(QMouseEvent *event) {
	QTableWidget::mousePressEvent(event);
	if (event->button() == Qt::LeftButton) {
		mouse_pressed = true;
		record_r = current_r;
		record_c = current_c;
	}
}

/**
 * \brief 鼠标松开事件
 * \param event 
 */
void Nonogram::mouseReleaseEvent(QMouseEvent *event) {
	QTableWidget::mouseReleaseEvent(event);
	if (event->button() == Qt::LeftButton) {
		mouse_pressed = false;
		drag_size->setVisible(false);
		const auto max_r = current_r >= record_r ? current_r : record_r;
		auto min_r = current_r < record_r ? current_r : record_r;
		const auto max_c = current_c >= record_c ? current_c : record_c;
		auto min_c = current_c < record_c ? current_c : record_c;
		min_r = min_r < hint_row + 1 ? hint_row + 1 : min_r;
		min_c = min_c < hint_column  + 1 ? hint_column + 1 : min_c;
		eraseAreaHighlight();
		if (canAct(current_r, current_c) && canAct(record_r, record_c)) {
            switch (GameController::game_window->tool_type) {
				case 0:
					for (auto r = min_r; r <= max_r; r++) {
						for (auto c = min_c; c <= max_c; c++) {
							if (canAct(r, c)) {
								if (item(r, c)->backgroundColor() != DARK_COLOR) {
									record(r, c, DARK_COLOR, QString(""));
                                    GameController::game_window->btn_reset->setDisabled(false);
                                    GameController::game_window->setWindowModified(true);
								}
								item(r, c)->setBackgroundColor(DARK_COLOR);
								item(r, c)->setText(QString(""));
								nonogram_preview->updatePreview(r, c, Qt::black);
								checkLineComplete(r, c);
							}
						}
					}
					break;
				case 1:
					for (auto r = min_r; r <= max_r; r++) {
						for (auto c = min_c; c <= max_c; c++) {
							if (canAct(r, c)) {
								if (item(r, c)->backgroundColor() != PRIMARY_COLOR || item(r, c)->text() != QString("")) {
									record(r, c, PRIMARY_COLOR, QString(""));
                                    GameController::game_window->btn_reset->setDisabled(false);
                                    GameController::game_window->setWindowModified(true);
								}
								item(r, c)->setBackgroundColor(PRIMARY_COLOR);
								item(r, c)->setText(QString(""));
								nonogram_preview->updatePreview(r, c, Qt::white);
								checkLineComplete(r, c);
							}
						}
					}
					break;
				case 2:
					for (auto r = min_r; r <= max_r; r++) {
						for (auto c = min_c; c <= max_c; c++) {
							if (canAct(r, c)) {
								if (item(r, c)->text() != QString("╳")) {
									record(r, c, PRIMARY_COLOR, QString("╳"));
                                    GameController::game_window->btn_reset->setDisabled(false);
                                    GameController::game_window->setWindowModified(true);
								}
								item(r, c)->setBackgroundColor(PRIMARY_COLOR);
								item(r, c)->setText(QString("╳"));
								nonogram_preview->updatePreview(r, c, Qt::white);
								checkLineComplete(r, c);
							}
						}
					}
					break;
	            default: ;
            }
			// ReSharper disable once CppExpressionWithoutSideEffects
			crossHighlight(current_r, current_c);
			last_r = current_r;
			last_c = current_c;
		}
		checkGameComplete();
	}
}

/**
 * \brief 记录操作
 * \param r 
 * \param c 
 * \param new_background_color 
 * \param new_text 
 */
void Nonogram::record(const int r, const int c, const QColor& new_background_color, const QString& new_text) {
	GameMove move;
	move.row = r;
	move.column = c;
	move.new_background_color = new_background_color;
	move.new_text = new_text;
	move.old_background_color = item(r, c)->backgroundColor();
	move.old_text = item(r, c)->text();
	undos.append(move);
    GameController::game_window->btn_undo->setDisabled(false);
	if (redos.length() != 0) {
		redos.clear();
        GameController::game_window->btn_redo->setDisabled(true);
	}
}

/**
 * \brief 撤销功能
 */
void Nonogram::undo() {
	const auto current_move = undos[undos.length() - 1];
	item(current_move.row, current_move.column)->setBackgroundColor(current_move.old_background_color);
	item(current_move.row, current_move.column)->setText(current_move.old_text);
	QColor preview_color;
	if (current_move.old_background_color == DARK_COLOR) {
		preview_color = Qt::black;
	}
	if (current_move.old_background_color == PRIMARY_COLOR) {
		preview_color = Qt::white;
	}
	nonogram_preview->updatePreview(current_move.row, current_move.column, preview_color);
	checkLineComplete(current_move.row, current_move.column);
	eraseCrossHighlight();
	if (undos.length() == 1) {
        GameController::game_window->setWindowModified(false);
        GameController::game_window->btn_undo->setDisabled(true);
	} else {
		crossHighlight(current_move.row, current_move.column);
		last_c = current_move.column;
		last_r = current_move.row;
	}
	redos.append(current_move);
    GameController::game_window->btn_redo->setDisabled(false);
	undos.pop_back();
	checkGameComplete();
}

/**
 * \brief 重做功能
 */
void Nonogram::redo() {
	const auto current_move = redos[redos.length() - 1];
	item(current_move.row, current_move.column)->setBackgroundColor(current_move.new_background_color);
	item(current_move.row, current_move.column)->setText(current_move.new_text);
	QColor preview_color;
	if (current_move.new_background_color == DARK_COLOR) {
		preview_color = Qt::black;
	}
	if (current_move.new_background_color == PRIMARY_COLOR) {
		preview_color = Qt::white;
	}
	nonogram_preview->updatePreview(current_move.row, current_move.column, preview_color);
	checkLineComplete(current_move.row, current_move.column);
	eraseCrossHighlight();
	crossHighlight(current_move.row, current_move.column);
	last_c = current_move.column;
	last_r = current_move.row;
	if (redos.length() == 1) {
        GameController::game_window->btn_redo->setDisabled(true);
	}
	undos.append(current_move);
    GameController::game_window->btn_undo->setDisabled(false);
	redos.pop_back();
}

/**
 * \brief 重置游戏功能
 */
void Nonogram::resetGame() {
	InfoWindow info(tr("是否重置游戏？您将丢失该网格画的全部进度！"), 2, this);
	const auto r = info.exec();
	if (r == QDialog::Accepted) {

		// 重置游戏区域
		eraseCrossHighlight();
		for (auto row = hint_row + 1; row < rowCount(); row++) {
			for (auto c = hint_column + 1; c < columnCount(); c++) {
				if (item(row, c)->backgroundColor() != SECONDARY_SPLITER_COLOR) {
					item(row, c)->setBackgroundColor(PRIMARY_COLOR);
					item(row, c)->setText(QString(""));
					nonogram_preview->updatePreview(row, c, Qt::white);
				}
			}
		}

		for (auto row = hint_row + 1; row < rowCount(); row++) {
			if (canAct(row, hint_column + 1)) {
				checkLineComplete(row, hint_column + 1);
			}
		}
		for (auto c = hint_column + 1; c < columnCount(); c++) {
			if (canAct(hint_row + 1, c)) {
				checkLineComplete(hint_row + 1, c);
			}
		}

		undos.clear();
		redos.clear();
		current_r = -1;
		current_c = -1;
		last_r = hint_row + 1;
		last_c = hint_column + 1;
        remove("save.nonogram");
        GameController::game_window->setWindowModified(false);
        GameController::game_window->btn_undo->setDisabled(true);
        GameController::game_window->btn_redo->setDisabled(true);
        GameController::game_window->btn_reset->setDisabled(true);
	}
}

/**
 * \brief 判断单行单列完成
 * \param r 
 * \param c 
 */
void Nonogram::checkLineComplete(const int r, const int c) {
	const auto row = readRow(r, this);
	const auto column = readColumn(c, this);
	const auto h_row = readHintRow(r - hint_row - 1, this);
	const auto h_column = readHintColumn(c - hint_column - 1, this);
	if (row == h_row) {
		for (auto tmp_column = 0; tmp_column < hint_column; tmp_column++) {
			if (global_nonogram_data[index].hint_v[tmp_column][r - hint_row - 1] != 0) {
				item(r, tmp_column)->setBackgroundColor(HINT_SOLVED_COLOR);
			}
		}
	} else {
		if (current_r == r && current_c == c) {
			for (auto tmp_column = 0; tmp_column < hint_column; tmp_column++) {
				if (global_nonogram_data[index].hint_v[tmp_column][r - hint_row - 1] != 0) {
					item(r, tmp_column)->setBackgroundColor(ACCENT_COLOR);
				}
			}
		} else {
			for (auto tmp_column = 0; tmp_column < hint_column; tmp_column++) {
				if (global_nonogram_data[index].hint_v[tmp_column][r - hint_row - 1] != 0) {
					item(r, tmp_column)->setBackgroundColor(HINT_UNSOLVED_COLOR);
				}
			}
		}
	}
	if (column == h_column) {
		for (auto tmp_row = 0; tmp_row < hint_row; tmp_row++) {
			if (global_nonogram_data[index].hint_h[tmp_row][c - hint_column - 1] != 0) {
				item(tmp_row, c)->setBackgroundColor(HINT_SOLVED_COLOR);
			}
		}
	} else {
		if (current_r == r && current_c == c) {
			for (auto tmp_row = 0; tmp_row < hint_row; tmp_row++) {
				if (global_nonogram_data[index].hint_h[tmp_row][c - hint_column - 1] != 0) {
					item(tmp_row, c)->setBackgroundColor(ACCENT_COLOR);
				}
			}
		} else {
			for (auto tmp_row = 0; tmp_row < hint_row; tmp_row++) {
				if (global_nonogram_data[index].hint_h[tmp_row][c - hint_column - 1] != 0) {
					item(tmp_row, c)->setBackgroundColor(HINT_UNSOLVED_COLOR);
				}
			}
		}
	}
}

/**
 * \brief 判断游戏完成
 */
void Nonogram::checkGameComplete() {
	complete = true;
	for (auto c = hint_column + 1; c < columnCount(); c++) {
		const auto tmp = item(hint_row - 1, c)->backgroundColor();
		if (tmp != HINT_SOLVED_COLOR && tmp != SECONDARY_SPLITER_COLOR && tmp != PRIMARY_COLOR) {
			complete = false;
		}
	}
	for (auto r = hint_row + 1; r < rowCount(); r++) {
		const auto tmp = item(r, hint_column - 1)->backgroundColor();
		if (tmp != HINT_SOLVED_COLOR && tmp != SECONDARY_SPLITER_COLOR && tmp != PRIMARY_COLOR) {
			complete = false;
		}
	}	

	if (complete) {
        viewport()->installEventFilter(GameController::game_window);
		disconnect(this, &QAbstractItemView::entered, this, &Nonogram::getBlock);
		setShowGrid(false);
		setMouseTracking(false);
		viewport()->setCursor(Qt::ArrowCursor);
		eraseCrossHighlight();
		if (game_column * BLOCK_SIZE + 2 < minimumWidth()) {
			setMinimumWidth(game_column * BLOCK_SIZE + 2);
		}
		if (game_row * BLOCK_SIZE + 2 < minimumHeight()) {
			setMinimumHeight(game_row * BLOCK_SIZE + 2);
		}
		for (auto r = 0; r < rowCount(); r++) {
			for(auto c = 0; c < columnCount(); c++) {
				item(r, c)->setText(QString(""));
			}
		}

        for (auto r = 0; r < hint_grid.x(); r++) {
			setRowHeight(r, 0);
		}
        for (auto c = 0; c < hint_grid.y(); c++) {
			setColumnWidth(c, 0);
		}
        for (auto r = hint_grid.x(); r < rowCount(); r += 6) {
			setRowHeight(r, 0);
		}
        for (auto c = hint_grid.y(); c < columnCount(); c += 6) {
			setColumnWidth(c, 0);
		}

		undos.clear();
		redos.clear();
        label_preview->hide();
        GameController::game_window->showComplete(nonogram_data[index].title);
	}
}

void Nonogram::save() {
    std::ofstream saver("save.nonogram");
    saver << index << std::endl;
    for (auto r = hint_grid.x() + 1; r < rowCount(); r++) {
        for (auto c = hint_grid.y() + 1; c < columnCount(); c++) {
            const auto c_color = item(r, c)->backgroundColor();
            const auto c_text = item(r, c)->text();
            if ((c_color == PRIMARY_COLOR || c_color == CROSS_HIGHLIGHT_COLOR) && c_text == QString("")) {
                saver << 0 << " ";
            } else if (c_color == DARK_COLOR) {
                saver << 1 << " ";
            } else if ((c_color == PRIMARY_COLOR || c_color == CROSS_HIGHLIGHT_COLOR) && c_text == QString("╳")) {
                saver << 2 << " ";
            } else if (c_color == SECONDARY_SEPARATOR_COLOR) {
                saver << -1 << " ";
            }
        }
        saver << std::endl;
    }
    saver.close();
}

void Nonogram::load(std::ifstream& loader) {
    for (auto row = getHintGrid().x() + 1; row < rowCount(); row++) {
        for (auto column = getHintGrid().y() + 1; column < columnCount(); column++) {
            int state;
            loader >> state;
            switch (state) {
                case 1:
                    item(row, column)->setBackgroundColor(DARK_COLOR);
                    nonogram_preview->updatePreview(row, column, Qt::black);
                    checkLineComplete(PVector(row, column));
                    break;
                case 2:
                    item(row, column)->setText(QString("╳"));
                default: ;
            }
        }
    }
}
