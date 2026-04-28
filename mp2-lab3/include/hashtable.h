#ifndef __CHAINHASHTABLE_H__
#define __CHAINHASHTABLE_H__

#include <iostream>
#include <vector>
#include <stdexcept>
#include "map.h"

using namespace std;

template <typename TKey, typename TValue>
class ChainHashTable : public Map<TKey, TValue> {
private:
    using typename Map<TKey, TValue>::Pair;
    struct Node {
        Pair data;
        Node* next;
        Node(const TKey& key, const TValue& value, Node* n = nullptr)
            : data(key, value), next(n) {}
    };
    Node** buckets;          
    int tableSize;           
    int elementCount;        
    double loadFactorLimit;  
    
    int simpleNumbers[25] = {31,      67,      131,     257,      521,      1031,     2053,      4099,
                             8209,    16411,   32771,   65537,    131101,   262147,   524309,    1048583,
                             2097169, 4194319, 8388617, 16777259, 33554467, 67108879, 134217757, 268435459};
    int indexNumber;         
    int hash(const TKey& key) const {
        int sum = 0;
        for (char ch : key) sum += ch;
        return sum % tableSize;}
    
    double loadFactor() const {
        return (double)elementCount / tableSize;}
    void ReHash() {
        if (indexNumber >= 24) return;  
        indexNumber++;
        int newSize = simpleNumbers[indexNumber];
        Node** newBuckets = new Node*[newSize]();
        for (int i = 0; i < newSize; i++) {
            newBuckets[i] = nullptr;}
        for (int i = 0; i < tableSize; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* next = current->next;
                int sum = 0;
                for (char ch : current->data.key) sum += ch;
                int newIndex = sum % newSize;
                current->next = newBuckets[newIndex];
                newBuckets[newIndex] = current;
                current = next;}}
        delete[] buckets;
        buckets = newBuckets;
        tableSize = newSize;
    }
public:
    ChainHashTable() : tableSize(simpleNumbers[0]), elementCount(0), loadFactorLimit(0.75), indexNumber(0) {
        buckets = new Node*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            buckets[i] = nullptr;}}

    ~ChainHashTable() override {
        Clear();
        delete[] buckets;}
    
    
    TValue* Find(const TKey& key) override {
        int index = hash(key);
        Node* current = buckets[index];
        
        while (current != nullptr) {
            if (current->data.key == key) {
                return &current->data.value;}
            current = current->next;}
        return nullptr;}
    void Insert(const TKey& key, const TValue& value) override {
        if (loadFactor() > loadFactorLimit && indexNumber < 24) {
            ReHash();}
        int index = hash(key);
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->data.key == key) {
                current->data.value = value;
                return;}
            current = current->next;}
        buckets[index] = new Node(key, value, buckets[index]);
        elementCount++;}

    void Delete(const TKey& key) override {
        int index = hash(key);
        Node* current = buckets[index];
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->data.key == key) {
                if (prev == nullptr) {
                    buckets[index] = current->next;} else {
                    prev->next = current->next;}
                delete current;
                elementCount--;
                return;}
            prev = current;
            current = current->next;}
        throw invalid_argument("Key not found");}

    int count() const override { return elementCount;}
    bool isempty() const {return elementCount == 0;}

    TValue& operator[](const TKey& key) override {
        TValue* found = Find(key);
        if (found != nullptr) {
            return *found;}
        Insert(key, TValue{});
        return *Find(key);}

    vector<TKey> keys() const override {
        vector<TKey> result;
        result.reserve(elementCount);
        for (int i = 0; i < tableSize; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                result.push_back(current->data.key);
                current = current->next;}}
        return result;}

    vector<TValue> values() const override {
        vector<TValue> result;
        result.reserve(elementCount);
        for (int i = 0; i < tableSize; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                result.push_back(current->data.value);
                current = current->next;}}
        return result;}

    void Clear() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;}
            buckets[i] = nullptr;}
        elementCount = 0;}

    void Print() {
        cout << "{\n";
        for (int i = 0; i < tableSize; i++) {
            Node* current = buckets[i];
            if (current != nullptr) {
                while (current != nullptr) {
                    cout << "\t" << current->data.key << ": " << current->data.value << endl;
                    current = current->next;}}}

        cout << "}\n";}

    int getSize() const { return tableSize;}
    int getIndexNumber() const { return indexNumber;}
};
#endif