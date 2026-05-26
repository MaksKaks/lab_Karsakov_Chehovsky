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
    cout << "Tree: ";
    tree.Print();
    string* val = tree.Find(10);
    cout << "Find 10: " << *val << endl;
    cout << "Keys: ";
    vector<int> keys = tree.keys();
    for (int k : keys) cout << k << " ";
    cout << endl;
    tree.Delete(5);
    cout << "delete 5: ";
    tree.Print();
    tree.Clear();
    cout << "clear: ";
    tree.Print();
    
    return 0;
}
