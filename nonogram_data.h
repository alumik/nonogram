#ifndef NONOGRAM_DATA_H
#define NONOGRAM_DATA_H

#include <QString>

struct NonogramData {
	int index;
	QString name;
	int game_row;
	int game_column;
	int hint_row;
	int hint_column;
	int hint_h[10][50];
	int hint_v[10][50];
};

extern NonogramData global_nonogram_data[5];

#endif // NONOGRAM_DATA_H
