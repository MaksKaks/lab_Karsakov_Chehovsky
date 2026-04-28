#ifndef __TREES_H__
#define __TREES_H__
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "map.h"
using namespace std;

template <typename TKey, typename TValue>
class Binarytree : public Map<TKey, TValue> {
private:
    using typename Map<TKey, TValue>::Pair;
    struct Node {
        Pair data;
        Node* left;
        Node* right;
        Node(const TKey& key, const TValue& value) : data(key, value), left(nullptr), right(nullptr) {}};
    Node* root;
    int treeSize;

    Node* insertnode(Node* node, const TKey& key, const TValue& value) {
        if (node == nullptr) { return new Node(key, value); }
        if (key < node->data.key) { node->left = insertnode(node->left, key, value); }
        else if (key > node->data.key) { node->right = insertnode(node->right, key, value); }
        else { node->data.value = value; }
        return node;}
    Node* findnode(Node* node, const TKey& key) const {
        if (node == nullptr || node->data.key == key) { return node; }
        if (key < node->data.key) { return findnode(node->left, key); }
        else { return findnode(node->right, key);}}

    Node* removenode(Node* node, const TKey& key) {
        if (node == nullptr) return nullptr;
        if (key < node->data.key) { node->left = removenode(node->left, key); }
        else if (key > node->data.key) { node->right = removenode(node->right, key); }
        else {
            if (node->left == nullptr) { Node* temp = node->right; delete node; return temp; }
            else if (node->right == nullptr) { Node* temp = node->left; delete node; return temp; }
            Node* minNode = findmin(node->right);
            node->data = minNode->data;
            node->right = removenode(node->right, minNode->data.key);}
        return node;}

    Node* findmin(Node* node) const {
        while (node && node->left != nullptr) { node = node->left; }
        return node;}

    void allkeys(Node* node, vector<TKey>& keys) const {
        if (node != nullptr) {
            allkeys(node->left, keys);
            keys.push_back(node->data.key);
            allkeys(node->right, keys);}}
    void allval(Node* node, vector<TValue>& values) const {
        if (node != nullptr) {
            allval(node->left, values);
            values.push_back(node->data.value);
            allval(node->right, values);}}
    void clearrec(Node* node) {
        if (node != nullptr) {
            clearrec(node->left);
            clearrec(node->right);
            delete node;}}
    public:
    Binarytree() : root(nullptr), treeSize(0) {}
    ~Binarytree() override { clear(); }

    TValue* Find(const TKey& key) override {
        Node* node = findnode(root, key);
        if (node != nullptr) { return &node->data.value; }
        else { return nullptr; }}

    void Insert(const TKey& key, const TValue& value) override {
        bool isNewKey = (Find(key) == nullptr);
        root = insertnode(root, key, value);
        if (isNewKey) treeSize++;}

    void Delete(const TKey& key) override {
        bool keyExisted = (Find(key) != nullptr);
        root = removenode(root, key);
        if (keyExisted) treeSize--;}
    int count() const override { return treeSize; }

    TValue& operator[](const TKey& key) override {
        TValue* existing = Find(key);
        if (existing != nullptr) { return *existing; }
        Insert(key, TValue());
        return *Find(key);}
    vector<TKey> keys() const override {
        vector<TKey> result;
        allkeys(root, result);
        return result;}

    vector<TValue> values() const override {
        vector<TValue> result;
        allval(root, result);
        return result;}

    void clear() override {
        clearrec(root);
        root = nullptr;
        treeSize = 0;}
    void Print() const override {
        auto allKeys = keys();
        auto allValues = values();
        if (allKeys.empty()) { cout << "{}" << endl; return; }
        for (size_t i = 0; i < allKeys.size(); i++) {
            cout << " " << allKeys[i] << " : " << allValues[i];
            if (i != allKeys.size() - 1) { cout << ","; }
            cout << endl;}
        }
};
#endif