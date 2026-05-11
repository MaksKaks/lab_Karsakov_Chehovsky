#ifndef __STACK_H__
#define __STACK_H__



#include <algorithm>
#include <stdexcept>
using namespace std;
template <typename T>
class TStack {
private:
    int capacity;
    int topIdx;
    T* mem;

public:
    TStack(int size = 10) : capacity(size), topIdx(-1) {
        mem = new T[capacity];
    }

    ~TStack() { delete[] mem; }

    void push(const T& val) {
        if (topIdx + 1 >= capacity) {
            int newCap = capacity * 2;
            T* newMem = new T[newCap];
            for (int i = 0; i <= topIdx; ++i) newMem[i] = mem[i];
            delete[] mem;
            mem = newMem;
            capacity = newCap;
        }
        mem[++topIdx] = val;
    }

    T pop() {
        if (topIdx < 0) throw invalid_argument("Stack is empty");
        return mem[topIdx--];
    }

    bool isEmpty() const { return topIdx == -1; }

    T& Top() {
        if (topIdx < 0) throw invalid_argument("Stack is empty");
        return mem[topIdx];
    }

    int get_count() const { return topIdx + 1; }
};

#endif