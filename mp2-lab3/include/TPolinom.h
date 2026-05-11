#include "TLists.h"
#include "TMonom.h"
#include <iostream>
#include <cmath>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
using namespace regex_constants;

vector<string> split(const string &str, char delimiter) {
  vector<string> tokens;
  stringstream ss(str);
  string token;
  while (getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

class TPolinom {
private:
  TSinglyList<TMonom> list;

public:
  TPolinom() { list.PushFront(TMonom(0, 0)); }
  TPolinom(double num) { list.PushFront(TMonom(num, 0)); }
  TPolinom(string st) {
    if (st.size() == 0) {
      TPolinom r;
      *this = r;

    } else {
      vector<string> res = split(st, '+');
      regex pattern(R"(^[-]?[0-9.]*x[0-9]y[0-9]z[0-9]$)");
      for (size_t i = 0; i < res.size(); i++) {
        if (!regex_match(res[i], pattern)) {
          throw invalid_argument("Invalid input" + res[i]);
        }
      }
      for (size_t i = 0; i < res.size(); i++) {
        size_t tmp = res[i].find('x');
        string number;
        int itmp = 0;
        while (itmp != tmp) {
          number += res[i][itmp];
          itmp++;
        }
        string number_for_degree;
        number_for_degree += res[i][tmp + 1];
        number_for_degree += res[i][tmp + 3];
        number_for_degree += res[i][tmp + 5];
        list.PushFront(TMonom(stod(number), stoi(number_for_degree)));
      }
      this->sort();
    }
  }

  TPolinom(const TPolinom &p) { list = p.list; }

  void sort() {
    if (!list.GetFirst() || !list.GetFirst()->pNext)
      return;
    bool swapped;
    do {
      swapped = false;
      typename TSinglyList<TMonom>::TNode *current = list.GetFirst();
      while (current->pNext != nullptr) {
        if (current->val < current->pNext->val) {
          TMonom temp = current->val;
          current->val = current->pNext->val;
          current->pNext->val = temp;
          swapped = true;
        }
        current = current->pNext;
      }
    } while (swapped);
  }

  TPolinom operator+(const TPolinom &p) {
    typename TSinglyList<TMonom>::TNode *Node_1 = list.GetFirst();
    typename TSinglyList<TMonom>::TNode *Node_2 = p.list.GetFirst();
    TPolinom res;
    while (Node_1 != nullptr && Node_2 != nullptr) {
      if (Node_1->val == Node_2->val) {
        double newCoeff = Node_1->val.Ratio() + Node_2->val.Ratio();
        if (newCoeff != 0) {
          res.list.PushFront(TMonom(newCoeff, Node_1->val.Degree()));
        }
        Node_1 = Node_1->pNext;
        Node_2 = Node_2->pNext;
      } else if (Node_1->val > Node_2->val) {
        res.list.PushFront(TMonom(Node_1->val.Ratio(), Node_1->val.Degree()));
        Node_1 = Node_1->pNext;
      } else {
        res.list.PushFront(TMonom(Node_2->val.Ratio(), Node_2->val.Degree()));
        Node_2 = Node_2->pNext;
      }
    }
    while (Node_1 != nullptr) {
      res.list.PushFront(TMonom(Node_1->val.Ratio(), Node_1->val.Degree()));
      Node_1 = Node_1->pNext;
    }
    while (Node_2 != nullptr) {
      res.list.PushFront(TMonom(Node_2->val.Ratio(), Node_2->val.Degree()));
      Node_2 = Node_2->pNext;
    }
    // res.sort();
    return res;
  }

  TPolinom operator*(const double value) const {
    TPolinom res = *this;
    typename TSinglyList<TMonom>::TNode *Node_1 = res.list.GetFirst();
    while (Node_1 != nullptr) {
      Node_1->val = TMonom(Node_1->val.Ratio() * value, Node_1->val.Degree());
      Node_1 = Node_1->pNext;
    }
    return res;
  }

  TPolinom &operator=(const TPolinom &t) {
    if (this != &t) {
      list = t.list;
    }
    return *this;
  }

  TPolinom operator*(const TMonom &m) const {
    TPolinom res = *this;
    typename TSinglyList<TMonom>::TNode *Node_2 = res.list.GetFirst();
    while (Node_2 != nullptr) {
      Node_2->val = TMonom((Node_2->val) * m);
      Node_2 = Node_2->pNext;
    }
    return res;
  }

  TPolinom &operator+=(const TMonom &m) {
    typename TSinglyList<TMonom>::TNode *Node_1 = list.GetFirst();
    bool found = false;
    while (Node_1 != nullptr && !found) {
      if (Node_1->val.Degree() == m.Degree()) {
        double newCoeff = Node_1->val.Ratio() + m.Ratio();
        Node_1->val = TMonom(newCoeff, m.Degree());
        found = true;
      }
      Node_1 = Node_1->pNext;
    }
    if (!found && m.Ratio() != 0) {
      list.PushFront(m);
      sort();
    }
    return *this;
  }

  TPolinom &operator+=(const TPolinom &p) {
    *this = *this + p;
    return *this;
  }

  TPolinom operator*(const TPolinom &p) {
    TPolinom res;
    typename TSinglyList<TMonom>::TNode *Node_1 = list.GetFirst();
    while (Node_1 != nullptr) {
      typename TSinglyList<TMonom>::TNode *Node_2 = p.list.GetFirst();
      while (Node_2 != nullptr) {
        TMonom product = Node_1->val * Node_2->val;
        res += product;
        Node_2 = Node_2->pNext;
      }
      Node_1 = Node_1->pNext;
    }
    return res;
  }

  bool operator==(TPolinom &t) {
    this->sort();
    t.sort();
    return list == t.list;
  }

  TPolinom operator-(const TPolinom &t) { return *this + t * (-1); }

  friend ostream &operator<<(ostream &os, const TPolinom &pol) {
    typename TSinglyList<TMonom>::TNode *Node_1 = pol.list.GetFirst();
    size_t counter = 0;
    while (Node_1 != nullptr) {
      if(Node_1->val.Degree()==0 && Node_1->val.Ratio()==0){
        Node_1=Node_1->pNext;
      }else{
      if (counter == 0) {
        if (Node_1->val.Degree() == 0) {
          os << Node_1->val.Ratio();
        } else {
          os << Node_1->val;
        }
      } else {
        if (Node_1->val.Ratio() < 0) {
          if (Node_1->val.Degree() == 0) {
            os << Node_1->val.Ratio();
          } else {
            os << Node_1->val;
          }

        } else if (Node_1->val.Ratio() > 0) {
          if (Node_1->val.Degree() == 0) {
            os << '+' << Node_1->val.Ratio();
          } else {
            os << '+' << Node_1->val;
          }
        }
      }
      counter++;
      Node_1 = Node_1->pNext;
    }}
    if (counter == 0) {
      os << "0";
    }
    return os;
  }

  void stick() {
    typename TSinglyList<TMonom>::TNode *Node_1 = list.GetFirst();
    while (Node_1 != nullptr && Node_1->pNext != nullptr) {
      if (Node_1->val.Degree() == Node_1->pNext->val.Degree()) {
        Node_1->val = TMonom(Node_1->val.Ratio() + Node_1->pNext->val.Ratio(),
                             Node_1->val.Degree());
        delete Node_1->pNext;
        Node_1->pNext = Node_1->pNext->pNext;
      }
      Node_1 = Node_1->pNext;
    }
  }

  double Calculate_At(const double &_x, const double &_y, const double &_z) {
    TPolinom tmp(*this);
    
    typename TSinglyList<TMonom>::TNode *Node_1 = tmp.list.GetFirst();
    bool flag_is_calculate_over = false;
    double result = 0;
    while (!flag_is_calculate_over) {
      if (Node_1->pNext == nullptr) {
        flag_is_calculate_over = true;
      }
      result += Node_1->val.Ratio() * pow(_x, Node_1->val.Degree() / 100) *
                pow(_y, Node_1->val.Degree() % 100 / 10) *
                pow(_z, Node_1->val.Degree() % 10);
      Node_1 = Node_1->pNext;
    }
    return result;
  }
};