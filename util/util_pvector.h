#ifndef UTIL_PVECTOR_H
#define UTIL_PVECTOR_H

class PVector {
    int xp;
    int yp;

public:
    PVector() {
        xp = 0;
        yp = 0;
    }

    PVector(const int x, const int y) {
        xp = x;
        yp = y;
    }

    inline int& x();
    inline int& y();

    inline int& row();
    inline int& column();

    inline int& width();
    inline int& height();

    friend inline PVector operator+(const PVector& p1, const PVector& p2);
    friend inline PVector operator+(const PVector& p, int n);
    friend inline PVector operator*(const PVector& p, int factor);
    friend inline PVector operator*(int factor, const PVector& p);
    friend inline PVector operator/(const PVector& p, int divisor);

    friend inline bool operator==(const PVector& p1, const PVector& p2);

    template<class T>
    void sepCompare(int n, T comp);

    template<class T>
    void sepCompare(const PVector& p, T comp);

    template<class T>
    static PVector sepCompare(const PVector& p, int n, T comp);

    template<class T>
    static PVector sepCompare(const PVector& p1, const PVector& p2, T comp);
};

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

inline PVector operator+(const PVector& p1, const PVector& p2) {
	return { p1.xp + p2.xp, p1.yp + p2.yp };
}

inline PVector operator+(const PVector& p, const int n) {
	return { p.xp + n, p.yp + n };
}

inline PVector operator*(const PVector& p, const int factor) {
	return { p.xp * factor, p.yp * factor };
}

inline PVector operator*(const int factor, const PVector& p) {
	return { p.xp * factor, p.yp * factor };
}

inline PVector operator/(const PVector& p, const int divisor) {
	return { p.xp / divisor, p.yp / divisor };
}

inline bool operator==(const PVector& p1, const PVector& p2) {
    return p1.xp == p2.xp && p1.yp == p2.yp;
}

template<class T>
void PVector::sepCompare(int n, T comp) {
    xp = comp(xp, n) ? xp : n;
    yp = comp(yp, n) ? yp : n;
}

template<class T>
void PVector::sepCompare(const PVector& p, T comp) {
    xp = comp(xp, p.xp) ? xp : p.xp;
    yp = comp(yp, p.yp) ? yp : p.yp;
}

template<class T>
PVector PVector::sepCompare(const PVector& p, int n, T comp) {
    return PVector(comp(p.xp, n) ? p.xp : n, comp(p.yp, n) ? p.yp : n);
}

template<class T>
PVector PVector::sepCompare(const PVector& p1, const PVector& p2, T comp) {
    return PVector(comp(p1.xp, p2.xp) ? p1.xp : p2.xp, comp(p1.yp, p2.yp) ? p1.yp : p2.yp);
}

#endif // UTIL_PVECTOR_H
