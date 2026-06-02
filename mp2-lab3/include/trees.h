#ifndef __TREES_H__
#define __TREES_H__

#include "map.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

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

    void cleartree(Node* node) {
        if (node == nullptr) return;
        cleartree(node->left);
        cleartree(node->right);
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
        cleartree(root);
        root = nullptr;
        treeSize = 0;
    }
};


template <typename TKey, typename TValue>
class Tree23 : public Map<TKey, TValue> {
private:
    using Pair = typename Map<TKey, TValue>::Pair;

    struct Node {
        TKey keys[3];    
        Pair data;
        Node* parent;
        Node* sons[4];   
        int length;
        bool isLeaf;

        Node() : parent(nullptr), length(0), isLeaf(false) {
            for(int i=0; i<4; ++i) sons[i] = nullptr;
            for(int i=0; i<3; ++i) keys[i] = TKey();
        }

        Node(const TKey& k, const TValue& v)
            : parent(nullptr), length(1), isLeaf(true) { 
             for(int i=0; i<4; ++i) sons[i] = nullptr;
             for(int i=0; i<3; ++i) keys[i] = TKey();
             data = Pair(k, v);
             keys[0] = k;
        }
    };

    Node* root;
    int treeSize;

    TKey maxintree(Node* node) {
        if (!node) return TKey();
        while (node && !node->isLeaf) {
            node = node->sons[node->length - 1];
        }
        return node ? node->data.key : TKey();
    }

    int sonIndex(Node* parent, Node* child) {
        if (!parent) return -1;
        for (int i = 0; i < parent->length; ++i) {
            if (parent->sons[i] == child) return i;
        }
        return -1;
    }

    void sortsons(Node* node) {
        if (!node || node->isLeaf || node->length < 2) return;
        for (int i = 0; i < node->length - 1; ++i) {
            for (int j = i + 1; j < node->length; ++j) {
                if (maxintree(node->sons[j]) < maxintree(node->sons[i])) {
                    swap(node->sons[i], node->sons[j]);
                }
            }
        }
    }

    void updatekeys(Node* from) {
        Node* node = from;

        while (node) {
            if (!node->isLeaf) {
                for (int i = 0; i < node->length - 1; ++i) {
                    if (node->sons[i]) {
                        node->keys[i] = maxintree(node->sons[i]);
                    }
                }
                for (int i = node->length - 1; i < 3; ++i) {
                    node->keys[i] = TKey();
                }
            }
            node = node->parent;
        }
    }

    Node* searchleaf(Node* node, const TKey& key) const {
    while (node && !node->isLeaf) {

        int i = 0;

        while (i < node->length - 1 && key > node->keys[i]) {
            ++i;
        }
        node = node->sons[i];
    }
    return node;
}

    void splitparent(Node* parent) {
        if (!parent || parent->length <= 3) return;
        Node* rightPart = new Node();
        rightPart->isLeaf = false;
        rightPart->length = 2;
        rightPart->sons[0] = parent->sons[2];
        rightPart->sons[1] = parent->sons[3];
        if(rightPart->sons[0]) rightPart->sons[0]->parent = rightPart;
        if(rightPart->sons[1]) rightPart->sons[1]->parent = rightPart;

        parent->length = 2;
        parent->sons[2] = parent->sons[3] = nullptr;
        parent->keys[1] = TKey();

        if (parent->parent) {
            Node* grand = parent->parent;
            grand->sons[grand->length] = rightPart;
            grand->length++;
            rightPart->parent = grand;
            sortsons(grand);
            updatekeys(rightPart);
            splitparent(grand);
        } else {
            Node* newRoot = new Node();
            newRoot->isLeaf = false;
            newRoot->length = 2;
            newRoot->sons[0] = parent;
            newRoot->sons[1] = rightPart;
            parent->parent = newRoot;
            rightPart->parent = newRoot;
            root = newRoot;
            sortsons(newRoot);
            updatekeys(newRoot);
        }
    }

    void cleartree(Node* node) {
        if (!node) return;
        if (!node->isLeaf) {
            for (int i = 0; i < node->length; ++i) {
                cleartree(node->sons[i]);
            }
        }
        delete node;
    }

    void collectInOrder(Node* node, vector<TKey>& keysOut, vector<TValue>& valuesOut) const {
        if (!node) return;
        if (node->isLeaf) {
            keysOut.push_back(node->data.key);
            valuesOut.push_back(node->data.value);
            return;
        }
        for (int i = 0; i < node->length; ++i) {
            if (node->sons[i]) { // <-- ЗАЩИТА ОТ nullptr
                collectInOrder(node->sons[i], keysOut, valuesOut);
            }
        }
    }

    void printTree(Node* node, int level = 0) const {
    if (!node) return;

    for (int i = 0; i < level; ++i)
        cout << "    ";

    if (node->isLeaf) {
        cout << "[Leaf: " << node->data.key
             << " -> " << node->data.value << "]\n";
    }
    else {
        cout << "[Internal ";

        cout << "keys: ";
        for (int i = 0; i < node->length - 1; ++i) {
            cout << node->keys[i];
            if (i + 1 < node->length - 1)
                cout << ", ";
        }

        cout << "]\n";

        for (int i = 0; i < node->length; ++i) {
            printTree(node->sons[i], level + 1);
        }
    }
}

public:
    Tree23() : root(nullptr), treeSize(0) {}
    ~Tree23() override { Clear(); }

    TValue* Find(const TKey& key) override {
        Node* leaf = searchleaf(root, key);
        if (leaf && leaf->isLeaf && leaf->data.key == key) {
            return &leaf->data.value;
        }
        return nullptr;
    }

    void Insert(const TKey& key, const TValue& value) override {
        if (!root) {
            root = new Node(key, value);
            treeSize = 1;
            return;
        }

        Node* pos = searchleaf(root, key);
        if (pos && pos->isLeaf && pos->data.key == key) {
            pos->data.value = value;
            return;
        }

        Node* leaf = new Node(key, value);
        treeSize++;

        if (!pos->parent) {
            Node* newRoot = new Node();
            newRoot->isLeaf = false;
            newRoot->length = 2;
            if (pos->data.key < key) {
                newRoot->sons[0] = pos;
                newRoot->sons[1] = leaf;
            } else {
                newRoot->sons[0] = leaf;
                newRoot->sons[1] = pos;
            }
            pos->parent = newRoot;
            leaf->parent = newRoot;
            root = newRoot;
            updatekeys(root);
            return;
        }

        Node* parent = pos->parent;
        parent->sons[parent->length] = leaf;
        parent->length++;
        leaf->parent = parent;
        sortsons(parent);
        updatekeys(parent);

        if (parent->length > 3) {
            splitparent(parent);
        }
    }

    void Delete(const TKey& key) override {
        Node* cur = root;
        Node* parent = nullptr;
        int idx = -1;

        while (cur && !cur->isLeaf) {
            parent = cur;
            idx = -1;
            for (int i = 0; i < cur->length; ++i) {
                if (i == cur->length - 1 || key <= cur->keys[i]) {
                    idx = i;
                    cur = cur->sons[i];
                    break;
                }
            }
            if (idx == -1) return;
        }

        if (!cur || !cur->isLeaf || cur->data.key != key) return;
        if (!parent) {
            delete cur;
            root = nullptr;
            treeSize = 0;
            return;
        }
        for (int i = idx; i < parent->length - 1; ++i) {
            parent->sons[i] = parent->sons[i + 1];
        }
        parent->length--;
        parent->sons[parent->length] = nullptr;
        for (int i = parent->length - 1; i < 3; ++i) {
            parent->keys[i] = TKey();
        }
        
        delete cur;
        treeSize--;
        updatekeys(parent);
    }

    int Count() const override { return treeSize; }

    TValue& operator[](const TKey& key) override {
        TValue* existing = Find(key);
        if (existing) return *existing;
        Insert(key, TValue());
        return *Find(key);
    }

    vector<TKey> keys() const override {
        vector<TKey> k;
        vector<TValue> v;
        collectInOrder(root, k, v);
        return k;
    }

    vector<TValue> values() const override {
        vector<TKey> k;
        vector<TValue> v;
        collectInOrder(root, k, v);
        return v;
    }

    void Clear() override {
        cleartree(root);
        root = nullptr;
        treeSize = 0;
    }
    
    void Print() override {
    if (!root) {
        cout << "<empty tree>\n";
        return;
    }

    printTree(root);
}
};
#endif
