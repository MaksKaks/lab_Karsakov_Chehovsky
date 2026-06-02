#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

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
    int Size;           
    int elcount;        
    double Limit;  
    int indexprostchislo;
    int simplenumber[25] = {31,67,131,257,521,1031,2053,4099,8209,16411,32771,
        65537,131101,262147,524309,1048583,2097169, 4194319,8388617,
        16777259,33554467, 67108879, 134217757, 268435459};         
    int hash(const TKey& key) const {
        int sum = 0;
        for (char ch : key) sum += ch;
        return sum % Size;}

    void ReHash() {
        if (indexprostchislo >= 24) return;  
        indexprostchislo++;
        int newSize = simpleNumbers[indexprostchislo];
        Node** newBuckets = new Node*[newSize]();
        for (int i = 0; i < newSize; i++) {
            newBuckets[i] = nullptr;}
        for (int i = 0; i < Size; i++) {
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
        Size = newSize;
    }
public:
    ChainHashTable() : Size(simpleNumbers[0]), elcount(0), Limit(0.75), indexprostchislo(0) {
        buckets = new Node*[Size];
        for (int i = 0; i < Size; i++) {
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
        if ((double)elcount / Size; > Limit && indexprostchislo < 24) {
            ReHash();}
        int index = hash(key);
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->data.key == key) {
                current->data.value = value;
                return;}
            current = current->next;}
        buckets[index] = new Node(key, value, buckets[index]);
        elcount++;}

    void Delete(const TKey& key) override {
        int index = hash(key);
        Node* current = buckets[index];
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->data.key == key) {
                if (prev == nullptr) {
                    buckets[index] = current->next;} 
                else {
                    prev->next = current->next;}
                delete current;
                elcount--;
                return;}
            prev = current;
            current = current->next;}
        throw invalid_argument("Key not");}

    int count() const override { return elcount;}
    bool isempty() const {return elcount == 0;}

    TValue& operator[](const TKey& key) override {
        TValue* found = Find(key);
        if (found != nullptr) {
            return *found;}
        Insert(key, TValue{});
        return *Find(key);}

    vector<TKey> keys() const override {
        vector<TKey> result;
        for (int i = 0; i < Size; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                result.push_back(current->data.key);
                current = current->next;}}
        return result;}

    vector<TValue> values() const override {
        vector<TValue> result;
        for (int i = 0; i < Size; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                result.push_back(current->data.value);
                current = current->next;}}
        return result;}

    void Clear() {
        for (int i = 0; i < Size; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* del = current;
                current = current->next;
                delete del;}
            buckets[i] = nullptr;}
        elcount = 0;}

    void Print() {
        cout << "{\n";
        for (int i = 0; i < Size; i++) {
            Node* current = buckets[i];
            if (current != nullptr) {
                while (current != nullptr) {
                    cout << " " << current->data.key << ": " << current->data.value << endl;
                    current = current->next;}}}

        cout << "}\n";}

    int getSize() const { return Size;}
    int getindexprostchislo() const { return indexprostchislo;}
};
#endif