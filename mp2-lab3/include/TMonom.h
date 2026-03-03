#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#ifndef _TMONOM_H_
#define _TMONOM_H_

class TMonom {
private:
  double digit;
  uint16_t degree;

public:
  TMonom() : digit(0), degree(0){};
  TMonom(double d, uint16_t deg) : digit(d), degree(deg) {}
  inline bool operator>(const TMonom &m) {
    if (degree > m.degree) {
      return true;
    } else {
      return false;
    }
  }
  inline bool operator<(const TMonom &m) {
    if (degree < m.degree) {
      return true;
    } else {
      return false;
    }
  }
  inline bool operator==(const TMonom &m) {
    if (degree == m.degree) {
      return true;
    } else {
      return false;
    }
  }

  TMonom operator*(const TMonom &m) {
    if (degree + m.degree > 999) {
      throw invalid_argument("Incorrect degree of result poly:" +
                             to_string(degree + m.degree));
    }
    uint16_t tmp = degree + m.degree;
    double res = digit * m.digit;
    TMonom t = TMonom(res, tmp);
    return t;
  }

  bool operator!=(const TMonom &m) {
    return (digit != m.Ratio() || degree != m.Degree());
  }
  double Ratio() const { return digit; }
  uint16_t Degree() const { return degree; }

  friend ostream &operator<<(ostream &os, TMonom t) {

    os << t.digit << "x" << t.degree / 100 << 'y' << t.degree % 100 / 10 << 'z'
       << t.degree % 10;

    return os;
  }
};

#endif