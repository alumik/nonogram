#ifndef UTIL_PVECTOR_H
#define UTIL_PVECTOR_H

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
//    inline PVector& PVector::operator-=(const PVector& p);
//    inline PVector& PVector::operator*=(int factor);
//    inline PVector& PVector::operator/=(int divisor);

//    inline bool operator==(const PVector& p1, const PVector& p2);
//    inline bool operator!=(const PVector& p1, const PVector& p2);
//    inline const PVector operator+(const PVector& p1, const PVector& p2);
//    inline const PVector operator-(const PVector& p1, const PVector& p2);
//    inline const PVector operator+(const PVector& p, int n);
//    inline const PVector operator-(const PVector& p, int n);
//    inline const PVector operator-(const PVector& p, int factor);
//    inline const PVector operator*(const PVector& p, int factor);
//    inline const PVector operator*(int factor, const PVector& p);
//    inline const PVector operator+(const PVector& p);
//    inline const PVector operator-(const PVector& p);
//    inline const PVector operator/(const PVector& p, int divisor);
};

#endif // UTIL_PVECTOR_H
