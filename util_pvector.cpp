#include "util_pvector.h"

PVector::PVector() {
    xp = 0;
    yp = 0;
}

PVector::PVector(int x, int y) {
    xp = x;
    yp = y;
}

inline int& PVector::x() {
    return xp;
}

inline int& PVector::y() {
    return yp;
}

inline int& PVector::row() {
    return yp;
}

inline int& PVector::column() {
    return xp;
}

inline int& PVector::width() {
    return xp;
}

inline int& PVector::height() {
    return yp;
}


