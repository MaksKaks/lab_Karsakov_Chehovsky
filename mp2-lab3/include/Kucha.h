#ifndef __KUCHA_H__
#define __KUCHA_H__

#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename T>
class Heapmax {
private:
    vector<T> heap;
    int countchild;
    int parentindex(int childindex) const {
        return (childindex - 1) / countchild;}
    int Firstchildindex(int parentind) const {
        return parentind * countchild + 1;}
    
    void bubbleUp(int startIdx) {
        int currentIdx = startIdx;
        while (currentIdx > 0) {
            int parentind = parentindex(currentIdx);
            if (heap[currentIdx] <= heap[parentind]) {
                break;}
            swap(heap[currentIdx], heap[parentind]);
            currentIdx = parentind;}}
    void sinkDown(int startIdx) {
        int currentIdx = startIdx;
        int heapSize = heap.size();
        while (true) {
            int firstChild = Firstchildindex(currentIdx);
            if (firstChild >= heapSize) {break;}
            int lastChild =min(firstChild + countchild - 1, heapSize - 1);
            int biggestchildindex = firstChild;
            for (int i = firstChild + 1; i <= lastChild; ++i) {
                if (heap[i] > heap[biggestchildindex]) {
                    biggestchildindex = i;}}
            if (heap[currentIdx] >= heap[biggestchildindex]) {break;}
            swap(heap[currentIdx], heap[biggestchildindex]);
            currentIdx = biggestchildindex;}}
    
public:
    Heapmax(int numbermaxchild = 2): countchild(numbermaxchild) {
        if (numbermaxchild < 2) {
            throw invalid_argument("!!!need>+2");}}
    Heapmax(const vector<T>& source, int numbermaxchild = 2) 
    : countchild(numbermaxchild) {
        if (numbermaxchild < 2) {
            throw invalid_argument("!!!need>+2");}
        if (source.empty()) {throw invalid_argument("empty");}
        heap = source;
        for (int i = heap.size() / countchild; i >= 0; --i) {sinkDown(i);}}
    
    void push(const T& value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);}
    
    T popmax() {
        if (heap.empty()) {
            throw runtime_error("empty");}
        T maxval = heap[0];
        if (heap.size() == 1) {
            heap.pop_back(); return maxval;}
        heap[0] = heap.back();
        heap.pop_back();
        sinkDown(0);
        return maxval;}
    
    T Getmaxval() const {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");}
        return heap[0];}
    
    int getSize() const {return heap.size();}
    
    bool isEmpty() const {return heap.empty();}
    
    void display() const {
    for (size_t i = 0; i < heap.size(); ++i) {
        cout << heap[i];
        if (i + 1 < heap.size()) {cout << " ";}}
    cout << "\n";}
    
    void clear() {heap.clear();}
};

#endif