#ifndef NONOGRAM_DATA_H
#define NONOGRAM_DATA_H

#include "util_pvector.h"

#include <QString>

struct HintSide {
    int size;
    int data[10][50];
};

struct Hint {
    HintSide top;
    HintSide left;
};

struct NonogramData {
    int index;
    QString title;
    PVector game_grid;
    Hint hint;
};

extern NonogramData nonogram_data[5];

#endif // NONOGRAM_DATA_H
