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

inline const PVector operator+(const PVector& p1, const PVector& p2) {
    return PVector(p1.xp + p2.xp, p1.yp + p2.yp);
}

inline const PVector operator+(const PVector& p, int n) {
    return PVector(p.xp + n, p.yp + n);
}

inline const PVector operator*(const PVector& p, int factor) {
    return PVector(p.xp * factor, p.yp * factor);
}

inline const PVector operator*(int factor, const PVector& p) {
    return PVector(p.xp * factor, p.yp * factor);
}

inline const PVector operator/(const PVector& p, int divisor) {
    return PVector(p.xp / divisor, p.yp / divisor);
}

template<class T>
void PVector::singleJudge(int n, T comp) {
    xp = comp(xp, n) ? n : xp;
    yp = comp(yp, n) ? n : yp;
}

template<class T>
PVector PVector::singleJudge(const PVector& p, int n, T comp) {
    return PVector(comp(p.xp, n) ? n : p.xp, comp(p.yp, n) ? n : p.yp);
}
