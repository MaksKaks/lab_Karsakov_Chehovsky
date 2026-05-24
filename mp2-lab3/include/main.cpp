#include "trees.h"
#include "map.h"
#include <exception>
#include <iostream>
#include <string>


using namespace std;

int main() {
    Tree23<int, string> tree;
    tree.Insert(10, "ten");
    tree.Insert(5, "five");
    tree.Insert(15, "fifteen");
    tree.Insert(3, "three");
    tree.Insert(7, "seven");
    tree.Insert(12, "twelve");
    tree.Insert(18, "eighteen");
    cout << "\nTree contents:" << endl;
    tree.Print();
    cout << "\nFind 7: ";
    string* val = tree.Find(7);
    if (val) cout << *val << endl;
    else cout << "Not found" << endl;
    cout << "tree[15] = " << tree[15] << endl;
    cout << "\ndel 5..." << endl;
    tree.Delete(5);
    cout << "after del:" << endl;
    tree.Print();
    cout << endl;
    tree.Clear();
    cout << "\nclear: ";
    tree.Print();

    return 0;
}