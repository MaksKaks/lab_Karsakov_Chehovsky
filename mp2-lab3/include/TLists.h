#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
#ifndef _TSINGLYLIST_H_
#define _TSINGLYLIST_H_

template <typename T> class TSinglyList {
public:
  struct TNode {
    T val;
    TNode *pNext;
    TNode(T v, TNode *p = nullptr) : val(v), pNext(p){};
  };

private:
  TNode *pFirst;
  size_t sz;

public:
  friend class TPolinom;
  TSinglyList() : pFirst(nullptr), sz(0) {}

  TSinglyList(const vector<T> &v) {
    if (v.size() != 0) {
      pFirst = new TNode(v[0]);
      sz = 1;
      TNode *current = pFirst;
      for (size_t i = 0; i < v.size(); i++) {
        current->pNext = new TNode(v[i]);
        current = current->pNext;
        sz++;
      }
    } else {
      throw invalid_argument("Vector size must be > 0");
    }
  }

  TSinglyList(const TSinglyList &list) : pFirst(nullptr), sz(0) {
    if (!list.pFirst)
      throw invalid_argument("Incorrect list");

    pFirst = new TNode(list.pFirst->val);
    sz++;
    TNode *current = pFirst;
    TNode *current2 = list.pFirst->pNext;

    while (current2 != nullptr) {
      current->pNext = new TNode(current2->val);
      current = current->pNext;
      current2 = current2->pNext;
      sz++;
    }
  }

  bool operator==(const TSinglyList &list) {
    if (sz != list.sz) {
      return false;
    } else {
      TNode *tmp1 = pFirst;
      TNode *tmp2 = list.GetFirst();
      while (tmp1 != nullptr && tmp2 != nullptr && tmp1->pNext != nullptr &&
             tmp2->pNext != nullptr) {
        if (tmp1->val != tmp2->val) {
          return false;
        }
        tmp1 = tmp1->pNext;
        tmp2 = tmp2->pNext;
      }
    }
    return true;
  }

  TSinglyList(TSinglyList &&list) noexcept {
    swap(pFirst, list.pFirst);
    sz = list.sz;
  }

  TSinglyList &operator=(const TSinglyList &list) {
    if (this == &list) {
      return *this;
    }
    pFirst = new TNode(list.pFirst->val);
    sz++;
    TNode *current = pFirst;
    TNode *current2 = list.pFirst->pNext;

    while (current2 != nullptr) {
      current->pNext = new TNode(current2->val);
      current = current->pNext;
      current2 = current2->pNext;
      sz++;
    }

    return *this;
  }

  TSinglyList &operator=(TSinglyList &&list) {
    swap(pFirst, list.pFirst);
    sz = list.sz;
    return *this;
  }

  size_t size() const noexcept { return sz; }
  bool isEmpty() const noexcept { return (sz == 0); }
  T &Front() noexcept { return *pFirst->val; }
  void PushFront(const T &val) {
    TNode *t = new TNode(val, nullptr);
    t->pNext = pFirst;
    pFirst = t;
  }
  void PopFront() noexcept {
    TNode *t = pFirst;
    pFirst = pFirst->pNext;
    delete t;
  }
  void PushBack(const T &val) {
    TNode *newNode = new TNode(val, nullptr);

    if (!pFirst) {
      pFirst = newNode;
    } else {
      TNode *current = pFirst;
      while (current->pNext) {
        current = current->pNext;
      }
      current->pNext = newNode;
    }
    sz++;
  }
  T &operator[](size_t pos) {
    TNode *tmp = pFirst;
    for (size_t i = 0; i < pos; i++) {
      tmp = tmp->pNext;
    }
    return tmp->val;
  }
  void PushAfter(size_t pos, const T &val) {
    if (pos <= 0 || pos > sz) {
      throw invalid_argument("Incorrect position");
    }
    TNode *tmp = pFirst;
    for (size_t i = 0; i < pos; i++) {
      tmp = tmp->pNext;
    }
    TNode *t = new TNode(val, tmp->pNext);
    tmp->pNext = t;
  }
  void EraseAfter(size_t pos) {
    if (pos <= 0 || pos > sz) {
      throw invalid_argument("Incorrect position");
    }
    TNode *tmp = pFirst;
    for (size_t i = 0; i < pos; i++) {
      tmp = tmp->pNext;
    }
    TNode *t = tmp->pNext;
    tmp->pNext = tmp->pNext->pNext;
    delete t;
  }

  ~TSinglyList() {
    while (pFirst) {
      PopFront();
    }
  }

  TNode *GetFirst() const { return pFirst; }
  TNode *GetLast() const {
    TNode *tmp = pFirst;
    for (size_t i = 0; i < sz; i++) {
      tmp = tmp->pNext;
    }
    return tmp;
  }
};

#endif