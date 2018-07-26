#ifndef UTIL_PVECTOR_H
#define UTIL_PVECTOR_H

#include <functional>

class PVector {
    int xp;
    int yp;

public:
    PVector();
    PVector(int x, int y);

    inline int& x();
    inline int& y();

    inline int& row();
    inline int& column();

    inline int& width();
    inline int& height();

    friend inline const PVector operator+(const PVector& p1, const PVector& p2);
    friend inline const PVector operator+(const PVector& p, int n);
    friend inline const PVector operator*(const PVector& p, int factor);
    friend inline const PVector operator*(int factor, const PVector& p);
    friend inline const PVector operator/(const PVector& p, int divisor);

    template<class T>
    void singleJudge(int n, T comp);

    template<class T>
    static PVector singleJudge(const PVector& p, int n, T comp);
//    inline PVector& PVector::operator-=(const PVector& p);
//    inline PVector& PVector::operator*=(int factor);
//    inline PVector& PVector::operator/=(int divisor);

//    inline bool operator==(const PVector& p1, const PVector& p2);
//    inline bool operator!=(const PVector& p1, const PVector& p2);
//
//    inline const PVector operator-(const PVector& p1, const PVector& p2);
//
//    inline const PVector operator-(const PVector& p, int n);
//    inline const PVector operator-(const PVector& p, int factor);
//
//
//    inline const PVector operator+(const PVector& p);
//    inline const PVector operator-(const PVector& p);
//
};

#endif // UTIL_PVECTOR_H
