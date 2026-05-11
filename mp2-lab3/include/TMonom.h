#ifndef _TMONOM_H_
#define _TMONOM_H_

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class TMonom {
private:
    double digit;
    uint16_t degree;

public:
    TMonom() : digit(0), degree(0) {}
    TMonom(double d, uint16_t deg) : digit(d), degree(deg) {}

    double Ratio() const { return digit; }
    uint16_t Degree() const { return degree; }

    bool operator<(const TMonom& m) const { return degree < m.degree; }
    bool operator>(const TMonom& m) const { return degree > m.degree; }
    bool operator==(const TMonom& m) const { return degree == m.degree && digit == m.digit; }
    bool operator!=(const TMonom& m) const { return !(*this == m); }

    TMonom operator*(const TMonom& m) const {
        if (degree + m.degree > 999)
            throw invalid_argument("Degree overflow: " + to_string(degree + m.degree));
        return TMonom(digit * m.digit, degree + m.degree);
    }

    friend ostream& operator<<(ostream& os, const TMonom& t) {
        os << t.digit << "x" << t.degree / 100 << 'y' << (t.degree % 100) / 10 << 'z' << t.degree % 10;
        return os;
    }
};

#endif