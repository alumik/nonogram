#include "define.h"
#include "nonogramdata.h"
#include "nonogram.h"

extern NonogramData nonogramData[4];

QVector<int> readRow(int r, Nonogram* nonogram) {
	QVector<int> data;
	int tmp = 0;
	for (int c = nonogram->hintColumn + 1; c < nonogram->columnCount(); c++) {
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

QVector<int> readColumn(int c, Nonogram* nonogram) {
	QVector<int> data;
	int tmp = 0;
	for (int r = nonogram->hintRow + 1; r < nonogram->rowCount(); r++) {
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

QVector<int> readHintRow(int r, Nonogram* nonogram) {
	QVector<int> data;
	for (int c = 0; c < nonogramData[nonogram->index].hintColumn; c++) {
		if (nonogramData[nonogram->index].hintV[c][r] != 0) {
			data.append(nonogramData[nonogram->index].hintV[c][r]);
		}
	}
	return data;
}

QVector<int> readHintColumn(int c, Nonogram* nonogram) {
	QVector<int> data;
	for (int r = 0; r < nonogramData[nonogram->index].hintRow; r++) {
		if (nonogramData[nonogram->index].hintH[r][c] != 0) {
			data.append(nonogramData[nonogram->index].hintH[r][c]);
		}
	}
	return data;
}
