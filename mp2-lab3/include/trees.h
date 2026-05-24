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




template <typename TKey, typename TValue>
class Tree23 : public Map<TKey, TValue> {
private:
    using Pair = typename Map<TKey, TValue>::Pair;

    struct Node {
        // ИСПРАВЛЕНО: Увеличены размеры массивов для временного хранения 4 детей при сплите
        TKey keys[3];    
        Pair data;
        Node* parent;
        Node* sons[4];   // Было [3], стало [4]
        int length;
        bool isLeaf;

        Node() : parent(nullptr), length(0), isLeaf(false) {
            for(int i=0; i<4; ++i) sons[i] = nullptr;
        }

        Node(const TKey& k, const TValue& v)
            : parent(nullptr), length(1), isLeaf(true) { // Leaf has length 1 logically in some impls, but here we treat leaf as having data
             // В вашей реализации лист хранит данные в data, а sons пустые.
             // Но для унификации length у листа обычно 0 или 1. 
             // Оставим как у вас было, но важно, что sons пусты.
             for(int i=0; i<4; ++i) sons[i] = nullptr;
             data = Pair(k, v);
             keys[0] = k;
        }
    };

    Node* root;
    int treeSize;

    // Вспомогательные методы
    TKey maxintree(Node* node) {
        if (!node) return TKey();
        while (node && !node->isLeaf) {
            node = node->sons[node->length - 1];
        }
        return node ? node->data.key : TKey();
    }

    static int sonIndex(Node* parent, Node* child) {
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
        Node* node = from ? from->parent : nullptr;
        while (node) {
            for (int i = 0; i < node->length - 1; ++i) {
                node->keys[i] = maxintree(node->sons[i]);
            }
            node = node->parent;
        }
    }

    Node* searchleaf(Node* node, const TKey& key) const {
        while (node && !node->isLeaf) {
            if (node->length == 2) {
                node = (key < node->keys[0]) ? node->sons[0] : node->sons[1];
            } else if (node->length == 3) {
                if (key < node->keys[0]) node = node->sons[0];
                else if (key < node->keys[1]) node = node->sons[1];
                else node = node->sons[2];
            } else {
                 // Fallback or error
                 break;
            }
        }
        return node;
    }

    void splitParent(Node* parent) {
        if (!parent || parent->length <= 3) return;

        Node* rightPart = new Node();
        rightPart->isLeaf = false;
        rightPart->length = 2;
        // Переносим 3-го и 4-го ребенка
        rightPart->sons[0] = parent->sons[2];
        rightPart->sons[1] = parent->sons[3];
        if(rightPart->sons[0]) rightPart->sons[0]->parent = rightPart;
        if(rightPart->sons[1]) rightPart->sons[1]->parent = rightPart;

        parent->length = 2;
        parent->sons[2] = parent->sons[3] = nullptr;

        if (parent->parent) {
            Node* grand = parent->parent;
            grand->sons[grand->length] = rightPart;
            grand->length++;
            rightPart->parent = grand;
            sortsons(grand);
            updatekeys(rightPart);
            splitParent(grand);
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

    void onlyson(Node* node) {
        if (!node || node->isLeaf || node->length >= 2) return;
        if (!node->parent) {
            if (node->length == 1) {
                root = node->sons[0];
                if(root) root->parent = nullptr;
                delete node;
            }
            return;
        }
        Node* parent = node->parent;
        int index = sonIndex(parent, node);
        if (index < 0) return;
        Node* only = node->sons[0];
        parent->sons[index] = only;
        if(only) only->parent = parent;
        delete node;
        updatekeys(parent); // Обновляем ключи родителя
        
        if (parent->length < 2 && !parent->isLeaf) {
             onlyson(parent);
        }
    }

    void removebolsh2(Node* leaf) {
        Node* parent = leaf->parent;
        if (!parent) {
            delete leaf;
            root = nullptr;
            return;
        }
        int index = sonIndex(parent, leaf);
        if (index < 0) return;
        for (int i = index; i < parent->length - 1; ++i) {
            parent->sons[i] = parent->sons[i + 1];
        }
        parent->length--;
        parent->sons[parent->length] = nullptr;
        delete leaf;
        updatekeys(parent);
    }

    void remove2(Node* leaf) {
        Node* parent = leaf->parent;
        if(!parent) {
             delete leaf; root=nullptr; return;
        }
        
        // Находим sibling (второго ребенка родителя)
        Node* sibling = (parent->sons[0] == leaf) ? parent->sons[1] : parent->sons[0];
        Node* grand = parent->parent;

        if (!grand) {
            delete leaf;
            root = sibling;
            if(sibling) sibling->parent = nullptr;
            delete parent;
            return;
        }

        int parentIndex = sonIndex(grand, parent);
        if (parentIndex < 0) { removebolsh2(leaf); return; }

        Node* bratparent = nullptr;
        bool bratIsLeft = false;
        if (parentIndex > 0) {
            bratparent = grand->sons[parentIndex - 1];
            bratIsLeft = true;
        } else if (parentIndex + 1 < grand->length) {
            bratparent = grand->sons[parentIndex + 1];
            bratIsLeft = false;
        }

        removebolsh2(leaf); // Удаляем лист из parent

        if (parent->length >= 2) {
            updatekeys(grand);
            return;
        }

        // Если соседа нет (странная ситуация)
        if (!bratparent) {
            grand->sons[parentIndex] = sibling;
            if(sibling) sibling->parent = grand;
            delete parent;
            grand->length--; // Уменьшаем количество детей у grand
            updatekeys(grand);
            if (grand->length < 2) onlyson(grand);
            return;
        }

        // Заимствование
        if (bratparent->length == 3) {
            Node* borrowed = bratIsLeft ? bratparent->sons[bratparent->length - 1] : bratparent->sons[0];
            
            if (bratIsLeft) {
                bratparent->length--;
                bratparent->sons[bratparent->length] = nullptr;
            } else {
                // Сдвиг влево
                for(int k=0; k<bratparent->length-1; ++k) bratparent->sons[k] = bratparent->sons[k+1];
                bratparent->length--;
                bratparent->sons[bratparent->length] = nullptr;
            }

            parent->sons[parent->length++] = borrowed;
            if(borrowed) borrowed->parent = parent;
            sortsons(parent);
            updatekeys(grand);
            return;
        }

        // Слияние
        // Добавляем sibling к bratparent
        bratparent->sons[bratparent->length++] = sibling;
        if(sibling) sibling->parent = bratparent;
        sortsons(bratparent);

        // Удаляем parent из grand
        for (int i = parentIndex; i < grand->length - 1; ++i) {
            grand->sons[i] = grand->sons[i + 1];
        }
        grand->length--;
        grand->sons[grand->length] = nullptr;
        
        delete parent;
        updatekeys(grand);

        if (bratparent->length > 3) {
            splitParent(bratparent);
        }

        if (grand->length < 2 && !grand->isLeaf) {
            onlyson(grand);
        }
    }

    void clearTree(Node* node) {
        if (!node) return;
        if (!node->isLeaf) {
            for (int i = 0; i < node->length; ++i) {
                clearTree(node->sons[i]);
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
            collectInOrder(node->sons[i], keysOut, valuesOut);
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

        if (!pos->parent) { // Pos was root
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
            splitParent(parent);
        }
    }

    void Delete(const TKey& key) override {
        Node* leaf = searchleaf(root, key);
        if (!leaf || !leaf->isLeaf || leaf->data.key != key) return;

        if (!leaf->parent) {
            delete leaf;
            root = nullptr;
            treeSize = 0;
            return;
        }

        Node* parent = leaf->parent;
        if (parent->length > 2) {
            removebolsh2(leaf);
            treeSize--;
            return;
        }
        remove2(leaf);
        treeSize--;
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
        clearTree(root);
        root = nullptr;
        treeSize = 0;
    }
    
    void Print() override {
        if (!root) {
            cout << "{}" << endl;
            return;
        }
        vector<TKey> k = keys();
        vector<TValue> v = values();
        cout << "{ ";
        for (size_t i = 0; i < k.size(); ++i) {
            cout << k[i] << " : " << v[i];
            if (i + 1 < k.size()) cout << ", ";
        }
        cout << " }" << endl;
    }
};

#endif
