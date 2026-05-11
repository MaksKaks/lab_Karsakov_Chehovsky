#ifndef __TLISTS_H__
#define __TLISTS_H__

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class TSinglyList {
public:
    struct TNode {
        T val;
        TNode* pNext;
        TNode(T v, TNode* p = nullptr) : val(v), pNext(p) {}
    };

private:
    TNode* pFirst;
    size_t sz;

public:
    TSinglyList() : pFirst(nullptr), sz(0) {}

    TSinglyList(const vector<T>& v) : pFirst(nullptr), sz(0) {
        if (v.empty()) throw invalid_argument("Vector size must be > 0");
        pFirst = new TNode(v[0]);
        sz = 1;
        TNode* current = pFirst;
        for (size_t i = 1; i < v.size(); ++i) {
            current->pNext = new TNode(v[i]);
            current = current->pNext;
            ++sz;
        }
    }

    TSinglyList(const TSinglyList& list) : pFirst(nullptr), sz(0) {
        if (!list.pFirst) return;
        pFirst = new TNode(list.pFirst->val);
        sz = 1;
        TNode* cur1 = pFirst;
        TNode* cur2 = list.pFirst->pNext;
        while (cur2) {
            cur1->pNext = new TNode(cur2->val);
            cur1 = cur1->pNext;
            cur2 = cur2->pNext;
            ++sz;
        }
    }

    TSinglyList& operator=(const TSinglyList& list) {
        if (this == &list) return *this;
        Clear();
        if (!list.pFirst) return *this;
        pFirst = new TNode(list.pFirst->val);
        sz = 1;
        TNode* cur1 = pFirst;
        TNode* cur2 = list.pFirst->pNext;
        while (cur2) {
            cur1->pNext = new TNode(cur2->val);
            cur1 = cur1->pNext;
            cur2 = cur2->pNext;
            ++sz;
        }
        return *this;
    }

    ~TSinglyList() { Clear(); }

    bool operator==(const TSinglyList& list) const {
        if (sz != list.sz) return false;
        TNode* t1 = pFirst;
        TNode* t2 = list.pFirst;
        while (t1 && t2) {
            if (!(t1->val == t2->val)) return false;
            t1 = t1->pNext;
            t2 = t2->pNext;
        }
        return true;
    }

    size_t size() const noexcept { return sz; }
    bool isEmpty() const noexcept { return sz == 0; }
    T& Front() {
        if (!pFirst) throw runtime_error("List is empty");
        return pFirst->val;
    }

    void PushFront(const T& val) {
        pFirst = new TNode(val, pFirst);
        ++sz;
    }

    void PopFront() {
        if (!pFirst) throw runtime_error("List is empty");
        TNode* tmp = pFirst;
        pFirst = pFirst->pNext;
        delete tmp;
        --sz;
    }

    void PushBack(const T& val) {
        if (!pFirst) {
            PushFront(val);
            return;
        }
        TNode* cur = pFirst;
        while (cur->pNext) cur = cur->pNext;
        cur->pNext = new TNode(val);
        ++sz;
    }

    T& operator[](size_t pos) {
        if (pos >= sz) throw out_of_range("Index out of bounds");
        TNode* cur = pFirst;
        for (size_t i = 0; i < pos; ++i) cur = cur->pNext;
        return cur->val;
    }

    void PushAfter(size_t pos, const T& val) {
        if (pos >= sz) throw invalid_argument("Incorrect position");
        TNode* cur = pFirst;
        for (size_t i = 0; i < pos; ++i) cur = cur->pNext;
        cur->pNext = new TNode(val, cur->pNext);
        ++sz;
    }

    void EraseAfter(size_t pos) {
        if (pos >= sz - 1) throw invalid_argument("Incorrect position");
        TNode* cur = pFirst;
        for (size_t i = 0; i < pos; ++i) cur = cur->pNext;
        TNode* toDelete = cur->pNext;
        cur->pNext = toDelete->pNext;
        delete toDelete;
        --sz;
    }

    void Clear() {
        while (pFirst) PopFront();
        sz = 0;
    }

    TNode* GetFirst() const { return pFirst; }
    TNode* GetLast() const {
        if (!pFirst) return nullptr;
        TNode* cur = pFirst;
        while (cur->pNext) cur = cur->pNext;
        return cur;
    }
};

#endif
