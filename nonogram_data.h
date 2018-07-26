#ifndef NONOGRAM_DATA_H
#define NONOGRAM_DATA_H

#include <QString>
#include <QPoint>

struct Hint {
    int horizontal[10][50];
    int vertical[10][50];
};

struct NonogramData {
	int index;
    QString title;
    QPoint game_grid;
    QPoint hint_grid;
    Hint hint;
};

extern NonogramData nonogram_data[5];

#endif // NONOGRAM_DATA_H
