#include "util_generic_define.h"
#include "nonogram_data.h"
#include "nonogram.h"

/**
 * \brief 读取一行数据
 * \param r 
 * \param nonogram 
 * \return 
 */
QVector<int> readRow(const int r, Nonogram* nonogram) {
	QVector<int> data;
	auto tmp = 0;
	for (auto c = nonogram->hint_column + 1; c < nonogram->columnCount(); c++) {
		if (nonogram->item(r, c)->backgroundColor() == DARK_COLOR) {
			tmp++;
		}
		if (nonogram->item(r, c)->backgroundColor() != DARK_COLOR && nonogram->item(r, c)->backgroundColor() != Qt::black) {
			if (tmp != 0) {
				data.append(tmp);
				tmp = 0;
			}
		}
	}
	if (tmp != 0) {
		data.append(tmp);
		tmp = 0;
	}
	return data;
}

/**
 * \brief 读取一列数据
 * \param c 
 * \param nonogram 
 * \return 
 */
QVector<int> readColumn(const int c, Nonogram* nonogram) {
	QVector<int> data;
	auto tmp = 0;
	for (auto r = nonogram->hint_row + 1; r < nonogram->rowCount(); r++) {
		if (nonogram->item(r, c)->backgroundColor() == DARK_COLOR) {
			tmp++;
		}
		if (nonogram->item(r, c)->backgroundColor() != DARK_COLOR && nonogram->item(r, c)->backgroundColor() != Qt::black) {
			if (tmp != 0) {
				data.append(tmp);
				tmp = 0;
			}
		}
	}
	if (tmp != 0) {
		data.append(tmp);
		tmp = 0;
	}
	return data;
}

/**
 * \brief 读取一行提示
 * \param r 
 * \param nonogram 
 * \return 
 */
QVector<int> readHintRow(const int r, Nonogram* nonogram) {
	QVector<int> data;
	for (auto c = 0; c < global_nonogram_data[nonogram->index].hint_column; c++) {
		if (global_nonogram_data[nonogram->index].hint_v[c][r] != 0) {
			data.append(global_nonogram_data[nonogram->index].hint_v[c][r]);
		}
	}
	return data;
}

/**
 * \brief 读取一列提示
 * \param c 
 * \param nonogram 
 * \return 
 */
QVector<int> readHintColumn(const int c, Nonogram* nonogram) {
	QVector<int> data;
	for (auto r = 0; r < global_nonogram_data[nonogram->index].hint_row; r++) {
		if (global_nonogram_data[nonogram->index].hint_h[r][c] != 0) {
			data.append(global_nonogram_data[nonogram->index].hint_h[r][c]);
		}
	}
	return data;
}
