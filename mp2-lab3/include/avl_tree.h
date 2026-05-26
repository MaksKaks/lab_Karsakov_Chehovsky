#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename TKey, typename TValue>
class AVLTree {
private:
    struct Node {
        TKey key;
        TValue value;
        Node* left;
        Node* right;
        int height;

        Node(const TKey& k, const TValue& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int treeSize;

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    int getBalance(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* B = x->right;

        x->right = y;
        y->left = B;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* B = y->left;

        y->left = x;
        x->right = B;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        if (!node) return nullptr;

        updateHeight(node);

        int balanceFactor = getBalance(node);

        //левое поддерево выше правого (нужен правый поворот)
        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        //правое поддерево выше левого (нужен левый поворот)
        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    Node* insertNode(Node* node, const TKey& key, const TValue& value) {
        if (!node) {
            treeSize++;
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key, value);
        }
        else {
            node->value = value;
            return node;
        }

        return balance(node);
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, const TKey& key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else {

            if (!node->left && !node->right) {
                delete node;
                treeSize--;
                return nullptr;
            }

            if (!node->left) {
                Node* rightChild = node->right;
                delete node;
                treeSize--;
                return rightChild;
            }
            if (!node->right) {
                Node* leftChild = node->left;
                delete node;
                treeSize--;
                return leftChild;
            }

            Node* minNode = findMin(node->right);
            node->key = minNode->key;
            node->value = minNode->value;
            node->right = deleteNode(node->right, minNode->key);
        }

        return balance(node);
    }

    void collectKeys(Node* node, vector<TKey>& out) const {
        if (!node) return;
        collectKeys(node->left, out);
        out.push_back(node->key);
        collectKeys(node->right, out);
    }

    void collectValues(Node* node, vector<TValue>& out) const {
        if (!node) return;
        collectValues(node->left, out);
        out.push_back(node->value);
        collectValues(node->right, out);
    }
    
    void clearTree(Node* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr), treeSize(0) {}

    ~AVLTree() {
        clearTree(root);
    }

    TValue* Find(const TKey& key) {
        Node* current = root;
        while (current) {
            if (key == current->key) {
                return &current->value;
            }
            else if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void Insert(const TKey& key, const TValue& value) {
        root = insertNode(root, key, value);
    }

    void Delete(const TKey& key) {
        if (Find(key)) {
            root = deleteNode(root, key);
        }
    }

    int Count() const {
        return treeSize;
    }

    bool isempty() const {
        return treeSize == 0;
    }

    TValue& operator[](const TKey& key) {
        TValue* value = Find(key);
        if (value) {
            return *value;
        }
        Insert(key, TValue());
        return *Find(key);
    }

    vector<TKey> keys() {
        vector<TKey> result;
        collectKeys(root, result);
        return result;
    }

    vector<TValue> values() {
        vector<TValue> result;
        collectValues(root, result);
        return result;
    }

    void Clear() {
        clearTree(root);
        root = nullptr;
        treeSize = 0;
    }

    void Print() {
        if (isempty()) {
            cout << "{}" << endl;
            return;
        }

        vector<TKey> allKeys = keys();
        vector<TValue> allValues = values();

        cout << "{" << endl;
        for (size_t i = 0; i < allKeys.size(); i++) {
            cout << "  " << allKeys[i] << " : " << allValues[i];
            if (i + 1 != allKeys.size()) cout << ",";
            cout << endl;
        }
        cout << "}" << endl;
    }
};

#endif