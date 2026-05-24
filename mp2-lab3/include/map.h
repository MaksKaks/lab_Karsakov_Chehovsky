#ifndef __MAP_H__
#define __MAP_H__

#include <vector>

using namespace std;

template <typename TKey, typename TValue>
class Map {
public:
    struct Pair {
        TKey key;
        TValue value;
        Pair() = default;
        Pair(const TKey& k, const TValue& v) : key(k), value(v) {}

        bool operator<(const Pair& other) const { return key < other.key; }
        bool operator>(const Pair& other) const { return key > other.key; }
        bool operator==(const Pair& other) const { return key == other.key; }
        bool operator==(const TKey& otherKey) const { return key == otherKey; }
    };

    virtual ~Map() = default;

    virtual TValue* Find(const TKey& key) = 0;
    virtual void Insert(const TKey& key, const TValue& value) = 0;
    virtual void Delete(const TKey& key) = 0;
    virtual int Count() const = 0;
    virtual bool isempty() const { return Count() == 0; }
    virtual TValue& operator[](const TKey& key) = 0;
    virtual vector<TKey> keys() const = 0;
    virtual vector<TValue> values() const  = 0;
    virtual void Clear() = 0;
    virtual void Print() = 0;
};

// template <typename TKey, typename TValue>
// class Orderedmap : public Map<TKey, TValue> {
// private:
//     using typename Map<TKey, TValue>::Pair;
//     vector<Pair> data;
    
//     int Binsearch(const TKey& key) const {
//         int left = 0;
//         int right = data.size() - 1;
//         while (left <= right) {
//             int mid = left + (right - left) / 2;
//             if (data[mid].key == key) {
//                 return mid;  }
//             if (data[mid].key < key) {
//                 left = mid + 1;} else {
//                 right = mid - 1;}} return -left - 1;}
    
// public:
//     Orderedmap() = default;
//     ~Orderedmap() = default;
//     TValue* Find(const TKey& key) override {
//         int result = Binsearch(key);
//         if (result >= 0) {
//             return &data[result].value;} return nullptr;}
    
//     void Insert(const TKey& key, const TValue& value) override {
//         int result = Binsearch(key);
//         if (result >= 0) {
//             data[result].value = value; return;}
//         size_t insertPos = -result - 1;  
//         data.insert(data.begin() + insertPos, Pair(key, value));
//     }
    
//     void Delete(const TKey& key) override {
//         int result = Binsearch(key);
//         if (result < 0) {
//             throw invalid_argument("Key not found");}
//         data.erase(data.begin() + result);}
//     int Count() const override { return data.size();}
    
//     TValue& operator[](const TKey& key) override {
//         int result = Binsearch(key);
//         if (result >= 0) { return data[result].value;}
//         size_t insertPos = -result - 1;
//         data.insert(data.begin() + insertPos, Pair(key, TValue()));
//         return data[insertPos].value;}

//     vector<TKey> Keys() const override {
//         vector<TKey> result;
//         for (const auto& pair : data) {
//             result.push_back(pair.key);} return result;}
    
//     vector<TValue> Values() const override {
//         vector<TValue> result;
//         for (const auto& pair : data) {
//             result.push_back(pair.value);} return result;}
    
//     void Clear() override { data.clear();}
//     void Print() const {
//         if (data.empty()) {
//         cout << "{}" << endl; return;}
//         for (size_t i = 0; i < data.size(); i++) {
//             cout << "  " << data[i].key <<" : "<< data[i].value;
//             if (i != data.size() - 1) {
//                 cout<<",";}
//             cout << endl;}}
// };


// template <typename TKey, typename TValue>
// class Unorderedmap : public Map<TKey, TValue> {
// private:
//     using typename Map<TKey, TValue>::Pair;  
//     TSinglyList<Pair> list;  
// public:
//     Unorderedmap() = default;
//     ~Unorderedmap() = default;
//     TValue* Find(const TKey& key) override {
//         for (int i = 0; i < list.size(); i++) {
//             if (list[i] == key) { 
//                 return &list[i].value;}}
//         return nullptr;}
// void Insert(const TKey& key, const TValue& value) override {
//     for (int i = 0; i < list.size(); i++) {
//         if (list[i] == key) {
//             list[i].value = value; return;}}
//     list.PushFront(Pair(key, value));}
    
// void Delete(const TKey& key) override {
//         if (list.isEmpty()) {
//             throw invalid_argument("Key not");}
//         if (list.GetFirst()->val == key) {  
//             list.PopFront(); return;}
//         for (int i = 1; i < list.size(); i++) {
//             if (list[i] == key) { 
//                 list.EraseAfter(i - 1);
//                 return;}}
//         throw invalid_argument("Key not");}
//     int Count() const override { return list.size();}
//     TValue& operator[](const TKey& key) override {
//         TValue* val = Find(key);
//         if (val != nullptr) {
//             return *val;}
//         list.PushFront(Pair(key, TValue()));
//         return list.GetFirst()->val.value;}
//     vector<TKey> Keys() const override {
//         vector<TKey> result;
//         result.reserve(list.size());
//         for (int i = 0; i < list.size(); i++) {
//             result.push_back(list[i].key);}
//         return result;}
//     vector<TValue> Values() const override {
//         vector<TValue> result;
//         result.reserve(list.size());
//         for (int i = 0; i < list.size(); i++) {
//             result.push_back(list[i].value);}
//         return result;}
//     void Clear() override {
//         while (!list.isEmpty()) {
//             list.PopFront();}}
//     void Print() const {
//         if (list.isEmpty()) {
//             cout << "{}" << endl;
//             return;}
//         for (int i = 0; i < list.size(); i++) {
//             cout << "  " << list[i].key << " : " << list[i].value;
//             if (i != list.size() - 1) {
//                 cout << ",";}
//             cout << endl;};}
// };

 #endif