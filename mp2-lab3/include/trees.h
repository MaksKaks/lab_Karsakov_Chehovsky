#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "map.h"
using namespace std;

template <typename TKey, typename TValue>
class BinarySearchTree : public Map<TKey, TValue> {
private:
    using typename Map<TKey, TValue>::Pair;

    struct Node {
        Pair data;
        Node* left;
        Node* right;

        Node(const TKey& key, const TValue& value)
            : data(key, value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int treeSize;

    Node* insertRec(Node* node, const TKey& key, const TValue& value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        if (key < node->data.key) {
            node->left = insertRec(node->left, key, value);
        } else if (key > node->data.key) {
            node->right = insertRec(node->right, key, value);
        } else {
            node->data.value = value;
        }
        return node;
    }

    Node* findRec(Node* node, const TKey& key) const {
        if (node == nullptr || node->data.key == key) {
            return node;
        }

        if (key < node->data.key) {
            return findRec(node->left, key);
        } else {
            return findRec(node->right, key);
        }
    }

    Node* removeRec(Node* node, const TKey& key) {
        if (node == nullptr) return nullptr;

        if (key < node->data.key) {
            node->left = removeRec(node->left, key);
        } else if (key > node->data.key) {
            node->right = removeRec(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = removeRec(node->right, minNode->data.key);
        }
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void inOrderTraversal(Node* node, vector<TKey>& keys) const {
        if (node != nullptr) {
            inOrderTraversal(node->left, keys);
            keys.push_back(node->data.key);
            inOrderTraversal(node->right, keys);
        }
    }

    void inOrderValuesTraversal(Node* node, vector<TValue>& values) const {
        if (node != nullptr) {
            inOrderValuesTraversal(node->left, values);
            values.push_back(node->data.value);
            inOrderValuesTraversal(node->right, values);
        }
    }

    void clearRec(Node* node) {
        if (node != nullptr) {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr), treeSize(0) {}

    ~BinarySearchTree() override {
        Clear();  
    }

    
    TValue* Find(const TKey& key) override {
    Node* node = findRec(root, key);
    if (node != nullptr) {
        return &node->data.value;
    } else {
        return nullptr;
    }
}

    
    void Insert(const TKey& key, const TValue& value) override {
       
        bool isNewKey = (Find(key) == nullptr);  
        root = insertRec(root, key, value);
        if (isNewKey) treeSize++;  
    }

    void Delete(const TKey& key) override {
        
        bool keyExisted = (Find(key) != nullptr);  
        root = removeRec(root, key);
        if (keyExisted) treeSize--;  
    }

    int count() const override {
        return treeSize;
    }

    TValue& operator[](const TKey& key) override {
        
        TValue* existing = Find(key);
        if (existing != nullptr) {
            return *existing;
        }
        Insert(key, TValue());
        
        return *Find(key);
    }

    vector<TKey> keys() const override {
        vector<TKey> result;
        inOrderTraversal(root, result);
        return result;
    }

    vector<TValue> values() const override {
        vector<TValue> result;
        inOrderValuesTraversal(root, result);
        return result;
    }

    void Clear() override {
        clearRec(root);
        root = nullptr;
        treeSize = 0;
    }

    void Print() const override {
        auto allKeys = keys();
        auto allValues = values();

        if (allKeys.empty()) {
            cout << "{}" << endl;
            return;
        }

        cout << "{" << endl;
        for (size_t i = 0; i < allKeys.size(); i++) {
            cout << "  " << allKeys[i] << " : " << allValues[i];
            if (i != allKeys.size() - 1) {
                cout << ",";
            }
            cout << endl;
        }
        cout << "}" << endl;
    }
};