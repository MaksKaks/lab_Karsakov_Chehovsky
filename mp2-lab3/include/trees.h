#ifndef __TREES_H__
#define __TREES_H__

#include "map.h"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename TKey, typename TValue>
class Binarytree : public Map<TKey, TValue> {
private:
    using Pair = typename Map<TKey, TValue>::Pair;

    struct Node {
        Pair data;
        Node* left;
        Node* right;
        Node(const TKey& k, const TValue& v) : data(k, v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int treeSize;

    Node* insertNode(Node* node, const TKey& key, const TValue& value) {
        if (node == nullptr) return new Node(key, value);
        if (key < node->data.key) node->left = insertNode(node->left, key, value);
        else if (key > node->data.key) node->right = insertNode(node->right, key, value);
        else node->data.value = value;
        return node;
    }

    Node* findNode(Node* node, const TKey& key) const {
        if (node == nullptr) return nullptr;
        if (node->data.key == key) return node;
        if (key < node->data.key) return findNode(node->left, key);
        return findNode(node->right, key);
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* removeNode(Node* node, const TKey& key) {
        if (node == nullptr) return nullptr;
        if (key < node->data.key) {
            node->left = removeNode(node->left, key);
        } else if (key > node->data.key) {
            node->right = removeNode(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* rightSubtree = node->right;
                delete node;
                return rightSubtree;
            }
            if (node->right == nullptr) {
                Node* leftSubtree = node->left;
                delete node;
                return leftSubtree;
            }
            Node* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = removeNode(node->right, minNode->data.key);
        }
        return node;
    }

    void collectKeys(Node* node, vector<TKey>& out)  const {
        if (node == nullptr) return;
        collectKeys(node->left, out);
        out.push_back(node->data.key);
        collectKeys(node->right, out);
    }

    void collectValues(Node* node, vector<TValue>& out) const {
        if (node == nullptr) return;
        collectValues(node->left, out);
        out.push_back(node->data.value);
        collectValues(node->right, out);
    }

    void clearTree(Node* node) {
        if (node == nullptr) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

public:
    Binarytree() : root(nullptr), treeSize(0) {}
    ~Binarytree() override { Clear(); }

    TValue* Find(const TKey& key) override {
    Node* node = findNode(root, key);
    if (node != nullptr) {
        return &node->data.value;
    } else {
        return nullptr;
    }
}

    void Insert(const TKey& key, const TValue& value) override {
        bool isNew = (Find(key) == nullptr);
        root = insertNode(root, key, value);
        if (isNew) ++treeSize;
    }

    void Delete(const TKey& key) override {
        bool exists = (Find(key) != nullptr);
        root = removeNode(root, key);
        if (exists) --treeSize;
    }

    int Count() const override {
        return treeSize;
    }

    TValue& operator[](const TKey& key) override {
        TValue* existing = Find(key);
        if (existing) return *existing;
        Insert(key, TValue());
        return *Find(key);
    }

    vector<TKey> keys()  override {
        vector<TKey> out;
        collectKeys(root, out);
        return out;
    }

    vector<TValue> values() override {
        vector<TValue> out;
        collectValues(root, out);
        return out;
    }

    void Print() override {
        vector<TKey> allKeys = keys();
        vector<TValue> allValues = values();
        if (allKeys.empty()) {
            cout << "{}" << endl;
            return;
        }
        for (size_t i = 0; i < allKeys.size(); i++) {
            cout << " " << allKeys[i] << " : " << allValues[i];
            if (i + 1 != allKeys.size()) cout << ",";
            cout << endl;
        }
    }

    void Clear() override {
        clearTree(root);
        root = nullptr;
        treeSize = 0;
    }
};

#endif